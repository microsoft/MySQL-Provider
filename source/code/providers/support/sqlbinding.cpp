/*--------------------------------------------------------------------------------
 *        Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *      
 *           */
 /**
        \file        sqlbinding.cpp

        \brief       Provider helper functions for MySQL bindings

        \date        10-28-14
*/
/*----------------------------------------------------------------------------*/

#include <vector>

#include "errmsg.h"

#include "mycnf-paths.h"
#include "sqlauth.h"
#include "sqlbinding.h"

// Define single global copy (intended as a singleton class)
SCXCoreLib::SCXHandle<MySQL_Factory> g_pFactory(new MySQL_Factory());

class SQLError : public SCXCoreLib::SCXException
{
public:
    SQLError(const SCXCoreLib::SCXCodeLocation& l)
        : SCXException(l), m_errorText(L"Generic Error")
    { }
    SQLError(const char *errorText, const SCXCoreLib::SCXCodeLocation& l)
        : SCXException(l), m_errorText(SCXCoreLib::StrFromUTF8(errorText))
    { }
    ~SQLError() { }

    std::wstring What() const
    {
        return m_errorText;
    }

private:
    std::wstring m_errorText;
};



MySQL_Dependencies::~MySQL_Dependencies()
{
    Detach();
}

bool MySQL_Dependencies::Attach()
{
    m_sqlErrorText.clear();
    m_sqlState.clear();
    m_sqlErrorNum = 0;

    if ( NULL == m_sqlConnection )
    {
        m_sqlConnection = mysql_init( NULL );
    }

    try
    {
        MYSQL *sqlConnRet;

        sqlConnRet = mysql_real_connect(
            m_sqlConnection,
            m_sqlHostName.c_str(),
            m_sqlUserID.c_str(),
            m_sqlPassword.c_str(),
            m_sqlDatabase.size() ? m_sqlDatabase.c_str() : NULL,
            m_sqlPort,                  /* Port */
            NULL,                       /* UNIX Socket */
            m_sqlConnectFlags );        /* Client connection flags */

        if ( NULL == sqlConnRet )
        {
            m_sqlErrorText = mysql_error(m_sqlConnection);
            m_sqlState = mysql_sqlstate(m_sqlConnection);
            m_sqlErrorNum = mysql_errno(m_sqlConnection);

            throw SQLError( mysql_error(m_sqlConnection), SCXSRCLOCATION );
        }

        m_infoConnection = mysql_get_host_info( m_sqlConnection );
        m_infoClient = mysql_get_client_info();
        m_infoServer = mysql_get_server_info( m_sqlConnection );
    }
    catch ( SQLError& e )
    {
        SCX_LOGERROR(m_log, e.What());
        return false;
    }

    return true;
}

bool MySQL_Dependencies::AttachUsingStoredCredentials(
    unsigned int port,
    util::unique_ptr<MySQL_Authentication>& auth,
    const std::string& database)
{
    bool fValidEntry = false;
    MySQL_AuthenticationEntry entry;
    try {
        fValidEntry = auth->GetEntry(port, entry);
    }
    catch (SCXCoreLib::SCXException& e)
    {
        SCX_LOGERROR(m_log, L"Failure getting credential entry: " + e.What());
        m_sqlErrorNum = MYSQL_AUTH_EXCEPTION;
        m_sqlErrorText = SCXCoreLib::StrToUTF8( e.What() );

        return false;
    }

    if ( ! fValidEntry )
    {
        m_sqlErrorNum = MYSQL_AUTH_INVALID_ENTRY;
        m_sqlErrorText = SCXCoreLib::StrToUTF8( SCXCoreLib::StrAppend(L"Invalid authentication entry for port ", port) );

        return false;
    }

    return Attach(entry.port, entry.binding, entry.username, entry.password, database);
}

bool MySQL_Dependencies::Detach()
{
    if ( NULL != m_sqlConnection )
    {
        mysql_close( m_sqlConnection );
        m_sqlConnection = NULL;
    }

    return true;
}



bool MySQL_Query::ExecuteQuery( const char* query )
{
    std::vector<std::string> parameters;
    return ExecuteQuery( query, parameters );
}



// Implementation note: Use prepared statements in API to avoid SQL injection attacks

