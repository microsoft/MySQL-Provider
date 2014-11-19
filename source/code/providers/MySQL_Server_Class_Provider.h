/* @migen@ */
#ifndef _MySQL_Server_Class_Provider_h
#define _MySQL_Server_Class_Provider_h

#include "MySQL_Server.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** MySQL_Server provider class declaration
**
**==============================================================================
*/

class MySQL_Server_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    MySQL_Server_Class_Provider(
        Module* module);

    ~MySQL_Server_Class_Provider();

    void Load(
        Context& context);

    void Unload(
        Context& context);

    void EnumerateInstances(
        Context& context,
        const String& nameSpace,
        const PropertySet& propertySet,
        bool keysOnly,
        const MI_Filter* filter);

    void GetInstance(
        Context& context,
        const String& nameSpace,
        const MySQL_Server_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const MySQL_Server_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const MySQL_Server_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const MySQL_Server_Class& instance);

    void Invoke_UpdateCredentials(
        Context& context,
        const String& nameSpace,
        const MySQL_Server_Class& instanceName,
        const MySQL_Server_UpdateCredentials_Class& in);

    void Invoke_DeleteCredentials(
        Context& context,
        const String& nameSpace,
        const MySQL_Server_Class& instanceName,
        const MySQL_Server_DeleteCredentials_Class& in);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MySQL_Server_Class_Provider_h */

