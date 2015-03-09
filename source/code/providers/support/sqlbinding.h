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
    MySQL_Dependencies()
    : m_sqlConnection(NULL),
      m_log(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.binding.dependencies")),
      m_sqlPort(0),
      m_sqlConnectFlags(0),
      m_sqlErrorNum(0)
    {}
    virtual ~MySQL_Dependencies();

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
    bool Attach();
    bool AttachUsingStoredCredentials(unsigned int port,
                                      util::unique_ptr<MySQL_Authentication>& auth,
                                      const std::string& database = "");
    bool Detach();
    void AllowStoredProcedures() { m_sqlConnectFlags = CLIENT_MULTI_RESULTS; }

    const std::string& GetErrorText() const { return m_sqlErrorText; }
    const std::string& GetErrorState() const { return m_sqlState; }
    unsigned int GetErrorNum() const { return m_sqlErrorNum; }

    const std::string& GetConnectionInfo() const { return m_infoConnection; }
    const std::string& GetClientInfo() const { return m_infoClient; }
    const std::string& GetServerInfo() const { return m_infoServer; }

private:
    MYSQL *m_sqlConnection;
    SCXCoreLib::SCXLogHandle m_log;

    unsigned int m_sqlPort;
    std::string m_sqlHostName;
    std::string m_sqlUserID;
    std::string m_sqlPassword;
    std::string m_sqlDatabase;
    unsigned long m_sqlConnectFlags;

    std::string m_sqlErrorText;
    std::string m_sqlState;
    unsigned int m_sqlErrorNum;

    std::string m_infoConnection;
    std::string m_infoClient;
    std::string m_infoServer;

    friend class MySQL_Query_Rows;
    friend class MySQL_Stored_Procedure_Test;
};



/*------------------------------------------------------------------------------*/
/**
 *   MySQL_Query
 *   Helper class to execute a query against a MySQL database
 *
 *   Note: the MySQL provider generally looks up key:value associations from the
 *   database (i.e. "show global status" and such). This class is optimized for
 *   that, and won't work well with queries that don't return two columns.
 *
 *   This class is "plugged in" to the class factory. Be sure to connect to a
 *   database prior to using this class, and be sure to instanciate this class
 *   via the class factory.
 */

const unsigned int COLUMN_MAXLEN = 256; /* Arbitrary value; raise if needed */
typedef std::map< std::string, std::vector<std::string> > MySQL_QueryResults;

class MySQL_Query_Base
{
public:
    explicit MySQL_Query_Base() : m_sqlErrorNum(0) {}
    virtual ~MySQL_Query_Base() {}

    virtual const std::string& GetErrorText() const { return m_sqlErrorText; }
    virtual const std::string& GetErrorState() const { return m_sqlState; }
    virtual unsigned int GetErrorNum() const { return m_sqlErrorNum; }

protected:
    std::string m_sqlErrorText;
    std::string m_sqlState;
    unsigned int m_sqlErrorNum;
};

class MySQL_Query_Rows : public MySQL_Query_Base
{
public:
    explicit MySQL_Query_Rows(SCXCoreLib::SCXHandle<MySQL_Dependencies> deps)
    : m_log(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.query.rows")), m_deps(deps),
      m_sqlStatement(NULL), m_bindInParamLength(NULL),
      m_bindOutParams(NULL), m_bindOutResultData(NULL), m_bindOutParamLength(NULL),
      m_fQueryForResults(false), m_columnCount(0)
    { }
    virtual ~MySQL_Query_Rows();
    virtual void Reset();

    virtual bool ExecuteQuery( const char* query, const std::vector<std::string>& parameters );
    virtual unsigned int GetColumnCount() const { return m_columnCount; }

    virtual bool GetColumnNames( std::vector<std::string>& columnNames );
    virtual bool GetNextRow( std::vector<std::string>& columns );

protected:
    SCXCoreLib::SCXLogHandle m_log;
    SCXCoreLib::SCXHandle<MySQL_Dependencies> m_deps;

    MYSQL_STMT* m_sqlStatement;
    long unsigned int* m_bindInParamLength;

    MYSQL_BIND* m_bindOutParams;
    char *m_bindOutResultData;
    long unsigned int* m_bindOutParamLength;

    bool m_fQueryForResults;
    unsigned int m_columnCount;
};

class MySQL_Query : public MySQL_Query_Base
{
public:
    explicit MySQL_Query(SCXCoreLib::SCXHandle<MySQL_Dependencies> deps)
    : m_rowHandler(deps),
      m_log(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.query.sets")),
      m_deps(deps)
    { }
    virtual ~MySQL_Query() {}

    virtual bool ExecuteQuery( const char* query );
    virtual bool ExecuteQuery( const char* query, const std::vector<std::string>& parameters );

    virtual bool GetResults(std::map<std::string, std::string>& results);
    virtual bool GetMultiColumnResults(MySQL_QueryResults& results) const;
    virtual const std::vector<std::string>& GetColumnNames() const { return m_columnNames; }

private:
    MySQL_Query_Rows m_rowHandler;
    SCXCoreLib::SCXLogHandle m_log;
    SCXCoreLib::SCXHandle<MySQL_Dependencies> m_deps;

    std::vector< std::string > m_columnNames;
    std::map< std::string, std::vector<std::string> > m_queryResults;
};



//
// MySQL_Binding
//
// Note: The Attach() method MUST be called, and MUST be checked for a valid
// return code. If Attach() is not called, or if it fails and queries are
// performed anyway, then failures will follow. Consider yourself warned!
//

class MySQL_Binding
{
public:
    explicit MySQL_Binding(SCXCoreLib::SCXHandle<MySQL_Dependencies> deps)
    : m_log(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.binding")), m_deps(deps)
    { }
    virtual ~MySQL_Binding();
    bool Attach(unsigned int port,
                const std::string& hostname,
                const std::string& username,
                const std::string& password,
                const std::string& database = "")
    { return m_deps->Attach(port, hostname, username, password, database); }
    bool Attach() { return m_deps->Attach(); }
    bool AttachUsingStoredCredentials(unsigned int port,
                                      util::unique_ptr<MySQL_Authentication>& auth,
                                      const std::string& database = "")
    { return m_deps->AttachUsingStoredCredentials(port, auth, database); }
    bool Detach() { return m_deps->Detach(); }
    void AllowStoredProcedures() { m_deps->AllowStoredProcedures(); }

    void GetConfigurationFilePaths( std::vector<std::string>& paths );

    const std::string& GetErrorText() { return m_deps->GetErrorText(); }
    const std::string& GetErrorState() { return m_deps->GetErrorState(); }
    unsigned int GetErrorNum() { return m_deps->GetErrorNum(); }

    const std::string& GetConnectionInfo() { return m_deps->GetConnectionInfo(); }
    const std::string& GetClientInfo() { return m_deps->GetClientInfo(); }
    const std::string& GetServerInfo() { return m_deps->GetServerInfo(); }

protected:

private:
    SCXCoreLib::SCXLogHandle m_log;
    SCXCoreLib::SCXHandle<MySQL_Dependencies> m_deps;
};



//
// MySQL Class Factory
//
// Allows contruction of MySQL_Binding class.
// This allows us to replace the factory for dependency injection purposes.
//

class MySQL_Factory
{
public:
    MySQL_Factory() {}
    virtual ~MySQL_Factory()
    {
        m_deps = NULL;
        m_binding = NULL;
        m_authDeps = NULL;
    }