bool MySQL_Query::ExecuteQuery( const char* query, const std::vector<std::string>& parameters )
{
    bool returnStatus = true;

    // Clear the prior results, if any
    m_columnNames.clear();
    m_queryResults.clear();

    // Execute the query using the row handler

    if ( (returnStatus = m_rowHandler.ExecuteQuery(query, parameters)) )
    {
        m_rowHandler.GetColumnNames( m_columnNames );

        if ( m_rowHandler.GetColumnCount() >= 2 )
        {
            std::vector<std::string> columns;
            while ( m_rowHandler.GetNextRow(columns) )
            {
                // If key is NULL, then don't try to insert the record
                if ( columns[0].size() == 0 )
                {
                    SCX_LOGERROR(m_log, std::string("Null key returned for query: ") + query);
                    continue;
                }

                // Get the key (in lower case)
                std::string key = columns[0];
                std::transform(key.begin(), key.end(), key.begin(), ::tolower);

                if ( m_queryResults.count(key) > 0 )
                {
                    m_sqlErrorText = "Duplicate result " + key + " returned in result set";
                    returnStatus = false;
                    break;
                }

                for (unsigned int i = 1; i < m_rowHandler.GetColumnCount(); ++i)
                {
                    m_queryResults[key].push_back( columns[i] );
                }
            }
        }
        else
        {
            // We didn't get two columns of information back from query
                
            m_sqlErrorText = "Result set did not contain at least two columns of data";
            returnStatus = false;
        }
    }
    else
    {
        // Query didn't execute for some reason ...

        m_sqlErrorText = m_rowHandler.GetErrorText();
        m_sqlState = m_rowHandler.GetErrorState();
        m_sqlErrorNum = m_rowHandler.GetErrorNum();
    }

    return returnStatus;
}

bool MySQL_Query::GetResults(std::map<std::string,std::string>& results)
{
    results.clear();

    if ( 2 != m_rowHandler.GetColumnCount() )
    {
        // We didn't get two columns of information back from query

        m_sqlErrorText = "Result set did not contain two columns of data";
        m_sqlState = "";
        m_sqlErrorNum = 0;

        return false;
    }

    // Make it easy to get a two-column result set
    // This is reasonable since our queries tend to be small

    for (MySQL_QueryResults::const_iterator it = m_queryResults.begin(); it != m_queryResults.end(); ++it )
    {
        results.insert( std::pair<std::string,std::string>(it->first, it->second[0]) );
    }
    return true;
}

bool MySQL_Query::GetMultiColumnResults(MySQL_QueryResults& results) const
{
    results = m_queryResults;
    return true;
}



MySQL_Query_Rows::~MySQL_Query_Rows()
{
    Reset();
}

void MySQL_Query_Rows::Reset()
{
    if ( NULL != m_deps->m_sqlConnection && NULL != m_sqlStatement )
    {
        // Release the statement results
        if ( mysql_stmt_free_result(m_sqlStatement) )
        {
            m_sqlErrorText = mysql_stmt_error(m_sqlStatement);
            m_sqlState = mysql_stmt_sqlstate(m_sqlStatement);
            m_sqlErrorNum = mysql_stmt_errno(m_sqlStatement);

            SCX_LOGWARNING(m_log, "Error calling mysql_stmt_free_result(): " + m_sqlErrorText);
        }

        // Close the prepared statement
        //
        // Note: With MySQL versions prior to v5.5.3, prepared statements that
        // utilize 'call' queries (to stored procedures) can't close properly
        // since we don't have mysql_stmt_next_result() to get the result of the
        // stored procedure execution.  This causes an error to be logged:
        //
        //   Commands out of sync; you can't run this command now
        //
        // Detect this and don't log the error to keep the log clean

        bool fResultsOutstanding = mysql_more_results(m_deps->m_sqlConnection);
        if ( mysql_stmt_close(m_sqlStatement) && !fResultsOutstanding )
        {
            m_sqlErrorText = mysql_stmt_error(m_sqlStatement);
            m_sqlState = mysql_stmt_sqlstate(m_sqlStatement);
            m_sqlErrorNum = mysql_stmt_errno(m_sqlStatement);

            SCX_LOGWARNING(m_log, "Error calling mysql_stmt_close(): " + m_sqlErrorText);
        }

        // If the statement wasn't really closed from above, we may have a leak
        // (but there's really nothing we can do about it).
        //
        // Note that since our agent is short-lived, any leaks should clear up on shutdown

        m_sqlStatement = NULL;
    }

    if ( NULL != m_bindInParamLength )
    {
        delete [] m_bindInParamLength;
        m_bindInParamLength = NULL;
    }

    if ( NULL != m_bindOutParams )
    {
        delete [] m_bindOutParams;
        m_bindOutParams = NULL;
    }

    if ( NULL != m_bindOutResultData )
    {
        delete [] m_bindOutResultData;
        m_bindOutResultData = NULL;
    }

    if ( NULL != m_bindOutParamLength )
    {
        delete [] m_bindOutParamLength;
        m_bindOutParamLength = NULL;
    }

    m_fQueryForResults = false;
}

