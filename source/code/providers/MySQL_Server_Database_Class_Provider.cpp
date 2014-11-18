/* @migen@ */
#include <MI.h>
#include "MySQL_Server_Database_Class_Provider.h"

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxnameresolver.h>
#include <scxcorelib/stringaid.h>

#include "logstartup.h"
#include "sqlbinding.h"

MI_BEGIN_NAMESPACE

static void EnumerateOneInstance(MySQL_Server_Database_Class& inst, const std::string& dbName, uint64_t tableCount, const std::string& instanceID, const bool keysOnly)
{
    inst.InstanceID_value( std::string(instanceID + ":" + dbName).c_str() );

    if ( !keysOnly )
    {
        inst.DatabaseName_value( dbName.c_str() );
        inst.NumberOfTables_value( tableCount );

        // *TODO* Need to work out Disk Space In Bytes with PM ...
        inst.DiskSpaceInBytes_value( 0 );
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

    // Attach to the MySQL instance
    if ( NULL == g_pFactory )
    {
        g_pFactory = new MySQL_Factory();
    }

    MySQL_Binding* pBinding = g_pFactory->GetBinding();

    if ( !pBinding->AttachUsingStoredCredentials() )
    {
        context.Post(MI_RESULT_FAILED);
        return;
    }

    context.Post(MI_RESULT_OK);
}

void MySQL_Server_Database_Class_Provider::Unload(
        Context& context)
{
    // Delete our factory
    if ( NULL != g_pFactory )
    {
        delete g_pFactory;
        g_pFactory = NULL;
    }

    context.Post(MI_RESULT_OK);
}

void MySQL_Server_Database_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    SCXCoreLib::SCXLogHandle hLog = SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.provider.database");

    CIM_PEX_BEGIN
    {
        // Execute a query to get the MySQL variables
        util::unique_ptr<MySQL_Query> pQuery( g_pFactory->GetQuery() );
        if ( ! pQuery->ExecuteQuery("show variables") )
        {
            std::stringstream ss;
            ss << "Failure executing query \"show variables\" against MySQL engine, Error "
               << pQuery->GetErrorNum() << ": " << pQuery->GetErrorText();
            SCX_LOGERROR(hLog, ss.str());
            context.Post(MI_RESULT_FAILED);
            return;
        }
        std::map<std::string, std::string> variables = pQuery->GetResults();

        // The InstanceID is the hostname:port combination
        std::string hostname, port;
        if ( !GetStrValue(variables, "hostname", hostname) )
        {
            // Populate hostname here (for MySQL 5.0 systems)
            SCXCoreLib::NameResolver nr;
            hostname = SCXCoreLib::StrToUTF8(nr.GetHostname());
        }

        if ( !GetStrValue(variables, "port", port) )
        {
            SCX_LOGERROR(hLog, L"Query \"show variables\" did not return \"port\" in the result set");
            context.Post(MI_RESULT_FAILED);
            return;
        }
        std::string instanceID = hostname + ":" + port;

        // Execute a query to get the list of MySQL databases and number of tables per database
        if ( ! pQuery->ExecuteQuery("select b.schema_name as \"Database\", count(a.table_name) as \"Count\" from information_schema.schemata b left join information_schema.tables a on b.schema_name = a.table_schema group by b.schema_name;") )
        {
            std::stringstream ss;
            ss << "Failure executing query to get list of tables/database against MySQL engine, error "
               << pQuery->GetErrorNum() << ": " << pQuery->GetErrorText();
            SCX_LOGERROR(hLog, ss.str());
            context.Post(MI_RESULT_FAILED);
            return;
        }
        std::map<std::string, std::string> databases = pQuery->GetResults();

        for (std::map<std::string,std::string>::const_iterator it = databases.begin(); it != databases.end(); ++it)
        {
            MySQL_Server_Database_Class inst;
            uint64_t tableCount = 0;

            if ( ! ConvertToUnsigned(it->second, tableCount) )
            {
                SCX_LOGERROR(hLog, "Failure converting count for database " + it->first + "; enumerating with zero databases");
            }

            EnumerateOneInstance(inst, it->first, tableCount, instanceID, keysOnly);
            context.Post(inst);
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
    context.Post(MI_RESULT_NOT_SUPPORTED);
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