    // This returns a unique_ptr to the MySQL_Binding class to guarantee destruction
    //
    // Use this with code like:
    //   unique_ptr<MySQL_Binding> pBinding(g_pFactory->GetBinding());
    //   pBinding->BindingMethod(...);
    virtual util::unique_ptr<MySQL_Binding>::move_type GetBinding()
    {
        util::unique_ptr<MySQL_Binding> pBinding (new MySQL_Binding(GetDependencies()));
        return pBinding.move();
    }

    // This returns a unique_ptr to the MySQL_Query class to guarantee destruction
    //
    // Use this with code like:
    //   unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());
    //   pQuery->QueryMethod(...);
    virtual util::unique_ptr<MySQL_Query>::move_type GetQuery()
    {
        util::unique_ptr<MySQL_Query> pQuery (new MySQL_Query(GetDependencies()));
        return pQuery.move();
    }

    // This returns a unique_ptr to the MySQL_Query_Rows class to guarantee destruction
    //
    // Use this with code like:
    //   unique_ptr<MySQL_Query_Rows> pQuery(g_pFactory->GetQueryByRow());
    //   pQuery->QueryMethod(...);
    virtual util::unique_ptr<MySQL_Query_Rows>::move_type GetQueryByRow()
    {
        util::unique_ptr<MySQL_Query_Rows> pQuery (new MySQL_Query_Rows(GetDependencies()));
        return pQuery.move();
    }

    // This returns a unique_ptr to the MySQL_Authentication class to guarantee destruction
    //
    // Use this with code like:
    //   unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
    //   pQuery->QueryMethod(...);
    virtual util::unique_ptr<MySQL_Authentication>::move_type GetAuthentication()
    {
        util::unique_ptr<MySQL_Authentication> pAuth (new MySQL_Authentication(GetAuthDependencies()));
        return pAuth.move();
    }

protected:
    // Production code doesn't need to get dependencies (factory handles this)
    virtual SCXCoreLib::SCXHandle<MySQL_Dependencies> GetDependencies()
    {
        if (NULL == m_deps)
        {
            m_deps = SCXCoreLib::SCXHandle<MySQL_Dependencies>(new MySQL_Dependencies());
        }

        return m_deps;
    }

    virtual SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> GetAuthDependencies()
    {
        if (NULL == m_authDeps)
        {
            m_authDeps = SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_AuthenticationDependencies());
        }

        return m_authDeps;
    }

protected:
    SCXCoreLib::SCXHandle<MySQL_Dependencies> m_deps;
    SCXCoreLib::SCXHandle<MySQL_Binding> m_binding;

    SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> m_authDeps;

    friend class MySQL_Stored_Procedure_Test;
};

// Define single global copy (intended as a singleton class)
extern SCXCoreLib::SCXHandle<MySQL_Factory> g_pFactory;



//
// Map access functions
//

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

// Get Unsigned value from map
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

// Return sum of values in a map starting with a known string (returns number of matches)
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

// Get string value from map
bool GetStrValue(const std::map<std::string, std::string>& mymap, const std::string keyName, std::string& value);



//
// The providers should have an exception handler wrapping all activity.  This
// helps guarantee that the agent won't crash if there's an unhandled exception.
// In the Pegasus model, this was done in the base class.  Since we don't have
// that luxury here, we'll have macros to make it easier.
//
// PEX = Provider Exception
//
// There's an assumption here that, since this is used in the OMI-generated code,
// "context" always exists for posting the result to.
//

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

//
// Have a little function to make it easy to break into a provider (as a debugging aid)
//
// The idea here is that we sleep indefinitely; if you break in with a debugger, then
// you can set f_break to true and then step through the code.
//

#define CIM_PROVIDER_WAIT_FOR_ATTACH         \
    {                                        \
        volatile bool f_break = false;       \
        while ( !f_break )                   \
            sleep(1);                        \
    }

#endif /* SQLBINDING_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
