/* @migen@ */
#include <MI.h>
#include "MySQL_ServerStatistics_Class_Provider.h"

#include <scxcorelib/scxnameresolver.h>

#include "logstartup.h"
#include "sqlbinding.h"

using namespace SCXCoreLib;

// Helper functions to compute a ratio
static void ComputeRatio(float numerator, float denominator, uint8_t& ratio, bool bAddToDenominator = false)
{
    ratio = 0;

    // Sometimes the numerator needs to be added to the demoniator ...
    if ( bAddToDenominator )
    {
        denominator += numerator;
    }

    if ( denominator ) // Avoid divide by zero
    {
        ratio = static_cast<uint8_t> ((numerator / denominator) * 100.0 + 0.5);
    }
}

static bool ComputeRatio(
    std::map<std::string, std::string> mymap,
    const char *key1,
    const char *key2,
    uint8_t& ratio,
    bool bAddToDenominator = false)
{
    float fval1, fval2;

    if ( GetUValue(mymap, key1, fval1) && GetUValue(mymap, key2, fval2) )
    {
        ComputeRatio(fval1, fval2, ratio, bAddToDenominator);
        return true;
    }

    return false;
}

MI_BEGIN_NAMESPACE

static bool EnumerateOneInstance(
    SCXLogHandle& hLog,
    MySQL_ServerStatistics_Class& inst,
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

        return false;
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

        return false;
    }

    // The InstanceID is the hostname:bind-address:port combination
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
        SCX_LOGWARNING(hLog, StrAppend(L"Query \"show variables\" did not return \"port\" in the result set from port ", port));
        strPort = StrToUTF8(StrFrom(port));
        /* This one isn't fatal - continue processing, we've done the best we can */
    }

    std::string instanceID = hostname + ":" + entry.binding + ":" + strPort;
    inst.InstanceID_value( instanceID.c_str() );

    if ( !keysOnly )
    {
        // Execute a query to get the global status
        std::map<std::string, std::string> globals;
        if ( ! pQuery->ExecuteQuery("show global status") || ! pQuery->GetResults(globals) )
        {
            std::stringstream ss;
            ss << "Failure executing query \"show global status\" against MySQL engine on port " << port
               << ", Error " << pQuery->GetErrorNum() << ": " << pQuery->GetErrorText();
            SCX_LOGERROR(hLog, ss.str());

            return false;
        }

        //
        // Now populate our properties
        //

        uint8_t  uval8;
        uint64_t uval64;
        float valFloat, valFloat2;

        // Look up number of queries:
        //
        // On MySQL 5.0, queries = questions + com_stmt_close + com_stmt_reset + com_stmt_prepare
        // On MySQL 5.1+, just use variable "queries"

        float queries = 0;
        if ( !GetUValue(globals, "queries", queries) )
        {
            // Fallback for older MySQL servers that don't return "queries" ...

            float questions, close, reset, prepare;
            if ( GetUValue(globals, "questions", questions, true )
                 && GetUValue(globals, "com_stmt_close", close, true )
                 && GetUValue(globals, "com_stmt_reset", reset, true )
                 && GetUValue(globals, "com_stmt_prepare", prepare, true ) )
            {
                queries = questions + close + reset + prepare;
            }
            else
            {
                SCX_LOGWARNING(hLog, L"Query \"show global status\" did not return expected value in result set");
            }
        }

        
        uint32_t connectionsCurrent;
        if ( GetUValue(globals, "threads_connected", connectionsCurrent) )
        {
            inst.CurrentNumConnections_value( connectionsCurrent );
        }

        uint32_t connectionsMax;
        if ( GetUValue(variables, "max_connections", connectionsMax) )
        {
            inst.MaxConnections_value( connectionsMax );
        }

        if ( GetUValue(globals, "uptime", uval64) )
        {
            inst.Uptime_value( uval64 );
        }

        // Issue query to get the size of all databases for the instance
        std::map<std::string, std::string> totalSize;
        
        if ( pQuery->ExecuteQuery("select \"Total\" as \"Database\", SUM(a.data_length) + SUM(a.index_length) as \"Size (Bytes)\" from information_schema.schemata b left join information_schema.tables a on b.schema_name = a.table_schema") && pQuery->GetResults(totalSize) )
        {
            inst.ServerDiskUseInBytes_value( StrToULong(StrFromUTF8(totalSize["total"])) );
        }
        else
        {
            std::stringstream ss;
            ss << "Failure executing query to get size of all databases against MySQL engine, Error "
               << pQuery->GetErrorNum() << ": " << pQuery->GetErrorText();
            SCX_LOGWARNING(hLog, ss.str());
        }

        ComputeRatio(connectionsCurrent, connectionsMax, uval8);
        inst.ConnectionsUsePct_value( uval8 );

        if ( ComputeRatio(globals, "aborted_connects", "connections", uval8) )
        {
            inst.AbortedConnectionPct_value( uval8 );
        }

        if ( GetUValue(globals, "slow_queries", valFloat) )
        {
            ComputeRatio(valFloat, queries, uval8);
            inst.SlowQueryPct_value( uval8 );
        }

        if ( ComputeRatio(globals, "key_reads", "key_read_requests", uval8) )
        {
            inst.KeyCacheHitPct_value( 100 - uval8 );
        }

        if ( ComputeRatio(globals, "key_writes", "key_write_requests", uval8) )
        {
            inst.KeyCacheWritePct_value( uval8 );
        }

        float keyBlocksUnused, keyCacheBlockSize;
        if ( GetUValue(globals, "key_blocks_unused", keyBlocksUnused)
             && GetUValue(variables, "key_cache_block_size", keyCacheBlockSize)
             && GetUValue(variables, "key_buffer_size", valFloat) )
        {
            ComputeRatio(keyBlocksUnused * keyCacheBlockSize, valFloat, uval8);
            inst.KeyCacheUsePct_value( 100 - uval8 );
        }

        if ( ComputeRatio(globals, "qcache_hits", "com_select", uval8, true) )
        {
            inst.QCacheHitPct_value( uval8 );
        }

        if ( GetUValue(globals, "qcache_lowmem_prunes", valFloat) )
        {
            ComputeRatio(valFloat, queries, uval8);
            inst.QCachePrunesPct_value( uval8 );
        }

        if ( GetUValue(variables, "query_cache_size", valFloat)
             && GetUValue(globals, "qcache_free_memory", valFloat2) )
        {
            ComputeRatio( valFloat - valFloat2, valFloat, uval8 );
            inst.QCacheUsePct_value( uval8 );
        }

        if ( ComputeRatio(globals, "open_tables", "opened_tables", uval8) )
        {
            inst.TCacheHitPct_value( uval8 );
        }

        if ( ComputeRatio(globals, "table_locks_waited", "table_locks_immediate", uval8, true) )
        {
            inst.TableLockContentionPct_value( uval8 );
        }

        if ( GetUValue(globals, "open_tables", valFloat)
             && (GetUValue(variables, "table_open_cache", valFloat2)
                 || GetUValue(variables, "table_cache", valFloat2)) )
        {
            ComputeRatio( valFloat, valFloat2, uval8 );
            inst.TableCacheUsePct_value( uval8 );
        }

        if ( ComputeRatio(globals, "innodb_buffer_pool_reads", "innodb_buffer_pool_read_requests", uval8) )
        {
            inst.IDB_BP_HitPct_value( 100 - uval8 );
        }

        if ( ComputeRatio(globals, "innodb_buffer_pool_wait_free", "innodb_buffer_pool_write_requests", uval8) )
        {
            inst.IDB_BP_WriteWaitPct_value( uval8 );
        }

        if ( ComputeRatio(globals, "innodb_buffer_pool_pages_data", "innodb_buffer_pool_pages_total", uval8) )
        {
            inst.IDB_BP_UsePct_value( uval8 );
        }

        // Support for FullTableScanPct
        //
        // We can't use AddValue() method because handler_read_*_last may exist, but should not be included
        float read_rnd, read_rnd_next, read_first, read_key, read_next, read_prev;

        if ( GetUValue(globals, "handler_read_rnd", read_rnd, true)
             && GetUValue(globals, "handler_read_rnd_next", read_rnd_next, true)
             && GetUValue(globals, "handler_read_first", read_first, true)
             && GetUValue(globals, "handler_read_key", read_key, true)
             && GetUValue(globals, "handler_read_next", read_next, true)
             && GetUValue(globals, "handler_read_prev", read_prev, true) )
        {
            valFloat = read_rnd + read_rnd_next;
            valFloat2 = read_rnd + read_rnd_next + read_first + read_key + read_next + read_prev;

            ComputeRatio(valFloat, valFloat2, uval8);
            inst.FullTableScanPct_value( uval8 );
        }
        else
        {
            SCX_LOGWARNING(hLog, L"Query \"show global status\" did not return expected value in result set");
        }
    }

    return true;
}

