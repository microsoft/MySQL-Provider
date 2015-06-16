/* @migen@ */

/*
 * --------------------------------- START OF LICENSE ----------------------------
 *
 * MySQL cimprov ver. 1.0
 *
 * Copyright (c) Microsoft Corporation
 *
 * All rights reserved. 
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the ""Software""), to deal
 * in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ---------------------------------- END OF LICENSE -----------------------------
*/

#include <MI.h>
#include "MySQL_Server_Database_Class_Provider.h"

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxnameresolver.h>
#include <scxcorelib/stringaid.h>

#include "logstartup.h"
#include "sqlbinding.h"

using namespace SCXCoreLib;

MI_BEGIN_NAMESPACE

/**
   Enumerate each of the databases in a MySQL server instance given inputs

   \param[in]  context   OMI context for posting instances to
   \param[in]  hLog      LogHandle for logging purposes
   \param[in]  port      Port number of MySQL server instance to connect to
   \param[in]  pAuth     Authentication class for MySQL authentication
   \param[in]  keysOnly  True if only keys should be populated, false otherwise

*/
static void EnumerateServerDatabases(
    Context& context,
    SCXLogHandle& hLog,
    unsigned int port,
    util::unique_ptr<MySQL_Authentication>& pAuth,
    const bool keysOnly)
{
    util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );

    // Attach to the MySQL database instance
    if ( !pBinding->AttachUsingStoredCredentials(port, pAuth) )
    {
        std::stringstream ss;
        ss << "Failure attaching to MySQL on port: " << port << ", Error "
           << pBinding->GetErrorNum() << ": " << pBinding->GetErrorText();
        SCX_LOGERROR(hLog, ss.str());

        return;
    }

    // Execute a query to get the MySQL variables
    std::map<std::string, std::string> variables;
    util::unique_ptr<MySQL_Query> pQuery( g_pFactory->GetQuery() );
    if ( ! pQuery->ExecuteQuery("show variables") || ! pQuery->GetResults(variables) )
    {
        std::stringstream ss;
        ss << "Failure executing query \"show variables\" against MySQL engine on port " << port
           << ", Error " << pQuery->GetErrorNum() << ": " << pQuery->GetErrorText();
        SCX_LOGERROR(hLog, ss.str());

        return;
    }

    // The InstanceID is the hostname:bind-address:port:database combination (database added later)
    std::string hostname, strPort;
    if ( !GetStrValue(variables, "hostname", hostname) )
    {
        // Populate hostname here (for MySQL 5.0 systems)
        NameResolver nr;
        hostname = StrToUTF8(nr.GetHostname());
    }

    MySQL_AuthenticationEntry entry;
    pAuth->GetEntry(port, entry);

    if ( !GetStrValue(variables, "port", strPort) )
    {
        SCX_LOGWARNING(hLog, L"Query \"show variables\" did not return \"port\" in the result set");
        strPort = StrToUTF8(StrFrom(port));
        /* This one isn't fatal - continue processing, we've done the best we can */
    }
    std::string instanceID = hostname + ":" + entry.binding + ":" + strPort;

    // Execute a query to get a result set like:
    //   +--------------------+--------+--------------+
    //   | Database           | Tables | Size (Bytes) |
    //   +--------------------+--------+--------------+
    //   | information_schema |     28 |         8192 |
    //   +--------------------+--------+--------------+
    // Note that Size may be NULL if database has no tables

    MySQL_QueryResults databases;
    const char *queryString = "select b.schema_name as \"Database\","
                              " COUNT(a.table_name) as \"Tables\","
                              " SUM(a.data_length) + SUM(a.index_length) as \"Size (Bytes)\" "
                              "from information_schema.schemata b"
                              " left join information_schema.tables a on b.schema_name = a.table_schema "
                              "group by b.schema_name";
    if ( ! pQuery->ExecuteQuery(queryString) || ! pQuery->GetMultiColumnResults(databases) )
    {
        std::stringstream ss;
        ss << "Failure executing query to get list of tables/database against MySQL engine on port " << port
           << ", error " << pQuery->GetErrorNum() << ": " << pQuery->GetErrorText();
        SCX_LOGERROR(hLog, ss.str());

        return;
    }

    for (MySQL_QueryResults::const_iterator it = databases.begin(); it != databases.end(); ++it)
    {
        MySQL_Server_Database_Class inst;

        inst.InstanceID_value( std::string(instanceID + ":" + it->first).c_str() );

        if ( !keysOnly )
        {
            uint64_t tableCount = 0;
            uint64_t dbSize = 0;

            if ( ! ConvertToUnsigned(it->second[0], tableCount) )
            {
                SCX_LOGERROR(hLog, "Failure converting count for database " + it->first + "; enumerating with zero databases");
            }

            if ( it->second[1].size() && ! ConvertToUnsigned(it->second[1], dbSize) )
            {
                SCX_LOGERROR(hLog, "Failure converting size for database " + it->first + "; enumerating with zero disk space");
            }

            inst.DatabaseName_value( it->first.c_str() );
            inst.NumberOfTables_value( tableCount );
            inst.DiskSpaceInBytes_value( dbSize );
        }

        context.Post(inst);
    }
}

MySQL_Server_Database_Class_Provider::MySQL_Server_Database_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

MySQL_Server_Database_Class_Provider::~MySQL_Server_Database_Class_Provider()
{
}

void MySQL_Server_Database_Class_Provider::Load(
        Context& context)
{
    MySQL::LogStartup();

    context.Post(MI_RESULT_OK);
}

