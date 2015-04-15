/*--------------------------------------------------------------------------------
 *        Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *     
 *        */
 /**
      \file        sqlbinding.h

      \brief       Provider helper functions for MySQL bindings and access

      \date        10-28-14
*/
/*----------------------------------------------------------------------------*/

#ifndef SQLBINDING_H
#define SQLBINDING_H

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxhandle.h>
#include <scxcorelib/scxlog.h>
#include <util/unique_ptr.h>

#include <map>
#include <mysql.h>
#include <sstream>
#include <stdint.h>
#include <string>

#include "sqlauth.h"



/*
 * Define constants for MySQL_Binding authentication
 */

#define MYSQL_AUTH_EXCEPTION            5000
#define MYSQL_AUTH_INVALID_ENTRY        5001



/*------------------------------------------------------------------------------*/
/**
 *   MySQL_Dependencies
 *   Helper class to help with access to MySQL Database
 */

class MySQL_Dependencies
{
public:
    //! Ctor
    MySQL_Dependencies()
    : m_sqlConnection(NULL),
      m_log(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.binding.dependencies")),
      m_sqlPort(0),
      m_sqlConnectFlags(0),
      m_sqlErrorNum(0)
    {}

    //! Dtor
    virtual ~MySQL_Dependencies();

    /**
       Attach to a MySQL Instance as specified by parameters

       \param[in]  Port      Port number for the MySQL Instance
       \param[in]  Hostname  Bind adress for the MySQL Instance
       \param[in]  Username  Username for the MySQL Instance
       \param[in]  Password  Password for the MySQL Instance
       \param[in]  Database  (Optional) Database to bind to, or none of not specified
       \returns    True if attach was successful, false otherwise

    */
    bool Attach(unsigned int port,
                const std::string& hostname,
                const std::string& username,
                const std::string& password,
                const std::string& database = "" /* No database by default */ )
    {
        m_sqlPort = port;
        m_sqlHostName = hostname;
        m_sqlUserID = username;
        m_sqlPassword = password;
        m_sqlDatabase = database;

        return Attach();
    }

    /**
       Attach to a MySQL Instance as stored by the dependency object

       Port nubmer, bind address, username, password, and database are already stored in object.

       \returns    True if attach was successful, false otherwise

    */
    bool Attach();

    /**
       Attach to a MySQL Instance via an entry in the provider authentication file

       \param[in]  Port      Port number for the MySQL Instance
       \param[in]  auth      Authentication object representing authentication file
       \param[in]  database  Database to bind to
       \returns    True if attach was successful, false otherwise

    */
    bool AttachUsingStoredCredentials(unsigned int port,
                                      util::unique_ptr<MySQL_Authentication>& auth,
                                      const std::string& database = "");

    /**
       Detach from MySQL instance (if currently attached)

       \returns    True

    */
    bool Detach();

    /**
       Allow stored procedure calls to be made for a query

       Calling this method will allow query engine to call a stored procedure.
       Otherwise, MySQL engine will return an error.

    */
    void AllowStoredProcedures() { m_sqlConnectFlags = CLIENT_MULTI_RESULTS; }

    /**
       Get MySQL error text describing MySQL error

       \returns    MySQL error text

    */
    const std::string& GetErrorText() const { return m_sqlErrorText; }

    /**
       Get MySQL error state describing MySQL error

       \returns    MySQL error state

    */
    const std::string& GetErrorState() const { return m_sqlState; }

    /**
       Get MySQL error number describing MySQL error

       \returns    MySQL error number

    */
    unsigned int GetErrorNum() const { return m_sqlErrorNum; }

    /**
       Get MySQL connection inforamtion

       \returns    MySQL connection information

    */
    const std::string& GetConnectionInfo() const { return m_infoConnection; }

    /**
       Get MySQL client version information

       \returns    MySQL client version information

    */
    const std::string& GetClientInfo() const { return m_infoClient; }

    /**
       Get MySQL server version information

       \returns    MySQL server version information

    */
    const std::string& GetServerInfo() const { return m_infoServer; }

private:
    MYSQL *m_sqlConnection;             //!< MySQL connection object
    SCXCoreLib::SCXLogHandle m_log;     //!< Log handle

    unsigned int m_sqlPort;             //!< Port number to connect to for MySQL instance
    std::string m_sqlHostName;          //!< Bind address to connect to for MySQL instance
    std::string m_sqlUserID;            //!< Username to connect to for MySQL instance
    std::string m_sqlPassword;          //!< Password to connect to for MySQL instance
    std::string m_sqlDatabase;          //!< Database to bind to ("" for no database binding)
    unsigned long m_sqlConnectFlags;    //!< Options when connecting to MySQL instance

    std::string m_sqlErrorText;         //!< MySQL error text from MySQL client library
    std::string m_sqlState;             //!< MySQL error state from MySQL client library
    unsigned int m_sqlErrorNum;         //!< MySQL error number from MySQL client library

    std::string m_infoConnection;       //!< MySQL connection information
    std::string m_infoClient;           //!< MySQL client version information
    std::string m_infoServer;           //!< MySQL server version information

    friend class MySQL_Query_Rows;
    friend class MySQL_Stored_Procedure_Test;
};



/*------------------------------------------------------------------------------*/
/**
 *   MySQL_Query_Base
 *   Base class to provide error fetch routines from MySQL database
 *
 */

class MySQL_Query_Base
{
public:
    //! Ctor
    explicit MySQL_Query_Base() : m_sqlErrorNum(0) {}
    //! Dtor
    virtual ~MySQL_Query_Base() {}