bool MySQL_Query_Rows::ExecuteQuery( const char* query, const std::vector<std::string>& parameters )
{
    bool returnStatus = true;
    SCX_LOGTRACE(m_log, std::string("Executing query: ") + query);

    // Clear for new query
    m_sqlErrorText.clear();
    m_sqlState.clear();
    m_sqlErrorNum = 0;

    Reset();

    try
    {
        MYSQL * sqlConnection = m_deps->m_sqlConnection;

        if ( NULL == sqlConnection )
        {
            m_sqlErrorText = "Attach() not called; not connected to a server";
            SCX_LOGERROR(m_log, m_sqlErrorText);
            return false;
        }

        // Initialize the statement
        m_sqlStatement = mysql_stmt_init( sqlConnection );
        if ( !m_sqlStatement )
        {
            m_sqlErrorText = "mysql_stmt_init() failed, out of memory";
            m_sqlErrorNum = CR_OUT_OF_MEMORY; // Don't have sqlStatement to assign normally

            throw SQLError( m_sqlErrorText.c_str(), SCXSRCLOCATION );
        }

        // Prepare the statement
        if ( mysql_stmt_prepare(m_sqlStatement, query, strlen(query)) )
        {
            throw SQLError( mysql_stmt_error(m_sqlStatement), SCXSRCLOCATION );
        }

        //
        // Bind the parameters (passed in) to the statement if any exist
        //

        size_t parameterCount;
        if ( (parameterCount = parameters.size()) > 0 )
        {
            SCX_LOGTRACE(m_log, std::wstring(L"Binding ") + SCXCoreLib::StrFrom(parameters.size()) + L" input parameters");

            MYSQL_BIND params[parameterCount];
            m_bindInParamLength = new long unsigned int[parameterCount];
            memset( params, 0, sizeof(params) );

            for (size_t i = 0; i < parameterCount; ++i)
            {
                params[i].buffer_type = MYSQL_TYPE_STRING;
                params[i].buffer = (void *) ( parameters[i].c_str() );
                params[i].buffer_length = static_cast<long unsigned int>( parameters[i].size() + 1 );
                params[i].is_null = 0;
                params[i].length = &m_bindInParamLength[i];

                m_bindInParamLength[i] = parameters[i].size();
            }

            if ( mysql_stmt_bind_param(m_sqlStatement, params) )
            {
                throw SQLError( mysql_stmt_error(m_sqlStatement), SCXSRCLOCATION );
            }
        }

        // Execute the SQL statement
        if ( mysql_stmt_execute(m_sqlStatement) )
        {
            throw SQLError( mysql_stmt_error(m_sqlStatement), SCXSRCLOCATION );
        }

        m_columnCount = mysql_stmt_field_count(m_sqlStatement);
        SCX_LOGTRACE(m_log, std::wstring(L"Query result column count: ") + SCXCoreLib::StrFrom(m_columnCount));

        if ( m_columnCount > 0 )
        {
            // We have results, so allow them to be collected

            m_fQueryForResults = true;

            // Bind the results so we can fetch from the database

            m_bindOutParams = new MYSQL_BIND [m_columnCount];
            m_bindOutResultData = new char [m_columnCount * COLUMN_MAXLEN];
            m_bindOutParamLength = new unsigned long [m_columnCount];
            memset( m_bindOutParams, 0, sizeof(MYSQL_BIND) * m_columnCount );

            for (size_t i = 0; i < m_columnCount; ++i)
            {
                m_bindOutParams[i].buffer_type = MYSQL_TYPE_VAR_STRING;
                m_bindOutParams[i].buffer = &m_bindOutResultData[i * COLUMN_MAXLEN];
                m_bindOutParams[i].buffer_length = COLUMN_MAXLEN;
                m_bindOutParams[i].is_null = 0;
                m_bindOutParams[i].length = &m_bindOutParamLength[i];
            }

            // Bind the results buffer ...

            if ( mysql_stmt_bind_result(m_sqlStatement, m_bindOutParams) )
            {
                throw SQLError( mysql_stmt_error(m_sqlStatement), SCXSRCLOCATION );
            }

            // At this point, we're good to go for calling GetNextRow() ...
        }
        else
        {
            m_sqlErrorText = "Result set is empty";
            SCX_LOGTRACE(m_log, m_sqlErrorText);
            returnStatus = false;
        }
    }
    catch ( SQLError& e )
    { 
        m_sqlErrorText = SCXCoreLib::StrToUTF8( e.What() );
        SCX_LOGERROR(m_log, e.What());

        if (NULL != m_sqlStatement)
        {
            m_sqlState = mysql_stmt_sqlstate(m_sqlStatement);
            m_sqlErrorNum = mysql_stmt_errno(m_sqlStatement);
        }

        Reset();
        return false;
    }

    return returnStatus;
}

