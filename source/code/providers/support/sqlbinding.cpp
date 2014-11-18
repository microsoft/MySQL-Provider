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

#include "sqlbinding.h"

// Define single global copy (intended as a singleton class)
MySQL_Factory* g_pFactory = NULL;

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
    m_sqlState.clear();
    m_sqlErrorText.clear();
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
            NULL, /* No database connection */
            0,
            NULL,
            0 );

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
    // Clear the prior results, if any
    m_queryResults.clear();
    m_sqlErrorText.clear();
    m_sqlState.clear();
    m_sqlErrorNum = 0;

    try
    {
        MYSQL * sqlConnection = m_deps->m_sqlConnection;

        if ( NULL == sqlConnection )
        {
            m_sqlErrorText = "Attach() not called; not connected to a server";
            return false;
        }

        int sqlStatus = mysql_query( sqlConnection, query );
        if ( sqlStatus )
        {
            m_sqlErrorText = mysql_error(sqlConnection);
            m_sqlState = mysql_sqlstate(sqlConnection);
            m_sqlErrorNum = mysql_errno(sqlConnection);

            throw SQLError( mysql_error(sqlConnection), SCXSRCLOCATION );
        }

        // Get the result set
        MYSQL_RES *sqlResult = mysql_store_result( sqlConnection );
        if ( NULL == sqlResult )
        {
            // Query was valid, but no rows were returned

            m_sqlErrorText = "Result set is empty";
            return false;
        }

        if ( 2 != mysql_num_fields(sqlResult) )
        {
            // We didn't get two columns of information back from query

            m_sqlErrorText = "Result set did not contain two columns of data";
            mysql_free_result(sqlResult);
            return false;
        }

        MYSQL_ROW sqlRow;
        while ( NULL != (sqlRow = mysql_fetch_row(sqlResult)) )
        {
            // Get the key (in lower case)
            std::string key = sqlRow[0];
            std::transform(key.begin(), key.end(), key.begin(), ::tolower);

            if ( m_queryResults.count(key) > 0 )
            {
                m_sqlErrorText = "Duplicate result " + key + " returned in result set";
                mysql_free_result(sqlResult);
                m_queryResults.clear();
                return false;
            }

            m_queryResults[key] = sqlRow[1];
        }

        mysql_free_result(sqlResult);
    }
    catch ( SQLError& e )
    {
        m_sqlErrorText = SCXCoreLib::StrToUTF8( e.What() );
        return false;
    }

    return true;
}



MySQL_Binding::~MySQL_Binding()
{
    Detach();

    // Note: We don't "own" pointer to dependencies; this is owned by the factory
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
