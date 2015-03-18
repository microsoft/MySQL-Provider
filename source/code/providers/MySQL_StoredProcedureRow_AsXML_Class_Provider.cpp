/* @migen@ */

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxhandle.h>
#include <scxcorelib/scxlog.h>
#include <scxcorelib/scxnameresolver.h>

#include "sqlauth.h"
#include "sqlbinding.h"

#include <algorithm>
#include <string>

#include <MI.h>
#include "MySQL_StoredProcedureRow_AsXML_Class_Provider.h"

using namespace std;
using namespace SCXCoreLib;

//
// Utility functions
//
// Technically, these can be in anonomous namespace, but they're not for unit test purposes
//

// Helper to get a value for a specified key in a given query, throws MissingValue
bool GetValueForKey(string& value, const string& query, const string& key)
{
    // Note: We want parameter names in query to be case insensitive (as they are in OMI itself).
    // So we find what we care about on a lower-case'd version of the query, but then pull the
    // parameter value from the actual query string.
    string queryLower(query);
    std::transform(queryLower.begin(), queryLower.end(), queryLower.begin(), ::tolower);

    string delimiter("\"\'");
    string::size_type start(queryLower.find(key)); // Start position of key in query
    string::size_type quote(queryLower.find_first_of(delimiter, start)); // Position of first quote after key

    // If the key or first quote are not found, return failure
    if (start == string::npos || quote == string::npos)
    {
        return false;
    }

    string endDelimiter("\\" + queryLower.substr(quote,1));
    string::size_type lastPos = quote + 1;

    // Find the closing quote character
    do
    {
        string::size_type pos = queryLower.find_first_of(endDelimiter, lastPos);
        if ( string::npos == pos )
        {
            // These substr's won't throw exceptions as quote and 0 are guaranteed to be in bounds
            string tail(query.substr(quote + 1 /* " */)); // Tail of query not including first quote

            value = tail.substr(0, tail.find_first_of(delimiter)); // Value not including second quote
        }
        else if ( '\\' == queryLower[pos] )
        {
            // Skip any quoted character
            lastPos = pos + 2;
            continue;
        }
        else
        {
            // We must have found our closing quote
            value = query.substr(quote + 1, pos - quote - 1);
        }
        break;
    } while (true);


    return true;
}

/*----------------------------------------------------------------------------*/
/**
   Quote an XML string for passage via WS-Man (which is, itself, an XML format).
   The following characters are quoted:
        "       &quot;
        '       &apos;
        <       &lt;
        >       &gt;
        &       &amp;
   All other characters are passed through unmodified.

   \param    str        String quote as XML
   \returns             Quoted string
*/

string QuoteXMLString(string input)
{
    wstring text(StrFromUTF8(input));
    wstring delimiters(L"\"'<>&");
    stringstream ss;

    wstring::size_type lastPos = 0;

    do
    {
        wstring::size_type pos = text.find_first_of(delimiters, lastPos);
        if ( wstring::npos == pos )
        {
            ss << StrToUTF8(text.substr(lastPos));
            break;
        }

        if ( pos > 0 )
        {
            ss << StrToUTF8(text.substr(lastPos, pos - lastPos));
        }

        switch ( text[pos] )
        {
            case L'"':
                ss << "&quot;";
                break;

            case L'\'':
                ss << "&apos;";
                break;

            case L'<':
                ss << "&lt;";
                break;

            case L'>':
                ss << "&gt;";
                break;

            case '&':
                ss << "&amp;";
        }

        lastPos = pos + 1;
    } while (true);

    return ss.str();
}

MI_BEGIN_NAMESPACE

MySQL_StoredProcedureRow_AsXML_Class_Provider::MySQL_StoredProcedureRow_AsXML_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

MySQL_StoredProcedureRow_AsXML_Class_Provider::~MySQL_StoredProcedureRow_AsXML_Class_Provider()
{
}

