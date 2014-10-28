/* @migen@ */
#ifndef _MySQL_Server_Database_Class_Provider_h
#define _MySQL_Server_Database_Class_Provider_h

#include "MySQL_Server_Database.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** MySQL_Server_Database provider class declaration
**
**==============================================================================
*/

class MySQL_Server_Database_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    MySQL_Server_Database_Class_Provider(
        Module* module);

    ~MySQL_Server_Database_Class_Provider();

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
        const MySQL_Server_Database_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const MySQL_Server_Database_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const MySQL_Server_Database_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const MySQL_Server_Database_Class& instance);

    void Invoke_RequestStateChange(
        Context& context,
        const String& nameSpace,
        const MySQL_Server_Database_Class& instanceName,
        const MySQL_Server_Database_RequestStateChange_Class& in);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MySQL_Server_Database_Class_Provider_h */

