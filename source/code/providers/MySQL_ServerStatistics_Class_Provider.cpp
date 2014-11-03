/* @migen@ */
#include <MI.h>
#include "MySQL_ServerStatistics_Class_Provider.h"

#include "sqlbinding.h"

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
        ratio = (numerator / denominator) * 100.0;
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

void MySQL_ServerStatistics_Class_Provider::Unload(
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

void MySQL_ServerStatistics_Class_Provider::EnumerateInstances(
    Context& context,
    const String& nameSpace,
    const PropertySet& propertySet,
    bool keysOnly,
    const MI_Filter* filter)
{
    CIM_PEX_BEGIN
    {
        MySQL_ServerStatistics_Class inst;

        // Execute a query to get the MySQL variables
        util::unique_ptr<MySQL_Query> pQuery( g_pFactory->GetQuery() );
        if ( ! pQuery->ExecuteQuery("show variables") )
        {
            // *TODO* Log something here!
            context.Post(MI_RESULT_FAILED);
            return;
        }
        std::map<std::string, std::string> variables = pQuery->GetResults();

        // The InstanceID is the hostname:port combination
        std::string hostname, port;
        if ( !GetStrValue(variables, "hostname", hostname) )
        {
            // Populate hostname here (for MySQL 5.0 systems)
            GetHostname( hostname );
        }

        if ( GetStrValue(variables, "port", port) )
        {
            std::string instanceID = hostname + ":" + port;
            inst.InstanceID_value( instanceID.c_str() );
        }
        else
        {
            // *TODO* Log something here!
            context.Post(MI_RESULT_FAILED);
            return;
        }

        if ( !keysOnly )
        {
            // Execute a query to get the global status
            if ( ! pQuery->ExecuteQuery("show global status") )
            {
                // *TODO* Log something here!
                context.Post(MI_RESULT_FAILED);
                return;
            }
            std::map<std::string, std::string> globals = pQuery->GetResults();

            //
            // Now populate our properties
            //

            uint8_t  uval8;
            uint32_t uval32;
            uint64_t uval64;
            float valFloat, valFloat2;

            // Look up number of queries:
            //
            // On MySQL 5.0, queries = questions + com_stmt_close + com_stmt_reset + com_stmt_prepare
            // On MySQL 5.1+, just use variable "queries"

            float queries = 0;
            if ( !GetUValue(globals, "queries", uval64) )
            {
                float questions, close, reset, prepare;
                if ( GetUValue(globals, "questions", questions )
                     && GetUValue(globals, "com_stmt_close", close )
                     && GetUValue(globals, "com_stmt_reset", reset )
                     && GetUValue(globals, "com_stmt_prepare", prepare ))
                {
                    queries = questions + close + reset + prepare;
                }
                else
                {
                    // *TODO* Log some sort of warning here, but fall through
                }
            }

            if ( GetUValue(globals, "threads_connected", uval32) )
            {
                inst.NumConnections_value( uval32 );
            }

            if ( GetUValue(variables, "max_connections", uval32) )
            {
                inst.MaxConnections_value( uval32 );
            }

            if ( GetUValue(globals, "aborted_connects", uval32) )
            {
                inst.FailedConnections_value( uval32 );
            }

            if ( GetUValue(globals, "uptime", uval64) )
            {
                inst.Uptime_value( uval64 );
            }

            // *TODO* This is involved, work this out a bit later; Waiting for PM feedback
            inst.ServerDiskUseInBytes_value( 0 );

            if ( GetUValue(globals, "slow_queries", valFloat) )
            {
                ComputeRatio(valFloat, queries, uval8);
                inst.SlowQueryPct_value( uval8 );
            }

            if ( ComputeRatio(globals, "key_reads", "key_read_requests", uval8) )
            {
                inst.KeyCacheHitPct_value( uval8 );
            }

            if ( ComputeRatio(globals, "key_writes", "key_write_requests", uval8) )
            {
                inst.KeyCacheWritePct_value( uval8 );
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

            if ( ComputeRatio(globals, "open_tables", "opened_tables", uval8) )
            {
                inst.TCacheHitPct_value( uval8 );
            }

            if ( ComputeRatio(globals, "table_locks_waited", "table_locks_immediate", uval8, true) )
            {
                inst.TableLockContentionPct_value( uval8 );
            }

            if ( ComputeRatio(globals, "innodb_buffer_pool_reads", "innodb_buffer_pool_read_requests", uval8, true) )
            {
                inst.IDB_BP_HitPct_value( uval8 );
            }

            if ( ComputeRatio(globals, "innodb_buffer_pool_pages_data", "innodb_buffer_pool_pages_total", uval8) )
            {
                inst.IDB_BP_UsePct_value( uval8 );
            }

            // *TODO* Rework this, handler_read_*_last may exist but should not be included
            int numeratorCount = AddValues(globals, "handler_read_rnd", valFloat);
            int denominatorCount = AddValues(globals, "handler_read_", valFloat2);
            if ( 2 == numeratorCount && 6 == denominatorCount )
            {
                ComputeRatio(valFloat, valFloat2, uval8);
                inst.FullTableScanPct_value( uval8 );
            }

            // *TODO* Need exact rules for what to return, and when; waiting for PM input
            inst.SlaveStatus_value( "Unknown" );

            // *TODO* Waiting for PM input; not clear how to pull this right now
            inst.SlaveLag_value( 0 );
        }

        context.Post(inst);
        context.Post(MI_RESULT_OK);
    }
    CIM_PEX_END( "MySQL_ServerStatistics_Class_Provider::EnumerateInstances" );
}

void MySQL_ServerStatistics_Class_Provider::GetInstance(
    Context& context,
    const String& nameSpace,
    const MySQL_ServerStatistics_Class& instanceName,
    const PropertySet& propertySet)
{
    context.Post(MI_RESULT_NOT_SUPPORTED);
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
