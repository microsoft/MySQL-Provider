/* @migen@ */
#include <MI.h>
#include "MySQL_ServerStatistics_Class_Provider.h"

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
    context.Post(MI_RESULT_NOT_SUPPORTED);
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