void MySQL_Server_Database_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void MySQL_Server_Database_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.provider.database");

    CIM_PEX_BEGIN
    {
        // Get the list of ports (instances) that we want to look at
        std::vector<unsigned int> portList;
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        pAuth->GetPortList(portList);

        for (std::vector<unsigned int>::const_iterator it = portList.begin(); it != portList.end(); ++it)
        {
            EnumerateServerDatabases(context, hLog, *it, pAuth, keysOnly);
        }

        context.Post(MI_RESULT_OK);
    }
    CIM_PEX_END( L"MySQL_Server_Database_Class_Provider::EnumerateInstances" , hLog );
}

void MySQL_Server_Database_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Database_Class& instanceName,
    const PropertySet& propertySet)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.provider.database");

    CIM_PEX_BEGIN
    {
        // Was have a single key:
        //   [Key] InstanceID=jeffcof64-rhel6-01:127.0.0.1:3306:<databasename>

        if ( !instanceName.InstanceID_exists() )
        {
            context.Post(MI_RESULT_INVALID_PARAMETER);
            return;
        }

        // Save the bind-address and port from the InstanceID (host:bind-address:port)

        std::wstring instanceID( StrFromUTF8(instanceName.InstanceID_value().Str()) );
        std::vector<std::wstring> elements;

        StrTokenize(instanceID, elements, L":", true, true);
        if ( 4 != elements.size() || std::string::npos != elements[2].find_first_not_of(L"0123456789") )
        {
            context.Post(MI_RESULT_NOT_FOUND);
            return;
        }

        std::string bindAddress( StrToUTF8(elements[1]) );
        unsigned int port = StrToUInt( elements[2] );
        std::string database( StrToUTF8(elements[3]) );

        // We have the information we need, so try and retrieve the instance
        // (But validate the bind address along the way)

        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        MySQL_AuthenticationEntry authEntry;
        pAuth->Load();
        pAuth->GetEntry(port, authEntry);

        if ( 0 != strcasecmp(authEntry.binding.c_str(), bindAddress.c_str()) )
        {
            context.Post(MI_RESULT_NOT_FOUND);
            return;
        }

        // We can't quite use prior infrastructure for this - it's just
        // "different enough". Considered ways to try and reuse existing code,
        // but no code deals with just one database, and this turns out to use
        // a different query against MySQL as well. Easiest to simply copy what
        // we need and modify to suite.

        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );

        // Attach to the MySQL database instance
        if ( !pBinding->AttachUsingStoredCredentials(port, pAuth) )
        {
            std::stringstream ss;
            ss << "Failure attaching to MySQL on port: " << port << ", Error "
               << pBinding->GetErrorNum() << ": " << pBinding->GetErrorText();
            SCX_LOGERROR(hLog, ss.str());

            context.Post(MI_RESULT_FAILED);
            return;
        }

        // Execute a query to get a result set like:
        //   +--------------------+--------+--------------+
        //   | Database           | Tables | Size (Bytes) |
        //   +--------------------+--------+--------------+
        //   | information_schema |     28 |         8192 |
        //   +--------------------+--------+--------------+
        // Note that Size may be NULL if database has no tables

        util::unique_ptr<MySQL_Query> pQuery( g_pFactory->GetQuery() );
        std::string strQueryPrefix = "select b.schema_name as \"Database\","
                                         "COUNT(a.table_name) as \"Tables\", "
                                         "SUM(a.data_length) + SUM(a.index_length) as \"Size (Bytes)\""
                                     " from information_schema.schemata b"
                                     " left join information_schema.tables a on b.schema_name = a.table_schema"
                                     " where b.schema_name = \"";
        std::string strQuerySuffix = "\" group by b.schema_name";

        std::string strQuery = strQueryPrefix + pQuery->EscapeQuery(database) + strQuerySuffix;

        MySQL_QueryResults databases;
        if ( ! pQuery->ExecuteQuery(strQuery.c_str(), strQuery.size())
             || ! pQuery->GetMultiColumnResults(databases) )
        {
            std::stringstream ss;
            ss << "Failure executing query to get list of databases/table-count/disk-used against MySQL engine, error "
               << pQuery->GetErrorNum() << ": " << pQuery->GetErrorText();
            SCX_LOGERROR(hLog, ss.str());

            context.Post(MI_RESULT_FAILED);
            return;
        }

        // If database wasn't found, then we won't find database in result set

        MySQL_QueryResults::const_iterator it = databases.find(database);
        if ( databases.end() != it )
        {
            MySQL_Server_Database_Class inst;
            uint64_t tableCount = 0;
            uint64_t dbSize = 0;

            if ( ! ConvertToUnsigned(it->second[0], tableCount) )
            {
                SCX_LOGERROR(hLog, "Failure converting count for database " + it->first + "; enumerating with zero databases");
            }

            if ( it->second[1].size() && ! ConvertToUnsigned(it->second[1], dbSize) )
            {
                SCX_LOGERROR(hLog, "Failure converting size for database " + it->first + "; enumerating with zero disk space");
            }

            inst.InstanceID_value( StrToUTF8(instanceID).c_str() );
            inst.DatabaseName_value( it->first.c_str() );
            inst.NumberOfTables_value( tableCount );
            inst.DiskSpaceInBytes_value( dbSize );

            context.Post(inst);
            context.Post(MI_RESULT_OK);
        }
        else
        {
            context.Post(MI_RESULT_NOT_FOUND);
        }
    }
    CIM_PEX_END( L"MySQL_Server_Database_Class_Provider::GetInstance", hLog );
}

void MySQL_Server_Database_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Database_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_Server_Database_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Database_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_Server_Database_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Database_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_Server_Database_Class_Provider::Invoke_RequestStateChange(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Database_Class& instanceName,
    const MySQL_Server_Database_RequestStateChange_Class& in)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