    /**
       Get MySQL error text describing MySQL error

       \returns    MySQL error text

    */
    virtual const std::string& GetErrorText() const { return m_sqlErrorText; }

    /**
       Get MySQL error state describing MySQL error

       \returns    MySQL error state

    */
    virtual const std::string& GetErrorState() const { return m_sqlState; }

    /**
       Get MySQL error number describing MySQL error

       \returns    MySQL error number

    */
    virtual unsigned int GetErrorNum() const { return m_sqlErrorNum; }

protected:
    std::string m_sqlErrorText;         //!< MySQL error text
    std::string m_sqlState;             //!< MySQL error state
    unsigned int m_sqlErrorNum;         //!< MySQL error number
};

const unsigned int COLUMN_MAXLEN = 256; //!< Max column length (Arbitrary value; raise if needed)

/*------------------------------------------------------------------------------*/
/**
 *   MySQL_Query_Rows: Execute a query against a MySQL database
 *
 *   This class is responsible for implementing queries against a MySQL Database.
 *
 *   IMPORTANT: This class is responsible for avoiding SQL injection attacks in
 *   conjunction with callers. Callers are responsible for escaping queries for
 *   proper behavior, but even if not escaped, this class MUST be implemented to
 *   not allow for muliple SQL statements per query, or other forms of SQL
 *   injection attacks.
 *
 *   This class implements a "blind" fetch-row type interface, with no knowledge
 *   about the type of data being fetched from the database. Note, however, that
 *   this class will return all fields as strings (numeric fields are converted
 *   to strings as needed).
 *
 *   This class is "plugged in" to the class factory. Be sure to connect to a
 *   database prior to using this class, and be sure to instanciate this class
 *   via the class factory.
 */

class MySQL_Query_Rows : public MySQL_Query_Base
{
public:
    //! Ctor
    explicit MySQL_Query_Rows(SCXCoreLib::SCXHandle<MySQL_Dependencies> deps)
    : m_log(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.query.rows")), m_deps(deps),
      m_sqlResult(NULL), m_fQueryForResults(false), m_columnCount(0)
    { }
    //! Dtor
    virtual ~MySQL_Query_Rows();
    //! Free any memory from MySQL query and reset for new query
    virtual void Reset();

    /**
       Helper method to escape a query string to help protect against SQL injection attacks

       \param[in]  query     Original query to execute
       \returns    Escaped query (single & double quotes and other special charaters escaped)

    */
    virtual const std::string EscapeQuery( const std::string& query );

    /**
       Execute a query against the current MySQL connection

       If this method returns "true", then other methods (i.e. GetNextRow)
       should be called to actually retrieve data from the database.

       \param[in]  query        Query to execute
       \param[in]  queryLength  Length of query string (zero if unknown)
       \returns    true if query was successfully executed, false otherwise

    */
    virtual bool ExecuteQuery( const char* query, unsigned int queryLength = 0 );

    /**
       Get number of columns returned from currently executing query

       \returns    Column count

    */
    virtual unsigned int GetColumnCount() const { return m_columnCount; }

    /**
       Get column names returned from currently executing query

       \param[out] columnNames  Column name for each column (count == GetColumnCount())
       \returns    true if columnNames populated, false otherwise

    */
    virtual bool GetColumnNames( std::vector<std::string>& columnNames );

    /**
       Get next row from the currently executing MySQL query

       \param[out] columns      Vector of column data representing the next row of data
       \returns    true if a valid row was returned, false if no more rows exist

    */
    virtual bool GetNextRow( std::vector<std::string>& columns );

protected:
    SCXCoreLib::SCXLogHandle m_log;     //!< Log handle
    SCXCoreLib::SCXHandle<MySQL_Dependencies> m_deps; //!< Dependency object

    MYSQL_RES* m_sqlResult;             //!< MySQL pointer to result structure

    bool m_fQueryForResults;            //!< Should more rows be queried for?
    unsigned int m_columnCount;         //!< Number of columns returned from query
};

/*------------------------------------------------------------------------------*/
/**
 *   MySQL_Query: Execute a query against a MySQL database
 *
 *   Note: the MySQL provider generally looks up key:value associations from the
 *   database (i.e. "show global status" and such). This class is optimized for
 *   that, and won't work well with queries that don't return two columns.
 *
 *   This class is "plugged in" to the class factory. Be sure to connect to a
 *   database prior to using this class, and be sure to instanciate this class
 *   via the class factory.
 */

typedef std::map< std::string, std::vector<std::string> > MySQL_QueryResults;

class MySQL_Query : public MySQL_Query_Base
{
public:
    //! Ctor
    explicit MySQL_Query(SCXCoreLib::SCXHandle<MySQL_Dependencies> deps)
    : m_rowHandler(deps),
      m_log(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.query.sets")),
      m_deps(deps)
    { }
    //! Dtor
    virtual ~MySQL_Query() {}

    /**
       Helper method to escape a query string to help protect against SQL injection attacks

       \param[in]  query     Original query to execute
       \returns    Escaped query (single & double quotes and other special charaters escaped)

    */
    virtual const std::string EscapeQuery( const std::string& query )
    {
        return m_rowHandler.EscapeQuery(query);
    }

    /**
       Execute a query against the current MySQL connection

       If this method returns "true", then other methods (i.e. GetResults or
       GetMultiColumnResults) should be called to actually retrieve data from
       the database.

       \param[in]  query        Query to execute
       \param[in]  queryLength  Length of query string (zero if unknown)
       \returns    true if query was successfully executed, false otherwise

    */
    virtual bool ExecuteQuery( const char* query, unsigned int queryLength = 0 );

    /**
       Fetch results from the database as a dictionary (easiest for
       "show variables" or "show global status" queries).

       \param[out] results      Result dictionary for query results
       \returns    true if query was returned successfully, false otherwise

    */
    virtual bool GetResults(std::map<std::string, std::string>& results);

    /**
       Fetch results from the database as a dictionary/vector.  This
       works well if more than two columns are returned, but the first
       column serves as a "key" to fetch data from the dictionary.

       \param[out] results      Result dictionary for query results
       \returns    true if query was returned successfully, false otherwise

    */
    virtual bool GetMultiColumnResults(MySQL_QueryResults& results) const;

    /**
       Get column names returned from currently executing query

       \returns    Column name for each column

    */
    virtual const std::vector<std::string>& GetColumnNames() const { return m_columnNames; }

private:
    MySQL_Query_Rows m_rowHandler;      //!< Row handler class implementation
    SCXCoreLib::SCXLogHandle m_log;     //!< Log handle
    SCXCoreLib::SCXHandle<MySQL_Dependencies> m_deps; //!< Dependency cklass

    std::vector< std::string > m_columnNames; //!< Column names for query results
    std::map< std::string, std::vector<std::string> > m_queryResults; //!< Query results
};



/*------------------------------------------------------------------------------*/
/**
 *   MySQL_Binding
 *
 *   Note: The Attach() method MUST be called, and MUST be checked for a valid
 *   return code. If Attach() is not called, or if it fails and queries are
 *   performed anyway, then failures will follow. Consider yourself warned!
 *
 *   This class is "plugged in" to the class factory. Be sure to instanciate
 *   this class via the class factory.
 */

class MySQL_Binding
{
public:
    //! Ctor
    explicit MySQL_Binding(SCXCoreLib::SCXHandle<MySQL_Dependencies> deps)
    : m_log(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.binding")), m_deps(deps)
    { }
    //! Dtor
    virtual ~MySQL_Binding();

    /**
       Attach to a MySQL Instance as specified by parameters

       \param[in]  Port      Port number for the MySQL Instance
       \param[in]  Hostname  Bind adress for the MySQL Instance
       \param[in]  Username  Username for the MySQL Instance
       \param[in]  Password  Password for the MySQL Instance
       \param[in]  Database  (Optional) Database to bind to, or none of not specified
       \returns    True if attach was successful, false otherwise

    */
    bool Attach(unsigned int port,
                const std::string& hostname,
                const std::string& username,
                const std::string& password,
                const std::string& database = "")
    { return m_deps->Attach(port, hostname, username, password, database); }

    /**
       Attach to a MySQL Instance as stored by the dependency object

       Port nubmer, bind address, username, password, and database are already stored in object.

       \returns    True if attach was successful, false otherwise

    */
    bool Attach() { return m_deps->Attach(); }

    /**
       Attach to a MySQL Instance via an entry in the provider authentication file

       \param[in]  Port      Port number for the MySQL Instance
       \param[in]  auth      Authentication object representing authentication file
       \param[in]  database  Database to bind to
       \returns    True if attach was successful, false otherwise

    */
    bool AttachUsingStoredCredentials(unsigned int port,
                                      util::unique_ptr<MySQL_Authentication>& auth,
                                      const std::string& database = "")
    { return m_deps->AttachUsingStoredCredentials(port, auth, database); }

    /**
       Detach from MySQL instance (if currently attached)

       \returns    True

    */
    bool Detach() { return m_deps->Detach(); }

    /**
       Allow stored procedure calls to be made for a query

       Calling this method will allow query engine to call a stored procedure.
       Otherwise, MySQL engine will return an error.

    */
    void AllowStoredProcedures() { m_deps->AllowStoredProcedures(); }

    /**
        Return a list of potential locations for MySQL configuration file.

        Note: This list should be returned in "priority" order (i.e. in order
        of what to check first, what to check next, etc). When looking at the
        various MySQL configuration files, the first path we find "wins".

        \param[out] paths List of MySQL server configuration paths (absolute paths)

    */
    void GetConfigurationFilePaths( std::vector<std::string>& paths );

    /**
       Get MySQL error text describing MySQL error

       \returns    MySQL error text

    */
    const std::string& GetErrorText() { return m_deps->GetErrorText(); }

    /**
       Get MySQL error state describing MySQL error

       \returns    MySQL error state

    */
    const std::string& GetErrorState() { return m_deps->GetErrorState(); }

    /**
       Get MySQL error number describing MySQL error

       \returns    MySQL error number

    */
    unsigned int GetErrorNum() { return m_deps->GetErrorNum(); }

    /**
       Get MySQL connection inforamtion

       \returns    MySQL connection information

    */
    const std::string& GetConnectionInfo() { return m_deps->GetConnectionInfo(); }

    /**
       Get MySQL client version information

       \returns    MySQL client version information

    */
    const std::string& GetClientInfo() { return m_deps->GetClientInfo(); }

    /**
       Get MySQL server version information

       \returns    MySQL server version information

    */
    const std::string& GetServerInfo() { return m_deps->GetServerInfo(); }

protected:

private:
    SCXCoreLib::SCXLogHandle m_log;     //!< Log handle
    SCXCoreLib::SCXHandle<MySQL_Dependencies> m_deps; //!< Dependency object
};



/*------------------------------------------------------------------------------*/
/**
 *   MySQL Class Factory
 *
 *   Allows construction of MySQL_Binding classes, as well as other classes, to
 *   perform operations against a MySQL instance.
 *
 *   This class allows us to replace the factory for dependency injection purposes.
 */

class MySQL_Factory
{
public:
    //! Ctor
    MySQL_Factory() {}
    //! Dtor
    virtual ~MySQL_Factory()
    {
        m_deps = NULL;
        m_binding = NULL;
        m_authDeps = NULL;
    }

