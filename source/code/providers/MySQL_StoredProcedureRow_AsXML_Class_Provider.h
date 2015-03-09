/* @migen@ */
#ifndef _MySQL_StoredProcedureRow_AsXML_Class_Provider_h
#define _MySQL_StoredProcedureRow_AsXML_Class_Provider_h

#include "MySQL_StoredProcedureRow_AsXML.h"
#ifdef __cplusplus
# include <micxx/micxx.h>
# include "module.h"

MI_BEGIN_NAMESPACE

/*
**==============================================================================
**
** MySQL_StoredProcedureRow_AsXML provider class declaration
**
**==============================================================================
*/

class MySQL_StoredProcedureRow_AsXML_Class_Provider
{
/* @MIGEN.BEGIN@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
private:
    Module* m_Module;

public:
    MySQL_StoredProcedureRow_AsXML_Class_Provider(
        Module* module);

    ~MySQL_StoredProcedureRow_AsXML_Class_Provider();

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
        const MySQL_StoredProcedureRow_AsXML_Class& instance,
        const PropertySet& propertySet);

    void CreateInstance(
        Context& context,
        const String& nameSpace,
        const MySQL_StoredProcedureRow_AsXML_Class& newInstance);

    void ModifyInstance(
        Context& context,
        const String& nameSpace,
        const MySQL_StoredProcedureRow_AsXML_Class& modifiedInstance,
        const PropertySet& propertySet);

    void DeleteInstance(
        Context& context,
        const String& nameSpace,
        const MySQL_StoredProcedureRow_AsXML_Class& instance);

/* @MIGEN.END@ CAUTION: PLEASE DO NOT EDIT OR DELETE THIS LINE. */
};

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MySQL_StoredProcedureRow_AsXML_Class_Provider_h */

