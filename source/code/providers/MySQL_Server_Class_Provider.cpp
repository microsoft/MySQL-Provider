/* @migen@ */
#include <MI.h>
#include "MySQL_Server_Class_Provider.h"

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxfile.h>
#include <scxcorelib/scxnameresolver.h>
#include <scxcorelib/stringaid.h>
#include <util/Base64Helper.h>

#include "sqlauth.h"
#include "logstartup.h"
#include "sqlbinding.h"

#include <errmsg.h>
#include <mysqld_error.h>



// Pick up specific definitions for new MySQL versions if we're on an older version

#if !defined(ER_BASE64_DECODE_ERROR)
#define ER_BASE64_DECODE_ERROR                  1575
#endif

#if !defined(ER_ACCESS_DENIED_NO_PASSWORD_ERROR)
#define ER_ACCESS_DENIED_NO_PASSWORD_ERROR      1698
#endif

using namespace SCXCoreLib;

MI_BEGIN_NAMESPACE

static std::string FindConfigurationFile(
    util::unique_ptr<MySQL_Binding>& pBinding,
    util::unique_ptr<MySQL_Authentication>& pAuth)
{
    std::string configFile;
    if ( pAuth->GetAutomaticUpdates() )
    {
        std::vector<std::string> sqlPaths;
        pBinding->GetConfigurationFilePaths( sqlPaths );

        for (std::vector<std::string>::const_iterator it = sqlPaths.begin(); it != sqlPaths.end(); ++it)
        {
            if ( SCXFile::Exists(SCXFilePath(StrFromUTF8(*it))) )
            {
                configFile = *it;
                break;
            }
        }
    }

    return configFile;
}

static void EnumerateConnectionFailure(
    SCXLogHandle& hLog,
    util::unique_ptr<MySQL_Binding>& pBinding,
    MySQL_Server_Class& inst,
    unsigned int port,
    util::unique_ptr<MySQL_Authentication>& pAuth,
    const bool keysOnly,
    unsigned int sqlError)
{
    // The ProductID is the hostname:bind-address:port combination (assume no DB connection)
    NameResolver nr;
    std::string hostname( StrToUTF8(nr.GetHostname()) );

    MySQL_AuthenticationEntry entry;
    pAuth->GetEntry(port, entry);

    std::string productID = hostname + ":" + entry.binding + ":" + StrToUTF8(StrFrom(port));

    inst.ProductIdentifyingNumber_value( productID.c_str() );
    inst.ProductName_value( "MySQL" );
    inst.ProductVendor_value( "Oracle" );
    inst.ProductVersion_value( "" );
    inst.SystemID_value( "" );
    inst.CollectionID_value( "" );

    if ( !keysOnly )
    {
        // Try and find the configuration at a list of known locations
        std::string configFile( FindConfigurationFile(pBinding, pAuth) );
        if ( configFile.size() )
        {
            inst.ConfigurationFile_value( configFile.c_str() );
        }

        inst.Hostname_value( hostname.c_str() );
        inst.BindAddress_value( entry.binding.c_str() );
        inst.Port_value( port );

        const char *pStatus;
        switch (sqlError)
        {
            case ER_ABORTING_CONNECTION:        // 1152
                pStatus = "Aborted";
                break;

            case ER_CRASHED_ON_REPAIR:          // 1195
            case ER_WARN_QC_RESIZE:             // 1282
            case ER_INDEX_REBUILD:              // 1187
                pStatus = "Degraded";
                break;

            case ER_DBACCESS_DENIED_ERROR:      // 1044
            case ER_ACCESS_DENIED_ERROR:        // 1045
            case ER_SPECIFIC_ACCESS_DENIED_ERROR: // 1227
            case ER_CANNOT_USER:                // 1396
            case ER_BASE64_DECODE_ERROR:        // 1575
            case ER_ACCESS_DENIED_NO_PASSWORD_ERROR: // 1698
                pStatus = "Insufficient Privileges";
                break;

            case CR_CONNECTION_ERROR:           // 2002
            case CR_CONN_HOST_ERROR:            // 2003
                pStatus = "No Contact";
                break;

            case ER_SERVER_SHUTDOWN:            // 1053
            case ER_NORMAL_SHUTDOWN:            // 1077
                pStatus = "Stopping";
                break;

            case ER_CON_COUNT_ERROR:            // 1040
            case ER_OUT_OF_RESOURCES:           // 1041
            case ER_HOST_IS_BLOCKED:            // 1129
            case ER_CANT_CREATE_THREAD:         // 1135
            case ER_TOO_MANY_USER_CONNECTIONS:  // 1203
            case ER_FPARSER_TOO_BIG_FILE:       // 1340
                pStatus = "Stressed";
                break;

            case MYSQL_AUTH_EXCEPTION:          // (Internal)
            case MYSQL_AUTH_INVALID_ENTRY:      // (Internal)
                pStatus = "Supporting Entity in Error";
                break;

            default:
                pStatus = "Unknown";
        }

        inst.OperatingStatus_value( pStatus );
    }
}

