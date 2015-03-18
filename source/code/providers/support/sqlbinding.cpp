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

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxfile.h>

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

        // Find the configuration file that we're going to use
        // (If we can't find one, just do the connect and pray)

        std::vector<std::string> configPaths;
        MySQL::GetConfigurationFilePaths( configPaths );

        for (std::vector<std::string>::const_iterator it = configPaths.begin(); it != configPaths.end(); ++it)
        {
            if ( SCXCoreLib::SCXFile::Exists(SCXCoreLib::StrFromUTF8(*it)) )
            {
                SCX_LOGHYSTERICAL(m_log, std::string("Configuring for connection using file: ") + *it);
                mysql_options( m_sqlConnection, MYSQL_READ_DEFAULT_FILE, (*it).c_str() );
                break;
            }
        }

        // Now connect to the MySQL server

        SCX_LOGHYSTERICAL(m_log, std::string("Connecting to MySQL server: ") + m_sqlHostName);
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

        SCX_LOGHYSTERICAL(m_log, "Successfully connected to MySQL server");
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



bool MySQL_Query::ExecuteQuery( const char* query, unsigned int queryLength /* = 0 */ )
{
    bool returnStatus = true;

    // Clear the prior results, if any
    m_columnNames.clear();
    m_queryResults.clear();

    // Execute the query using the row handler

    if ( (returnStatus = m_rowHandler.ExecuteQuery(query, queryLength)) )
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
    if ( NULL != m_sqlResult )
    {
        // Release the results
        mysql_free_result(m_sqlResult);
        m_sqlResult = NULL;
    }

    m_fQueryForResults = false;
}

const std::string MySQL_Query_Rows::EscapeQuery( const std::string&query )
{
    MYSQL * sqlConnection = m_deps->m_sqlConnection;

    if ( NULL == sqlConnection )
    {
        m_sqlErrorText = "Attach() not called; not connected to a server";
        SCX_LOGERROR(m_log, m_sqlErrorText);
        return std::string("");
    }

    char queryBuffer[query.size() * 2 + 1], *end = queryBuffer;
    end += mysql_real_escape_string(sqlConnection, queryBuffer, query.c_str(), query.size());
    return std::string(queryBuffer, end - queryBuffer);
}

bool MySQL_Query_Rows::ExecuteQuery( const char* query, unsigned int queryLength )
{
    bool returnStatus = true;
    SCX_LOGTRACE(m_log, std::string("Executing query: ") + query);

    // Clear for new query
    m_sqlErrorText.clear();
    m_sqlState.clear();
    m_sqlErrorNum = 0;

    Reset();

    MYSQL * sqlConnection = m_deps->m_sqlConnection;
    if ( NULL == sqlConnection )
    {
        m_sqlErrorText = "Attach() not called; not connected to a server";
        SCX_LOGERROR(m_log, m_sqlErrorText);
        return false;
    }

    try
    {
        // Execute the SQL query
        if ( queryLength == 0 )
        {
            queryLength = strlen(query);
        }

        if ( mysql_real_query(sqlConnection, query, queryLength) )
        {
            throw SQLError( mysql_error(sqlConnection), SCXSRCLOCATION );
        }

        m_sqlResult = mysql_store_result(sqlConnection);

        // Are there resulting rows?
        if ( m_sqlResult )
        {
            m_columnCount = mysql_num_fields( m_sqlResult );
            SCX_LOGTRACE(m_log, std::wstring(L"Query result column count: ") + SCXCoreLib::StrFrom(m_columnCount));

            // Ready to fetch rows via GetNextRow method ...
            m_fQueryForResults = true;
        }
        else
        {
            // We have an empty result set, but did we actually get an error?
            if ( 0 != mysql_field_count(sqlConnection) )
            {
                m_sqlErrorText = "Could not retrieve result set!";
                SCX_LOGERROR(m_log, m_sqlErrorText);
                returnStatus = false;
            }

            // Statement may have affected some number of rows, but we don't
            // return this (nobody cares), and it's not considered an error.
            //
            // If we care in the future, mysql_affected_rows() will give this.
        }
    }
    catch ( SQLError& e )
    { 
        m_sqlErrorText = SCXCoreLib::StrToUTF8( e.What() );
        SCX_LOGERROR(m_log, e.What());

        if (NULL != sqlConnection)
        {
            m_sqlState = mysql_sqlstate(sqlConnection);
            m_sqlErrorNum = mysql_errno(sqlConnection);
        }

        Reset();
        return false;
    }

    return returnStatus;
}

bool MySQL_Query_Rows::GetColumnNames( std::vector<std::string>& columnNames )
{
    columnNames.clear();

    if ( m_sqlResult && m_columnCount > 0 )
    {
        MYSQL_FIELD* field;
        while ( (field = mysql_fetch_field(m_sqlResult)) != NULL )
        {
            columnNames.push_back( field->name );
        }

        return true;
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

    MYSQL_ROW sqlRow;
    bool fMoreRows = false;
    if ( (sqlRow = mysql_fetch_row(m_sqlResult)) != NULL )
    {
        fMoreRows = true;

        for (unsigned int i = 0; i < m_columnCount; ++i)
        {
            const char *value = sqlRow[i];
            columns.push_back( value ? value : "" );
            SCX_LOGHYSTERICAL(m_log, std::string("Column ") + SCXCoreLib::StrToUTF8(SCXCoreLib::StrFrom(i))
                              + ": pushed " + (value ? value : "<empty>"));
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
