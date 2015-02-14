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
            NULL,      /* No database connection */
            m_sqlPort, /* Port */
            NULL,      /* UNIX Socket */
            0 );       /* Client connection flags */

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

bool MySQL_Dependencies::AttachUsingStoredCredentials(unsigned int port, util::unique_ptr<MySQL_Authentication>& auth)
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

    return Attach(entry.port, entry.binding, entry.username, entry.password);
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
    SCX_LOGINFO(m_log, std::string("Executing query: ") + query);

    // Clear the prior results, if any
    m_columnNames.clear();
    m_queryResults.clear();

    m_sqlErrorText.clear();
    m_sqlState.clear();
    m_sqlErrorNum = 0;

    MYSQL_STMT* sqlStatement = NULL;
    long unsigned int* paramLength = NULL;
    try
    {
        MYSQL * sqlConnection = m_deps->m_sqlConnection;

        if ( NULL == sqlConnection )
        {
            m_sqlErrorText = "Attach() not called; not connected to a server";
            return false;
        }

        // Initialize the statement
        sqlStatement = mysql_stmt_init( sqlConnection );
        if ( !sqlStatement )
        {
            m_sqlErrorText = "mysql_stmt_init() failed, out of memory";
            m_sqlErrorNum = CR_OUT_OF_MEMORY; // Don't have sqlStatement to assign normally

            throw SQLError( m_sqlErrorText.c_str(), SCXSRCLOCATION );
        }

        // Prepare the statement
        if ( mysql_stmt_prepare(sqlStatement, query, strlen(query)) )
        {
            throw SQLError( mysql_stmt_error(sqlStatement), SCXSRCLOCATION );
        }

        //
        // Now that the statement is prepared, we can pick up the column names.
        // (If no columns, then statement must not have generated results)
        //

        if ( (m_columnCount = mysql_stmt_field_count(sqlStatement)) > 0 )
        {
            MYSQL_RES *resultSet = mysql_stmt_result_metadata(sqlStatement);
            if ( !resultSet )
            {
                throw SQLError( mysql_stmt_error(sqlStatement), SCXSRCLOCATION );
            }

            MYSQL_FIELD* field;
            while ( (field = mysql_fetch_field(resultSet)) != 0 )
            {
                m_columnNames.push_back( field->name );
            }

            mysql_free_result(resultSet);
        }

        //
        // Bind the parameters (passed in) to the statement if any exist
        //

        size_t parameterCount;
        if ( (parameterCount = parameters.size()) > 0 )
        {
            MYSQL_BIND params[parameterCount];
            paramLength = new long unsigned int[parameterCount];
            memset( params, 0, sizeof(params) );

            for (size_t i = 0; i < parameterCount; ++i)
            {
                params[i].buffer_type = MYSQL_TYPE_STRING;
                params[i].buffer = (void *) ( parameters[i].c_str() );
                params[i].buffer_length = static_cast<long unsigned int>( parameters[i].size() + 1 );
                params[i].is_null = 0;
                params[i].length = &paramLength[i];

                paramLength[i] = parameters[i].size();
            }

            if ( mysql_stmt_bind_param(sqlStatement, params) )
            {
                throw SQLError( mysql_stmt_error(sqlStatement), SCXSRCLOCATION );
            }
        }

        //
        // Bind the output parameters (passed in) to the statement if appropriate
        //

        if ( m_columnCount > 0 )
        {
            const unsigned int COLUMN_MAXLEN = 256; /* Arbitary value, raise if needed */

            MYSQL_BIND results[m_columnCount];
            char result_data[m_columnCount][COLUMN_MAXLEN];
            unsigned long result_lengths[m_columnCount];

            memset( results, 0, sizeof(results) );

            for (size_t i = 0; i < m_columnCount; ++i)
            {
                results[i].buffer_type = MYSQL_TYPE_VAR_STRING;
                results[i].buffer = result_data[i];
                results[i].buffer_length = COLUMN_MAXLEN;
                results[i].is_null = 0;
                results[i].length = &result_lengths[i];
            }

            // Bind the results buffer ...
            if ( mysql_stmt_bind_result(sqlStatement, results) )
            {
                throw SQLError( mysql_stmt_error(sqlStatement), SCXSRCLOCATION );
            }

            // ... and execute the SQL statement
            if ( mysql_stmt_execute(sqlStatement) )
            {
                throw SQLError( mysql_stmt_error(sqlStatement), SCXSRCLOCATION );
            }

            // Finally collect up the results

            if ( m_columnCount >= 2 )
            {
                SCX_LOGERROR(m_log, std::string("Results for query: ") + query);

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
                 * Furthermore, it appears that the length (in result_lengths) isn't set
                 * properly for numeric fields that undergo ASCII conversion. Thus, the
                 * easist fix is to zero out the result memory (variable result_data),
                 * making it appear that this last field is "", which is good enough.
                 */

                while ( memset( result_data, 0, sizeof(result_data) ),
                        memset( result_lengths, 0, sizeof(result_lengths) ),
                        mysql_stmt_fetch(sqlStatement) == 0 )
                {
                    // If key is NULL, then don't try to insert the record
                    if ( results[0].is_null )
                    {
                        continue;
                    }

                    // Get the key (in lower case)
                    std::string key = result_data[0];
                    std::transform(key.begin(), key.end(), key.begin(), ::tolower);

                    if ( m_queryResults.count(key) > 0 )
                    {
                        m_sqlErrorText = "Duplicate result " + key + " returned in result set";
                        returnStatus = false;
                        break;
                    }

                    for (unsigned int i = 1; i < m_columnCount; ++i)
                    {
                        if ( ! results[i].is_null )
                        {
                            result_data[i][result_lengths[i]] = '\0';
                            m_queryResults[key].push_back( result_data[i] );
                            SCX_LOGERROR(m_log, std::string("For key ") + key + ", pushed back " + result_data[i]);
                            // TODO: gi wrong for test database on port 3399 - why?
                            // Wrong because fetch returned different number of rows?
                            // (memset at while loop resolved, but is this the right fix?)
                        }
                        else
                        {
                            m_queryResults[key].push_back( "" );
                            SCX_LOGERROR(m_log, std::string("For key ") + key + ", pushed back EMPTY" );
                        }
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
            // No results to bind, so just execute (no data returned)
            if ( mysql_stmt_execute(sqlStatement) )
            {
                throw SQLError( mysql_stmt_error(sqlStatement), SCXSRCLOCATION );
            }

            m_sqlErrorText = "Result set is empty";
            returnStatus = false;
        }

    }
    catch ( SQLError& e )
    {
        m_sqlErrorText = SCXCoreLib::StrToUTF8( e.What() );
        SCX_LOGERROR(m_log, e.What());

        if (NULL != sqlStatement)
        {
            m_sqlState = mysql_stmt_sqlstate(sqlStatement);
            m_sqlErrorNum = mysql_stmt_errno(sqlStatement);
            mysql_stmt_close(sqlStatement);
        }

        delete [] paramLength;
        return false;
    }

    if (NULL != sqlStatement)
    {
        mysql_stmt_close(sqlStatement);
    }
    delete [] paramLength;

    return returnStatus;
}

bool MySQL_Query::GetResults(std::map<std::string,std::string>& results)
{
    results.clear();

    if ( 2 != m_columnCount )
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

bool MySQL_Query::GetMultiColumnResults(MySQL_QueryResults& results)
{
    results = m_queryResults;
    return true;
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