static void EnumerateOneInstance(
    SCXLogHandle& hLog,
    MySQL_Server_Class& inst,
    unsigned int port,
    util::unique_ptr<MySQL_Authentication>& pAuth,
    const bool keysOnly)
{
    util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
    std::string strValue;

    // Attach to the MySQL database instance
    if ( !pBinding->AttachUsingStoredCredentials(port, pAuth) )
    {
        std::stringstream ss;
        ss << "Failure attaching to MySQL on port: " << port << ", Error "
           << pBinding->GetErrorNum() << ": " << pBinding->GetErrorText();
        SCX_LOGERROR(hLog, ss.str());

        EnumerateConnectionFailure(hLog, pBinding, inst, port, pAuth, keysOnly, pBinding->GetErrorNum());
        return;
    }

    // Execute a query to get the MySQL variables
    util::unique_ptr<MySQL_Query> pQuery( g_pFactory->GetQuery() );
    std::map<std::string, std::string> variables;
    if ( ! pQuery->ExecuteQuery("show variables") || ! pQuery->GetResults(variables) )
    {
        std::stringstream ss;
        ss << "Failure executing query \"show variables\" against MySQL engine on port " << port
           << ", Error " << pQuery->GetErrorNum() << ": " << pQuery->GetErrorText();
        SCX_LOGERROR(hLog, ss.str());

        EnumerateConnectionFailure(hLog, pBinding, inst, port, pAuth, keysOnly, pQuery->GetErrorNum());
        return;
    }

    // The ProductID is the hostname:bind-address:port combination
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
        SCX_LOGERROR(hLog, StrAppend(L"Query \"show variables\" did not return \"port\" in the result set on port ", port));
        strPort = StrToUTF8(StrFrom(port));
    }
    std::string productID = hostname + ":" + entry.binding + ":" + strPort;

    inst.ProductIdentifyingNumber_value( productID.c_str() );
    inst.ProductName_value( "MySQL" );
    inst.ProductVendor_value( "Oracle" );

    if ( GetStrValue(variables, "version", strValue) )
    {
        inst.ProductVersion_value( strValue.c_str() );
    }

    if ( GetStrValue(variables, "server_id", strValue) )
    {
        inst.SystemID_value( strValue.c_str() );
    }

    if ( GetStrValue(variables, "version_compile_os", strValue) )
    {
        inst.CollectionID_value( strValue.c_str() );
    }

    if ( !keysOnly )
    {
        // Try and find the configuration at a list of known locations
        std::string configFile( FindConfigurationFile(pBinding, pAuth) );
        if ( configFile.size() )
        {
            inst.ConfigurationFile_value( configFile.c_str() );
        }

        if ( GetStrValue(variables, "log_error", strValue) )
        {
            inst.ErrorLogFile_value( strValue.c_str() );
        }

        inst.Hostname_value( hostname.c_str() );
        inst.BindAddress_value( entry.binding.c_str() );
        inst.Port_value( port );

        if ( GetStrValue(variables, "socket", strValue) )
        {
            inst.SocketFile_value( strValue.c_str() );
        }

        if ( GetStrValue(variables, "datadir", strValue) )
        {
            inst.DataDirectory_value( strValue.c_str() );
        }

        inst.OperatingStatus_value( "OK" );
    }
}