MySQL_ServerStatistics_Class_Provider::MySQL_ServerStatistics_Class_Provider(
    Module* module) :
    m_Module(module)
{
}

MySQL_ServerStatistics_Class_Provider::~MySQL_ServerStatistics_Class_Provider()
{
}

void MySQL_ServerStatistics_Class_Provider::Load(
        Context& context)
{
    MySQL::LogStartup();

    context.Post(MI_RESULT_OK);
}

void MySQL_ServerStatistics_Class_Provider::Unload(
        Context& context)
{
    context.Post(MI_RESULT_OK);
}

void MySQL_ServerStatistics_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.provider.serverstatistics");

    CIM_PEX_BEGIN
    {
        // Get the list of ports (instances) that we want to look at
        std::vector<unsigned int> portList;
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        pAuth->GetPortList(portList);

        for (std::vector<unsigned int>::const_iterator it = portList.begin(); it != portList.end(); ++it)
        {
            MySQL_ServerStatistics_Class inst;
            if ( EnumerateOneInstance(hLog, inst, *it, pAuth, keysOnly) )
            {
                // If we posted results in EnumerateOneInstance, then post them here.
                // If not, we just skip it to pick up other instances ...

                context.Post(inst);
            }
        }

        context.Post(MI_RESULT_OK);
    }
    CIM_PEX_END( L"MySQL_ServerStatistics_Class_Provider::EnumerateInstances" , hLog );
}

