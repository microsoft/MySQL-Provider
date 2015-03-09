/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#include <MI.h>
#include "module.h"
#include "MySQL_Server_Class_Provider.h"
#include "MySQL_ServerStatistics_Class_Provider.h"
#include "MySQL_Server_Database_Class_Provider.h"
#include "MySQL_StoredProcedureRow_AsXML_Class_Provider.h"

using namespace mi;

MI_EXTERN_C void MI_CALL MySQL_Server_Load(
    MySQL_Server_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MySQL_Server_Class_Provider* prov = new MySQL_Server_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_Context_PostResult(context, r);
        return;
    }
    *self = (MySQL_Server_Self*)prov;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL MySQL_Server_Unload(
    MySQL_Server_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MySQL_Server_Class_Provider* prov = (MySQL_Server_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((MySQL_Server_Class_Provider*)self);
    MI_Context_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL MySQL_Server_EnumerateInstances(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MySQL_Server_Class_Provider* cxxSelf =((MySQL_Server_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL MySQL_Server_GetInstance(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server* instanceName,
    const MI_PropertySet* propertySet)
{
    MySQL_Server_Class_Provider* cxxSelf =((MySQL_Server_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_Server_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MySQL_Server_CreateInstance(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server* newInstance)
{
    MySQL_Server_Class_Provider* cxxSelf =((MySQL_Server_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_Server_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL MySQL_Server_ModifyInstance(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MySQL_Server_Class_Provider* cxxSelf =((MySQL_Server_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_Server_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MySQL_Server_DeleteInstance(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server* instanceName)
{
    MySQL_Server_Class_Provider* cxxSelf =((MySQL_Server_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_Server_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL MySQL_Server_Invoke_UpdateCredentials(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySQL_Server* instanceName,
    const MySQL_Server_UpdateCredentials* in)
{
    MySQL_Server_Class_Provider* cxxSelf =((MySQL_Server_Class_Provider*)self);
    MySQL_Server_Class instance(instanceName, false);
    Context  cxxContext(context);
    MySQL_Server_UpdateCredentials_Class param(in, false);

    cxxSelf->Invoke_UpdateCredentials(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL MySQL_Server_Invoke_DeleteCredentials(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySQL_Server* instanceName,
    const MySQL_Server_DeleteCredentials* in)
{
    MySQL_Server_Class_Provider* cxxSelf =((MySQL_Server_Class_Provider*)self);
    MySQL_Server_Class instance(instanceName, false);
    Context  cxxContext(context);
    MySQL_Server_DeleteCredentials_Class param(in, false);

    cxxSelf->Invoke_DeleteCredentials(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_Load(
    MySQL_ServerStatistics_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MySQL_ServerStatistics_Class_Provider* prov = new MySQL_ServerStatistics_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_Context_PostResult(context, r);
        return;
    }
    *self = (MySQL_ServerStatistics_Self*)prov;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_Unload(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MySQL_ServerStatistics_Class_Provider* prov = (MySQL_ServerStatistics_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((MySQL_ServerStatistics_Class_Provider*)self);
    MI_Context_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_EnumerateInstances(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MySQL_ServerStatistics_Class_Provider* cxxSelf =((MySQL_ServerStatistics_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_GetInstance(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_ServerStatistics* instanceName,
    const MI_PropertySet* propertySet)
{
    MySQL_ServerStatistics_Class_Provider* cxxSelf =((MySQL_ServerStatistics_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_ServerStatistics_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_CreateInstance(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_ServerStatistics* newInstance)
{
    MySQL_ServerStatistics_Class_Provider* cxxSelf =((MySQL_ServerStatistics_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_ServerStatistics_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_ModifyInstance(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_ServerStatistics* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MySQL_ServerStatistics_Class_Provider* cxxSelf =((MySQL_ServerStatistics_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_ServerStatistics_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_DeleteInstance(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_ServerStatistics* instanceName)
{
    MySQL_ServerStatistics_Class_Provider* cxxSelf =((MySQL_ServerStatistics_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_ServerStatistics_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_Invoke_ResetSelectedStats(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySQL_ServerStatistics* instanceName,
    const MySQL_ServerStatistics_ResetSelectedStats* in)
{
    MySQL_ServerStatistics_Class_Provider* cxxSelf =((MySQL_ServerStatistics_Class_Provider*)self);
    MySQL_ServerStatistics_Class instance(instanceName, false);
    Context  cxxContext(context);
    MySQL_ServerStatistics_ResetSelectedStats_Class param(in, false);

    cxxSelf->Invoke_ResetSelectedStats(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL MySQL_Server_Database_Load(
    MySQL_Server_Database_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MySQL_Server_Database_Class_Provider* prov = new MySQL_Server_Database_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_Context_PostResult(context, r);
        return;
    }
    *self = (MySQL_Server_Database_Self*)prov;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL MySQL_Server_Database_Unload(
    MySQL_Server_Database_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MySQL_Server_Database_Class_Provider* prov = (MySQL_Server_Database_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((MySQL_Server_Database_Class_Provider*)self);
    MI_Context_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL MySQL_Server_Database_EnumerateInstances(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MySQL_Server_Database_Class_Provider* cxxSelf =((MySQL_Server_Database_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL MySQL_Server_Database_GetInstance(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server_Database* instanceName,
    const MI_PropertySet* propertySet)
{
    MySQL_Server_Database_Class_Provider* cxxSelf =((MySQL_Server_Database_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_Server_Database_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MySQL_Server_Database_CreateInstance(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server_Database* newInstance)
{
    MySQL_Server_Database_Class_Provider* cxxSelf =((MySQL_Server_Database_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_Server_Database_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL MySQL_Server_Database_ModifyInstance(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server_Database* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MySQL_Server_Database_Class_Provider* cxxSelf =((MySQL_Server_Database_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_Server_Database_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MySQL_Server_Database_DeleteInstance(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server_Database* instanceName)
{
    MySQL_Server_Database_Class_Provider* cxxSelf =((MySQL_Server_Database_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_Server_Database_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}

MI_EXTERN_C void MI_CALL MySQL_Server_Database_Invoke_RequestStateChange(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySQL_Server_Database* instanceName,
    const MySQL_Server_Database_RequestStateChange* in)
{
    MySQL_Server_Database_Class_Provider* cxxSelf =((MySQL_Server_Database_Class_Provider*)self);
    MySQL_Server_Database_Class instance(instanceName, false);
    Context  cxxContext(context);
    MySQL_Server_Database_RequestStateChange_Class param(in, false);

    cxxSelf->Invoke_RequestStateChange(cxxContext, nameSpace, instance, param);
}

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_Load(
    MySQL_StoredProcedureRow_AsXML_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MySQL_StoredProcedureRow_AsXML_Class_Provider* prov = new MySQL_StoredProcedureRow_AsXML_Class_Provider((Module*)selfModule);

    prov->Load(ctx);
    if (MI_RESULT_OK != r)
    {
        delete prov;
        MI_Context_PostResult(context, r);
        return;
    }
    *self = (MySQL_StoredProcedureRow_AsXML_Self*)prov;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_Unload(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context)
{
    MI_Result r = MI_RESULT_OK;
    Context ctx(context, &r);
    MySQL_StoredProcedureRow_AsXML_Class_Provider* prov = (MySQL_StoredProcedureRow_AsXML_Class_Provider*)self;

    prov->Unload(ctx);
    delete ((MySQL_StoredProcedureRow_AsXML_Class_Provider*)self);
    MI_Context_PostResult(context, r);
}

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_EnumerateInstances(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter)
{
    MySQL_StoredProcedureRow_AsXML_Class_Provider* cxxSelf =((MySQL_StoredProcedureRow_AsXML_Class_Provider*)self);
    Context  cxxContext(context);

    cxxSelf->EnumerateInstances(
        cxxContext,
        nameSpace,
        __PropertySet(propertySet),
        __bool(keysOnly),
        filter);
}

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_GetInstance(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_StoredProcedureRow_AsXML* instanceName,
    const MI_PropertySet* propertySet)
{
    MySQL_StoredProcedureRow_AsXML_Class_Provider* cxxSelf =((MySQL_StoredProcedureRow_AsXML_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_StoredProcedureRow_AsXML_Class cxxInstanceName(instanceName, true);

    cxxSelf->GetInstance(
        cxxContext,
        nameSpace,
        cxxInstanceName,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_CreateInstance(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_StoredProcedureRow_AsXML* newInstance)
{
    MySQL_StoredProcedureRow_AsXML_Class_Provider* cxxSelf =((MySQL_StoredProcedureRow_AsXML_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_StoredProcedureRow_AsXML_Class cxxNewInstance(newInstance, false);

    cxxSelf->CreateInstance(cxxContext, nameSpace, cxxNewInstance);
}

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_ModifyInstance(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_StoredProcedureRow_AsXML* modifiedInstance,
    const MI_PropertySet* propertySet)
{
    MySQL_StoredProcedureRow_AsXML_Class_Provider* cxxSelf =((MySQL_StoredProcedureRow_AsXML_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_StoredProcedureRow_AsXML_Class cxxModifiedInstance(modifiedInstance, false);

    cxxSelf->ModifyInstance(
        cxxContext,
        nameSpace,
        cxxModifiedInstance,
        __PropertySet(propertySet));
}

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_DeleteInstance(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_StoredProcedureRow_AsXML* instanceName)
{
    MySQL_StoredProcedureRow_AsXML_Class_Provider* cxxSelf =((MySQL_StoredProcedureRow_AsXML_Class_Provider*)self);
    Context  cxxContext(context);
    MySQL_StoredProcedureRow_AsXML_Class cxxInstanceName(instanceName, true);

    cxxSelf->DeleteInstance(cxxContext, nameSpace, cxxInstanceName);
}


MI_EXTERN_C MI_SchemaDecl schemaDecl;

void MI_CALL Load(MI_Module_Self** self, struct _MI_Context* context)
{
    *self = (MI_Module_Self*)new Module;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

void MI_CALL Unload(MI_Module_Self* self, struct _MI_Context* context)
{
    Module* module = (Module*)self;
    delete module;
    MI_Context_PostResult(context, MI_RESULT_OK);
}

MI_EXTERN_C MI_EXPORT MI_Module* MI_MAIN_CALL MI_Main(MI_Server* server)
{
    /* WARNING: THIS FUNCTION AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT. */
    extern MI_Server* __mi_server;
    static MI_Module module;
    __mi_server = server;
    module.flags |= MI_MODULE_FLAG_STANDARD_QUALIFIERS;
    module.flags |= MI_MODULE_FLAG_CPLUSPLUS;
    module.charSize = sizeof(MI_Char);
    module.version = MI_VERSION;
    module.generatorVersion = MI_MAKE_VERSION(1,0,8);
    module.schemaDecl = &schemaDecl;
    module.Load = Load;
    module.Unload = Unload;
    return &module;
}