MySQL_Server_Class_Provider::MySQL_Server_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

MySQL_Server_Class_Provider::~MySQL_Server_Class_Provider()
{
}

void MySQL_Server_Class_Provider::Load(
        Context& context)
{
    MySQL::LogStartup();

    context.Post(MI_RESULT_OK);
}

void MySQL_Server_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void MySQL_Server_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.provider.server");

    CIM_PEX_BEGIN
    {
        // Get the list of ports (instances) that we want to look at
        std::vector<unsigned int> portList;
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        pAuth->GetPortList(portList);

        for (std::vector<unsigned int>::const_iterator it = portList.begin(); it != portList.end(); ++it)
        {
            MySQL_Server_Class inst;
            EnumerateOneInstance(hLog, inst, *it, pAuth, keysOnly);
            context.Post(inst);
        }

        context.Post(MI_RESULT_OK);
    }
    CIM_PEX_END( L"MySQL_Server_Class_Provider::EnumerateInstances" , hLog );
}

void MySQL_Server_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Class& instanceName,
    const PropertySet& propertySet)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.provider.server");

    CIM_PEX_BEGIN
    {
        // Was have a 6-part key (on Redhat, it looks like this):
        //   [Key] ProductIdentifyingNumber=jeffcof64-rhel6-01:127.0.0.1:3306
        //   [Key] ProductName=MySQL
        //   [Key] ProductVendor=Oracle
        //   [Key] ProductVersion=5.1.52
        //   [Key] SystemID=0
        //   [Key] CollectionID=redhat-linux-gnu

        if ( !instanceName.ProductIdentifyingNumber_exists()
             || !instanceName.ProductName_exists()
             || !instanceName.ProductVendor_exists()
             || !instanceName.ProductVersion_exists()
             || !instanceName.SystemID_exists()
             || !instanceName.CollectionID_exists() )
        {
            context.Post(MI_RESULT_INVALID_PARAMETER);
            return;
        }

        // Now compare (case insensitive for the class names, case sensitive for the others)
        if ( 0 != strcasecmp("MySQL", instanceName.ProductName_value().Str())
             || 0 != strcasecmp("Oracle", instanceName.ProductVendor_value().Str()) )
        {
            context.Post(MI_RESULT_NOT_FOUND);
            return;
        }

        // Save the bind-address and port from the ProductIdentifyingNumber (host:bind-address:port)

        std::wstring productID( StrFromUTF8(instanceName.ProductIdentifyingNumber_value().Str()) );
        std::vector<std::wstring> elements;

        StrTokenize(productID, elements, L":", true, true);
        if ( 3 != elements.size() || std::string::npos != elements[2].find_first_not_of(L"0123456789") )
        {
            context.Post(MI_RESULT_NOT_FOUND);
            return;
        }

        std::string bindAddress( StrToUTF8(elements[1]) );
        unsigned int port = StrToUInt( elements[2] );

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

        MySQL_Server_Class inst;
        EnumerateOneInstance(hLog, inst, port, pAuth, false /* keysOnly */);

        // Wicked ugly; the CIM standard calls for key validation, so we must as well (or unit tests fail)
        // If these final values pass, then we post result; otherwise we just return a failure
        // This, unfortunately, makes this class almost useless, but the standard is the standard

        if ( 0 != strcasecmp(inst.ProductVersion_value().Str(), instanceName.ProductVersion_value().Str())
             || 0 != strcasecmp(inst.SystemID_value().Str(), instanceName.SystemID_value().Str())
             || 0 != strcasecmp(inst.CollectionID_value().Str(), instanceName.CollectionID_value().Str()) )
        {
            context.Post(MI_RESULT_NOT_FOUND);
            return;
        }

        context.Post(inst);

        context.Post(MI_RESULT_OK);
    }
    CIM_PEX_END( L"MySQL_Server_Class_Provider::GetInstance", hLog );
}

