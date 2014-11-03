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

#include <iostream>
#include <vector>

#include "sqlbinding.h"

// Define single global copy (intended as a singleton class)
MySQL_Factory* g_pFactory = NULL;

// *TODO* Derive from SCXException if we can use PAL code in this project
class SQLError
{
public:
    SQLError() { m_label = "Generic Error"; }
    ~SQLError() { }
    SQLError(const char *message) { m_label = message; }
    inline const char* GetMessage(void) { return m_label.c_str(); }

private:
    std::string m_label;
};



MySQL_Dependencies::~MySQL_Dependencies()
{
    Detach();
}

bool MySQL_Dependencies::Attach()
{
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
            throw SQLError( mysql_error(m_sqlConnection) );

        m_infoConnection = mysql_get_host_info( m_sqlConnection );
        m_infoClient = mysql_get_client_info();
        m_infoServer = mysql_get_server_info( m_sqlConnection );
    }
    catch ( SQLError e )
    {
        // *TODO* Log Message!
        std::cerr << e.GetMessage() << std::endl;
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
            throw SQLError( mysql_error(sqlConnection) );
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
    catch ( SQLError e )
    {
        m_sqlErrorText = e.GetMessage();
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



// Get system host name (via low-level system call)
//
// *TODO*
// Butchered from scxnameresolver.cpp in the PAL; remove this if we include PAL

bool GetHostname( std::string& hostname )
{
    bool found = false;
    hostname.clear();

    // First determine the maximum size of the host name

    size_t size = 257;

    long sysSize = sysconf(_SC_HOST_NAME_MAX);
    if( (-1 != sysSize) && (size < (size_t)sysSize ) && (sysSize > 0) )
    {
        size = sysSize + 1;
    }

    std::vector<char> buf; 
    buf.resize(size, 0);

    // *TODO* Log something here if gethostname underlying call fails ...
    int rc = gethostname(&buf[0], size);
    if(0 == rc)
    {
        hostname = std::string( &buf[0] );
        found = true;
    }

    return found;
}

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