    /**
       This returns a unique_ptr to the MySQL_Binding class to guarantee destruction

       Use this with code like:
         unique_ptr<MySQL_Binding> pBinding(g_pFactory->GetBinding());
         pBinding->BindingMethod(...);
    */
    virtual util::unique_ptr<MySQL_Binding>::move_type GetBinding()
    {
        util::unique_ptr<MySQL_Binding> pBinding (new MySQL_Binding(GetDependencies()));
        return pBinding.move();
    }

    /**
       This returns a unique_ptr to the MySQL_Query class to guarantee destruction

       Use this with code like:
         unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());
         pQuery->QueryMethod(...);
    */
    virtual util::unique_ptr<MySQL_Query>::move_type GetQuery()
    {
        util::unique_ptr<MySQL_Query> pQuery (new MySQL_Query(GetDependencies()));
        return pQuery.move();
    }

    /**
       This returns a unique_ptr to the MySQL_Query_Rows class to guarantee destruction

       Use this with code like:
         unique_ptr<MySQL_Query_Rows> pQuery(g_pFactory->GetQueryByRow());
         pQuery->QueryMethod(...);
    */
    virtual util::unique_ptr<MySQL_Query_Rows>::move_type GetQueryByRow()
    {
        util::unique_ptr<MySQL_Query_Rows> pQuery (new MySQL_Query_Rows(GetDependencies()));
        return pQuery.move();
    }