bool MySQL_Query_Rows::GetColumnNames( std::vector<std::string>& columnNames )
{
    columnNames.clear();

    if ( m_fQueryForResults && m_columnCount > 0 )
    {
        try
        {
            MYSQL_RES *resultSet = mysql_stmt_result_metadata(m_sqlStatement);
            if ( !resultSet )
            {
                throw SQLError( mysql_stmt_error(m_sqlStatement), SCXSRCLOCATION );
            }

            MYSQL_FIELD* field;
            while ( (field = mysql_fetch_field(resultSet)) != 0 )
            {
                columnNames.push_back( field->name );
            }

            mysql_free_result(resultSet);
            return true;
        }
        catch ( SQLError& e )
        { 
            m_sqlErrorText = SCXCoreLib::StrToUTF8( e.What() );
            SCX_LOGERROR(m_log, e.What());

            if (NULL != m_sqlStatement)
            {
                m_sqlState = mysql_stmt_sqlstate(m_sqlStatement);
                m_sqlErrorNum = mysql_stmt_errno(m_sqlStatement);
            }

            return false;
        }
    }

    return false;
}

bool MySQL_Query_Rows::GetNextRow( std::vector<std::string>& columns )
{
    columns.clear();

    // Nothing to query for? Then don't allow it ...
    if ( ! m_fQueryForResults )
    {
        return false;
    }

    SCX_LOGHYSTERICAL(m_log, "MySQL::GetNextRow entry");

    /*
     * If the prepared statement result set contains somethning like this:
     *
     * +--------------------+--------+--------------+
     * | Database           | Tables | Size (Bytes) |
     * +--------------------+--------+--------------+
     * | information_schema |     28 |         8192 |
     * | mysql              |     23 |       641963 |
     * | test               |      0 |         NULL |
     * +--------------------+--------+--------------+
     *
     * then, unfortunately, mysql_stmt_fetch doesn't set up the last column
     * result bindings for the very last column. This causes programs looking
     * at the result bindings to believe that the size of the test database is
     * acutally 641963, which is wrong.
     *
     * Furthermore, it appears that the length (in m_bindOutParamLength) isn't set
     * properly for numeric fields that undergo ASCII conversion. Thus, the
     * easist fix is to zero out the result memory (variable m_bindOutResultData),
     * making it appear that this last field is "", which is good enough.
     */

    memset( m_bindOutResultData, 0, m_columnCount * COLUMN_MAXLEN );
    memset( m_bindOutParamLength, 0, m_columnCount * sizeof(unsigned long) );

    bool fMoreRows = false;
    if ( mysql_stmt_fetch(m_sqlStatement) == 0 )
    {
        fMoreRows = true;

        for (unsigned int i = 0; i < m_columnCount; ++i)
        {
            if ( m_bindOutParams[i].is_null && *(m_bindOutParams[i].is_null) )
            {
                columns.push_back( "" );
                SCX_LOGHYSTERICAL(m_log, std::wstring(L"Column ") + SCXCoreLib::StrFrom(i) + L": pushed EMPTY" );
            }
            else
            {
                m_bindOutResultData[(i * COLUMN_MAXLEN) + m_bindOutParamLength[i]] = '\0';
                columns.push_back( &m_bindOutResultData[i * COLUMN_MAXLEN] );
                SCX_LOGHYSTERICAL(m_log, std::string("Column ") + SCXCoreLib::StrToUTF8(SCXCoreLib::StrFrom(i))
                             + ": pushed " + &m_bindOutResultData[i * COLUMN_MAXLEN]);
            }
        }
    }

    SCX_LOGHYSTERICAL(m_log, "MySQL::GetNextRow exit");
    return fMoreRows;
}



MySQL_Binding::~MySQL_Binding()
{
    Detach();

    // Note: We don't "own" pointer to dependencies; this is owned by the factory
}

void MySQL_Binding::GetConfigurationFilePaths( std::vector<std::string>& paths )
{
    MySQL::GetConfigurationFilePaths( paths );
    return;
}



// Get string value from map
bool GetStrValue(const std::map<std::string, std::string>& mymap, const std::string keyName, std::string& value)
{
    std::map<std::string, std::string>::const_iterator it;
    it = mymap.find(keyName);
    if ( mymap.end() == it )
    {
        return false;
    }

    value = it->second;
    return true;
}

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