void MySQL_ServerStatistics_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_ServerStatistics_Class& instanceName,
    const PropertySet& propertySet)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.provider.serverstatistics");

    CIM_PEX_BEGIN
    {
        // Was have a single key:
        //   [Key] InstanceID=jeffcof64-rhel6-01:127.0.0.1:3306

        if ( !instanceName.InstanceID_exists() )
        {
            context.Post(MI_RESULT_INVALID_PARAMETER);
            return;
        }

        // Save the bind-address and port from the InstanceID (host:bind-address:port)

        std::wstring instanceID( StrFromUTF8(instanceName.InstanceID_value().Str()) );
        std::vector<std::wstring> elements;

        StrTokenize(instanceID, elements, L":", true, true);
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

        MySQL_ServerStatistics_Class inst;
        EnumerateOneInstance(hLog, inst, port, pAuth, false /* keysOnly */);
        context.Post(inst);

        context.Post(MI_RESULT_OK);
    }
    CIM_PEX_END( L"MySQL_ServerStatistics_Class_Provider::GetInstance", hLog );
}

void MySQL_ServerStatistics_Class_Provider::CreateInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_ServerStatistics_Class& newInstance)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_ServerStatistics_Class_Provider::ModifyInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_ServerStatistics_Class& modifiedInstance,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_ServerStatistics_Class_Provider::DeleteInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_ServerStatistics_Class& instanceName)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}

void MySQL_ServerStatistics_Class_Provider::Invoke_ResetSelectedStats(
    Context& context,
    const String& nameSpace,
    const MySQL_ServerStatistics_Class& instanceName,
    const MySQL_ServerStatistics_ResetSelectedStats_Class& in)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
}


MI_END_NAMESPACE