    /**
       This returns a unique_ptr to the MySQL_Authentication class to guarantee destruction

       Use this with code like:
         unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
         pQuery->QueryMethod(...);
    */
    virtual util::unique_ptr<MySQL_Authentication>::move_type GetAuthentication()
    {
        util::unique_ptr<MySQL_Authentication> pAuth (new MySQL_Authentication(GetAuthDependencies()));
        return pAuth.move();
    }

protected:
    /**
       Get dependency injection object

       Note:  Production code doesn't need to get dependencies (factory handles this)
    */
    virtual SCXCoreLib::SCXHandle<MySQL_Dependencies> GetDependencies()
    {
        if (NULL == m_deps)
        {
            m_deps = SCXCoreLib::SCXHandle<MySQL_Dependencies>(new MySQL_Dependencies());
        }

        return m_deps;
    }

    /**
       Get authentication dependency injection object

       Note:  Production code doesn't need to get authentication dependencies (factory handles this)
    */
    virtual SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> GetAuthDependencies()
    {
        if (NULL == m_authDeps)
        {
            m_authDeps = SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_AuthenticationDependencies());
        }

        return m_authDeps;
    }

protected:
    SCXCoreLib::SCXHandle<MySQL_Dependencies> m_deps;   //!< Handle to dependency object
    SCXCoreLib::SCXHandle<MySQL_Binding> m_binding;     //!< Handle to binding object

    SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> m_authDeps; //!< Handle to authentication object

    friend class MySQL_Stored_Procedure_Test;
};

extern SCXCoreLib::SCXHandle<MySQL_Factory> g_pFactory; //!< Define single global copy (intended as a singleton class)



/*------------------------------------------------------------------------------*/
/*
 *   Map access functions
 *
 */

/**
   Helper function: Convert string value to unsigned value

   \param[in]  strNum    String representation of numeric value
   \param[out] value     Value to return numeric value in
   \returns    True if conversion was successful, false otherwise

*/
template <typename T> bool ConvertToUnsigned(const std::string& strNum, T& value)
{
    try {
        value = SCXCoreLib::StrToUInt( SCXCoreLib::StrFromUTF8(strNum) );
    }
    catch (SCXCoreLib::SCXNotSupportedException& e)
    {
        SCXCoreLib::SCXLogHandle hLog = SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.binding.utils");
        SCX_LOGERROR(hLog, std::wstring(L"Cannot parse unsigned value - ").append(SCXCoreLib::StrFromUTF8(strNum)));
        return false;
    }

    return true;
}

/**
   Get unsigned value from a dictionary (map)

   \param[in]  myMap     Map that contains key/value pairs to find
   \param[in]  keyName   Name of key to find within the map
   \param[out] value     Value to return numeric value in
   \param[in]  fWarn     Log warnings upon conversion errors
   \returns    True if conversion was successful, false otherwise

*/
template <typename T> bool GetUValue(const std::map<std::string, std::string>& mymap, const std::string keyName, T& value, bool fWarn = false)
{
    std::map<std::string, std::string>::const_iterator it = mymap.find(keyName);
    if ( mymap.end() == it )
    {
        if ( fWarn )
        {
            SCXCoreLib::SCXLogHandle hLog = SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.provider.support");
            SCX_LOGWARNING(hLog, "MySQL result set did not contain \"" + keyName + "\" in the result set" );
        }
        return false;
    }

    return ConvertToUnsigned(it->second, value);
}

/**
   Return sum of values in a map starting with a known string (returns number of matches)

   \param[in]  myMap        Map that contains key/value pairs to find
   \param[in]  startsWith   Starting contents of key to match against
   \param[out] value        Value to return numeric value in
   \returns    Count of keys that were considered in the match

*/
template <typename T> int AddValues(const std::map<std::string, std::string>& mymap, const char* startsWith, T& value)
{
    int count = 0;
    value = 0;

    for (std::map<std::string, std::string>::const_iterator it = mymap.begin(); it != mymap.end(); ++it)
    {
        // Does the key begin with what we were passed?
        if ( 0 == it->first.find(startsWith) )
        {
            uint32_t temp;

            if ( ConvertToUnsigned(it->second, temp) )
            {
                count++;
                value += temp;
            }
        }
    }

    return count;
}

/**
   Get string value from map

   \param[in]  myMap     Map that contains key/value pairs to find
   \param[in]  keyName   Name of key to find within the map
   \param[out] value     Value from the map
   \returns    True if key was found, false otherwise

*/
bool GetStrValue(const std::map<std::string, std::string>& mymap, const std::string keyName, std::string& value);



/*------------------------------------------------------------------------------*/
/*
 *   Helper definitions for exception handling
 *
 *   The providers should have an exception handler wrapping all activity.  This
 *   helps guarantee that the agent won't crash if there's an unhandled exception.
 *   In the Pegasus model, this was done in the base class.  Since we don't have
 *   that luxury here, we'll have macros to make it easier.
 *
 *   PEX = Provider Exception
 *
 *   There's an assumption here that, since this is used in the OMI-generated code,
 *   "context" always exists for posting the result to.
 *
 */

#define CIM_PEX_BEGIN \
    try

#define CIM_PEX_END(module, log) \
    catch (const SCXCoreLib::SCXException& e) \
    { \
        SCX_LOGWARNING((log), std::wstring(module).append(L" - "). \
                       append(e.What()).append(L" - ").append(e.Where())); \
        context.Post(MI_RESULT_FAILED); \
    } \
    catch (std::exception &e) { \
        SCX_LOGERROR((log), std::wstring(module).append(L" - ").append(SCXCoreLib::DumpString(e))); \
        context.Post(MI_RESULT_FAILED); \
    } \
    catch (...) \
    { \
        SCX_LOGERROR((log), std::wstring(module).append(L" - Unknown exception")); \
        context.Post(MI_RESULT_FAILED); \
    }

/*------------------------------------------------------------------------------*/
/*
 *
 *   Have a little function to make it easy to break into a provider (as a debugging aid)
 *
 *   The idea here is that we sleep indefinitely; if you break in with a debugger, then
 *   you can set f_break to true and then step through the code.
 *
 */

#define CIM_PROVIDER_WAIT_FOR_ATTACH         \
    {                                        \
        volatile bool f_break = false;       \
        while ( !f_break )                   \
            sleep(1);                        \
    }

#endif /* SQLBINDING_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