void MySQL_StoredProcedureRow_AsXML_Class_Provider::Load(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void MySQL_StoredProcedureRow_AsXML_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void MySQL_StoredProcedureRow_AsXML_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.provider.storedprocedurerow_asxml");

    CIM_PEX_BEGIN
    {
        SCX_LOGTRACE(hLog, "Entry: MySQL_StoredProcedureRow_AsXML_Class_Provider::EnumerateInstances");

        // This provider's interface is the WQL invocation, which is a SQL-like query
        // made by the OMI client to the OMI server. We use this with a query of the
        // form:
        //
        //   select * from MySQL_StoredProcedureRow_AsXML
        //    where DatabaseName = 'dbname' or StoredProcedureName = 'spname'
        //       or Prameters = 'param1, param2, param3'
        //
        // In this way, we can indirectly receive input (the database name, the stored
        // procedure name, and the parameters) while OMI's processing of the WQL query
        // will pass all rows since DatabaseName and StoredProcedureName are always
        // returned with all instances.
        //
        // Since the filter is required, return an error if filter is not specified.
        if ( !filter )
        {
            SCX_LOGINFO(hLog, "Class StoredProcedureRow_AsXML enumerated without XML filter!");
            context.Post( MI_RESULT_FAILED );
            return;
        }

        // The MI_Filter pointer (structure defined in MI.h) gives us the expression
        // via the function table found on the filter. 'GetExpression' returns the
        // query through a C-style reference.

        const MI_Char* lang;            // String to receive the 'query language', must be "WQL"
        const MI_Char* expr;            // String to receive the 'query expression', our input

        filter->ft->GetExpression(filter, &lang, &expr);

        // Sanity check (the query language must be WQL)
        {
            string language(lang);
            if ( language != "WQL" )
            {
                SCX_LOGERROR(hLog, "Class StoredProcedureRow_AsXML enumerated with query language: " + language);
                context.Post( MI_RESULT_FAILED );
                return;
            }
        }

        // Get our query and required parameters from the query
        string query(expr);
        string strPort, database, spName, spParameters;
        unsigned int port;

        if ( GetValueForKey(strPort, query, "port") )
        {
            port = StrToUInt(StrFromUTF8(strPort));
        }
        else
        {
            // Default to port 3306 if port not specified in query
            port = 3306;
        }

        if ( !GetValueForKey(database, query, "databasename") )
        { 
            SCX_LOGINFO(hLog, "Class StoredProcedureRow_AsXML enumerated with query: " + query + ", couldn't find DatabaseName");
            context.Post( MI_RESULT_FAILED );
            return;
        }

        if ( !GetValueForKey(spName, query, "storedprocedurename") )
        {
            SCX_LOGINFO(hLog, "Class StoredProcedureRow_AsXML enumerated with query: " + query
                                 + ", couldn't find StoredProcedureName");
            context.Post( MI_RESULT_FAILED );
            return;
        }

        GetValueForKey(spParameters, query, "parameters"); // Parameters are optional
        SCX_LOGTRACE(hLog, "MySQL_StoredProcedureRow_AsXML_Class_Provider::EnumerateInstances: Query: " + query
                           + ", Database: " + database + ", StoredProcName: " + spName);
        if ( spParameters.size() )
        {
            SCX_LOGTRACE(hLog, "MySQL_StoredProcedureRow_AsXML_Class_Provider::EnumerateInstances: Parameters: " + spParameters);
        }
        else
        {
            SCX_LOGTRACE(hLog, "MySQL_StoredProcedureRow_AsXML_Class_Provider::EnumerateInstances: (No parameters)");
        }

        // Contruct parameter list for the query
        vector<std::string> parameters;
        if ( spParameters.size() )
        {
            vector<std::wstring> wParameters;
            StrTokenize(StrFromUTF8(spParameters), wParameters, L",");

            // Convert the std::wstring vector into std::string vector
            for (vector<std::wstring>::const_iterator it = wParameters.begin(); it != wParameters.end(); ++it)
            {
                parameters.push_back( StrToUTF8(*it) );
            }
        }

        //
        // Now we're ready to execute the stored procedure
        //

        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Query_Rows> pQuery(g_pFactory->GetQueryByRow());
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();

        pBinding->AllowStoredProcedures();
        if ( !pBinding->AttachUsingStoredCredentials(port, pAuth, database) )
        {
            std::stringstream ss;
            ss << "Failure attaching to MySQL on port: " << port << ", Error "
               << pBinding->GetErrorNum() << ": " << pBinding->GetErrorText();
            SCX_LOGINFO(hLog, ss.str());

            context.Post(MI_RESULT_FAILED);
            return;
        }

        // Construct the query string (something like 'call `spName` ("p1", "p2", "p3")' based on # of parameters)
        string strQuery = "call `" + spName + "` ";
        if ( parameters.size() )
        {
            for (vector<std::string>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
            {
                strQuery += ( it == parameters.begin() ? "(\"" : ", \"");
                strQuery += pQuery->EscapeQuery(*it) + "\"";
            }
            strQuery += ");";
        }
        else
        {
            strQuery += "();";
        }
        // The following is only logged in trace mode; check severity for efficiency
        if ( eTrace == hLog.GetSeverityThreshold() )
        {
            SCX_LOGTRACE(hLog, "MySQL generated query: " + strQuery);

            string parameterList;
            string quote ("\"");
            for (vector<std::string>::const_iterator it = parameters.begin(); it != parameters.end(); ++it)
            {
                parameterList += (it != parameters.begin()  ? ", " : "") + quote + *it + quote;
            }
            SCX_LOGTRACE(hLog, "Parameter substitution list: " + ( parameterList.size() ? parameterList : "<None>") );
        }

        if ( ! pQuery->ExecuteQuery(strQuery.c_str(), strQuery.size()) )
        {
            std::stringstream ss;
            ss << "Failure executing query to execute stored procedure, error "
               << pQuery->GetErrorNum() << ": " << pQuery->GetErrorText();
            SCX_LOGINFO(hLog, ss.str());

            context.Post(MI_RESULT_FAILED);
            return;
        }

        // Don't try to get further information if no data was returned from query
        if ( pQuery->GetColumnCount() )
        {
            vector<string> columnNames, columns;
            if ( ! pQuery->GetColumnNames(columnNames) )
            {
                std::stringstream ss;
                ss << "Failure collecting column names, error "
                   << pQuery->GetErrorNum() << ": " << pQuery->GetErrorText();
                SCX_LOGINFO(hLog, ss.str());

                context.Post(MI_RESULT_FAILED);
                return;
            }

            // Instance ID should be: hostname:bind-address:port:database:storedProcName:row#
            // Build the constant stuff here, once for efficiency
            string instanceID;
            {
                stringstream ss;

                NameResolver nr;
                string hostname = StrToUTF8(nr.GetHostname());

                MySQL_AuthenticationEntry entry;
                pAuth->GetEntry(port, entry);

                ss << hostname << ":" << entry.binding << ":" << port << ":"
                   << database << ":" << spName << ":";
                instanceID = ss.str();
            }

            size_t rowNumber = 0;
            while ( pQuery->GetNextRow(columns) )
            {
                rowNumber++;

                MySQL_StoredProcedureRow_AsXML_Class inst;
                inst.InstanceID_value( string(instanceID + StrToUTF8(StrFrom(rowNumber))).c_str() );

                if ( ! keysOnly )
                {
                    // Construct the result for this row
                    string rowResult;
                    rowResult += "<row>";
                    bool fIsTruncated = false;

                    for (size_t i = 0; i < pQuery->GetColumnCount(); ++i)
                    {
                        std::string columnResult;
                        columnResult += "<field name=\"" + QuoteXMLString(columnNames[i]) + "\">";
                        columnResult += QuoteXMLString(columns[i]);
                        columnResult += "</field>";

                        // Limit return row length to 60k bytes (OMI instance max is 64k bytes)
                        if (rowResult.size() + columnResult.size() > 60000)
                        {
                            fIsTruncated = true;
                            break;
                        }

                        rowResult += columnResult;
                    }

                    rowResult += "</row>";

                    // Populate remaining columns
                    inst.Port_value( port );
                    inst.DatabaseName_value( database.c_str() );
                    inst.StoredProcedureName_value( spName.c_str() );
                    // Property "Parameters" will not be returned ...
                    inst.RowXMLValue_value( rowResult.c_str() );
                    inst.IsTruncated_value( fIsTruncated );
                }
                context.Post(inst);
            }
        }

        SCX_LOGTRACE(hLog, "Exit: MySQL_StoredProcedureRow_AsXML_Class_Provider::EnumerateInstances");
        context.Post(MI_RESULT_OK);
    }
    CIM_PEX_END( L"MySQL_StoredProcedureRow_AsXML_Class_Provider::EnumerateInstances", hLog );
}

void MySQL_StoredProcedureRow_AsXML_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_StoredProcedureRow_AsXML_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_StoredProcedureRow_AsXML_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_StoredProcedureRow_AsXML_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_StoredProcedureRow_AsXML_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_StoredProcedureRow_AsXML_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_StoredProcedureRow_AsXML_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_StoredProcedureRow_AsXML_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