void MySQL_Server_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_Server_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_Server_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_Server_Class_Provider::Invoke_UpdateCredentials(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Class& instanceName,
    const MySQL_Server_UpdateCredentials_Class& in)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.provider.server");

    CIM_PEX_BEGIN
    {
        SCX_LOGTRACE( hLog, L"MySQL_Server_Class_Provider::Invoke_UpdateCredentials Begin" )

        // Parameters (from MOF file):
        //   [IN] uint16 Port
        //   [IN] string BindAddress  (optional)
        //   [IN] string Username     (optional)
        //   [IN] string Password     (optional)
        //   [IN] boolean B64Encoded  (optional)

        // Validate that we have mandatory arguments
        if ( !in.Port_exists() )
        {
            SCX_LOGTRACE( hLog, L"Missing arguments to Invoke_UpdateCredentials method" );
            context.Post(MI_RESULT_INVALID_PARAMETER);
            return;
        }

        uint16_t port = in.Port_value();
        std::string bindAddress = ( in.BindAddress_exists() ? in.BindAddress_value().Str() : "" );
        std::string username = ( in.Username_exists() ? in.Username_value().Str() : "" );
        std::string password = ( in.Password_exists() ? in.Password_value().Str() : "" );

        // If we need to decode a Base64-encoded password, do so
        if ( in.B64Encoded_exists() && in.B64Encoded_value() )
        {
            bool result = util::Base64Helper::Decode(password, password);
            if ( ! result )
            {
                // Base64 conversion error - return failure
                context.Post(MI_RESULT_FAILED);
                return;
            }
        }

        SCX_LOGTRACE( hLog, "MySQL_Server_Class_Provider::Invoke_UpdateCredentials - Port: " + StrToUTF8(StrFrom(port))
                      + ", Bind Address: " + bindAddress + ", Username: " + username
                      + ", Password: " + ( password.size() ? "<not empty>" : "<empty>") );

        bool returnFlag = false;

        try
        {
            util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
            pAuth->Load();
            pAuth->AddCredentialSet(port, bindAddress, username, password);
            pAuth->Save();

            returnFlag = true;
        }
        catch (SCXException& e)
        {
            SCX_LOGERROR(hLog, L"Failure updating credentials: " + e.What());
        }

        MySQL_Server_UpdateCredentials_Class inst;

        inst.MIReturn_value(returnFlag);
        context.Post(inst);
        context.Post(MI_RESULT_OK);
    }
    CIM_PEX_END( L"MySQL_Server_Class_Provider::Invoke_UpdateCredentials", hLog );
}

void MySQL_Server_Class_Provider::Invoke_DeleteCredentials(
    Context& context,
    const String& nameSpace,
    const MySQL_Server_Class& instanceName,
    const MySQL_Server_DeleteCredentials_Class& in)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.provider.server");

    CIM_PEX_BEGIN
    {
        SCX_LOGTRACE( hLog, L"MySQL_Server_Class_Provider::Invoke_DeleteCredentials Begin" )

        // Parameters (from MOF file):
        //   [IN] uint16 Port

        // Validate that we have mandatory arguments
        if ( !in.Port_exists() )
        {
            SCX_LOGTRACE( hLog, L"Missing arguments to Invoke_DeleteCredentials method" );
            context.Post(MI_RESULT_INVALID_PARAMETER);
            return;
        }

        uint16_t port = in.Port_value();

        SCX_LOGTRACE( hLog, L"MySQL_Server_Class_Provider::Invoke_DeleteCredentials - Port: " + StrFrom(port) );

        bool returnFlag = false;

        try
        {
            util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
            pAuth->Load();
            pAuth->DeleteCredentialSet(port);
            pAuth->Save();

            returnFlag = true;
        }
        catch (SCXException& e)
        {
            SCX_LOGERROR(hLog, L"Failure deleting credentials: " + e.What());
        }

        MySQL_Server_DeleteCredentials_Class inst;

        inst.MIReturn_value(returnFlag);
        context.Post(inst);
        context.Post(MI_RESULT_OK);
    }
    CIM_PEX_END( L"MySQL_Server_Class_Provider::Invoke_DeleteCredentials", hLog );
}


MI_END_NAMESPACE
