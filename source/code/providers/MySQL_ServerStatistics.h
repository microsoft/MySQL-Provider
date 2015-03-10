/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MySQL_ServerStatistics_h
#define _MySQL_ServerStatistics_h

#include <MI.h>
#include "CIM_StatisticalData.h"

/*
**==============================================================================
**
** MySQL_ServerStatistics [MySQL_ServerStatistics]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _MySQL_ServerStatistics /* extends CIM_StatisticalData */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_StatisticalData properties */
    MI_ConstDatetimeField StartStatisticTime;
    MI_ConstDatetimeField StatisticTime;
    MI_ConstDatetimeField SampleInterval;
    /* MySQL_ServerStatistics properties */
    MI_ConstUint32Field CurrentNumConnections;
    MI_ConstUint32Field MaxConnections;
    MI_ConstUint64Field Uptime;
    MI_ConstUint64Field ServerDiskUseInBytes;
    MI_ConstUint8Field ConnectionsUsePct;
    MI_ConstUint8Field AbortedConnectionPct;
    MI_ConstUint8Field SlowQueryPct;
    MI_ConstUint8Field KeyCacheHitPct;
    MI_ConstUint8Field KeyCacheWritePct;
    MI_ConstUint8Field KeyCacheUsePct;
    MI_ConstUint8Field QCacheHitPct;
    MI_ConstUint8Field QCachePrunesPct;
    MI_ConstUint8Field QCacheUsePct;
    MI_ConstUint8Field TCacheHitPct;
    MI_ConstUint8Field TableLockContentionPct;
    MI_ConstUint8Field TableCacheUsePct;
    MI_ConstUint8Field IDB_BP_HitPct;
    MI_ConstUint8Field IDB_BP_UsePct;
    MI_ConstUint8Field FullTableScanPct;
}
MySQL_ServerStatistics;

typedef struct _MySQL_ServerStatistics_Ref
{
    MySQL_ServerStatistics* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_ServerStatistics_Ref;

typedef struct _MySQL_ServerStatistics_ConstRef
{
    MI_CONST MySQL_ServerStatistics* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_ServerStatistics_ConstRef;

typedef struct _MySQL_ServerStatistics_Array
{
    struct _MySQL_ServerStatistics** data;
    MI_Uint32 size;
}
MySQL_ServerStatistics_Array;

typedef struct _MySQL_ServerStatistics_ConstArray
{
    struct _MySQL_ServerStatistics MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MySQL_ServerStatistics_ConstArray;

typedef struct _MySQL_ServerStatistics_ArrayRef
{
    MySQL_ServerStatistics_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_ServerStatistics_ArrayRef;

typedef struct _MySQL_ServerStatistics_ConstArrayRef
{
    MySQL_ServerStatistics_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_ServerStatistics_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MySQL_ServerStatistics_rtti;

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Construct(
    MySQL_ServerStatistics* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MySQL_ServerStatistics_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clone(
    const MySQL_ServerStatistics* self,
    MySQL_ServerStatistics** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MySQL_ServerStatistics_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MySQL_ServerStatistics_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Destruct(MySQL_ServerStatistics* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Delete(MySQL_ServerStatistics* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Post(
    const MySQL_ServerStatistics* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_InstanceID(
    MySQL_ServerStatistics* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_SetPtr_InstanceID(
    MySQL_ServerStatistics* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_InstanceID(
    MySQL_ServerStatistics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_Caption(
    MySQL_ServerStatistics* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_SetPtr_Caption(
    MySQL_ServerStatistics* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_Caption(
    MySQL_ServerStatistics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_Description(
    MySQL_ServerStatistics* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_SetPtr_Description(
    MySQL_ServerStatistics* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_Description(
    MySQL_ServerStatistics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_ElementName(
    MySQL_ServerStatistics* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_SetPtr_ElementName(
    MySQL_ServerStatistics* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_ElementName(
    MySQL_ServerStatistics* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_StartStatisticTime(
    MySQL_ServerStatistics* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->StartStatisticTime)->value = x;
    ((MI_DatetimeField*)&self->StartStatisticTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_StartStatisticTime(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->StartStatisticTime, 0, sizeof(self->StartStatisticTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_StatisticTime(
    MySQL_ServerStatistics* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->StatisticTime)->value = x;
    ((MI_DatetimeField*)&self->StatisticTime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_StatisticTime(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->StatisticTime, 0, sizeof(self->StatisticTime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_SampleInterval(
    MySQL_ServerStatistics* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->SampleInterval)->value = x;
    ((MI_DatetimeField*)&self->SampleInterval)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_SampleInterval(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->SampleInterval, 0, sizeof(self->SampleInterval));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_CurrentNumConnections(
    MySQL_ServerStatistics* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->CurrentNumConnections)->value = x;
    ((MI_Uint32Field*)&self->CurrentNumConnections)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_CurrentNumConnections(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->CurrentNumConnections, 0, sizeof(self->CurrentNumConnections));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_MaxConnections(
    MySQL_ServerStatistics* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MaxConnections)->value = x;
    ((MI_Uint32Field*)&self->MaxConnections)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_MaxConnections(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->MaxConnections, 0, sizeof(self->MaxConnections));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_Uptime(
    MySQL_ServerStatistics* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->Uptime)->value = x;
    ((MI_Uint64Field*)&self->Uptime)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_Uptime(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->Uptime, 0, sizeof(self->Uptime));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_ServerDiskUseInBytes(
    MySQL_ServerStatistics* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->ServerDiskUseInBytes)->value = x;
    ((MI_Uint64Field*)&self->ServerDiskUseInBytes)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_ServerDiskUseInBytes(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->ServerDiskUseInBytes, 0, sizeof(self->ServerDiskUseInBytes));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_ConnectionsUsePct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->ConnectionsUsePct)->value = x;
    ((MI_Uint8Field*)&self->ConnectionsUsePct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_ConnectionsUsePct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->ConnectionsUsePct, 0, sizeof(self->ConnectionsUsePct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_AbortedConnectionPct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->AbortedConnectionPct)->value = x;
    ((MI_Uint8Field*)&self->AbortedConnectionPct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_AbortedConnectionPct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->AbortedConnectionPct, 0, sizeof(self->AbortedConnectionPct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_SlowQueryPct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->SlowQueryPct)->value = x;
    ((MI_Uint8Field*)&self->SlowQueryPct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_SlowQueryPct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->SlowQueryPct, 0, sizeof(self->SlowQueryPct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_KeyCacheHitPct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->KeyCacheHitPct)->value = x;
    ((MI_Uint8Field*)&self->KeyCacheHitPct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_KeyCacheHitPct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->KeyCacheHitPct, 0, sizeof(self->KeyCacheHitPct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_KeyCacheWritePct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->KeyCacheWritePct)->value = x;
    ((MI_Uint8Field*)&self->KeyCacheWritePct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_KeyCacheWritePct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->KeyCacheWritePct, 0, sizeof(self->KeyCacheWritePct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_KeyCacheUsePct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->KeyCacheUsePct)->value = x;
    ((MI_Uint8Field*)&self->KeyCacheUsePct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_KeyCacheUsePct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->KeyCacheUsePct, 0, sizeof(self->KeyCacheUsePct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_QCacheHitPct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->QCacheHitPct)->value = x;
    ((MI_Uint8Field*)&self->QCacheHitPct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_QCacheHitPct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->QCacheHitPct, 0, sizeof(self->QCacheHitPct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_QCachePrunesPct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->QCachePrunesPct)->value = x;
    ((MI_Uint8Field*)&self->QCachePrunesPct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_QCachePrunesPct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->QCachePrunesPct, 0, sizeof(self->QCachePrunesPct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_QCacheUsePct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->QCacheUsePct)->value = x;
    ((MI_Uint8Field*)&self->QCacheUsePct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_QCacheUsePct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->QCacheUsePct, 0, sizeof(self->QCacheUsePct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_TCacheHitPct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->TCacheHitPct)->value = x;
    ((MI_Uint8Field*)&self->TCacheHitPct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_TCacheHitPct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->TCacheHitPct, 0, sizeof(self->TCacheHitPct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_TableLockContentionPct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->TableLockContentionPct)->value = x;
    ((MI_Uint8Field*)&self->TableLockContentionPct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_TableLockContentionPct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->TableLockContentionPct, 0, sizeof(self->TableLockContentionPct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_TableCacheUsePct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->TableCacheUsePct)->value = x;
    ((MI_Uint8Field*)&self->TableCacheUsePct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_TableCacheUsePct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->TableCacheUsePct, 0, sizeof(self->TableCacheUsePct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_IDB_BP_HitPct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->IDB_BP_HitPct)->value = x;
    ((MI_Uint8Field*)&self->IDB_BP_HitPct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_IDB_BP_HitPct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->IDB_BP_HitPct, 0, sizeof(self->IDB_BP_HitPct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_IDB_BP_UsePct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->IDB_BP_UsePct)->value = x;
    ((MI_Uint8Field*)&self->IDB_BP_UsePct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_IDB_BP_UsePct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->IDB_BP_UsePct, 0, sizeof(self->IDB_BP_UsePct));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Set_FullTableScanPct(
    MySQL_ServerStatistics* self,
    MI_Uint8 x)
{
    ((MI_Uint8Field*)&self->FullTableScanPct)->value = x;
    ((MI_Uint8Field*)&self->FullTableScanPct)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_Clear_FullTableScanPct(
    MySQL_ServerStatistics* self)
{
    memset((void*)&self->FullTableScanPct, 0, sizeof(self->FullTableScanPct));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySQL_ServerStatistics.ResetSelectedStats()
**
**==============================================================================
*/

typedef struct _MySQL_ServerStatistics_ResetSelectedStats
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstStringAField SelectedStatistics;
}
MySQL_ServerStatistics_ResetSelectedStats;

MI_EXTERN_C MI_CONST MI_MethodDecl MySQL_ServerStatistics_ResetSelectedStats_rtti;

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_ResetSelectedStats_Construct(
    MySQL_ServerStatistics_ResetSelectedStats* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySQL_ServerStatistics_ResetSelectedStats_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_ResetSelectedStats_Clone(
    const MySQL_ServerStatistics_ResetSelectedStats* self,
    MySQL_ServerStatistics_ResetSelectedStats** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_ResetSelectedStats_Destruct(
    MySQL_ServerStatistics_ResetSelectedStats* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_ResetSelectedStats_Delete(
    MySQL_ServerStatistics_ResetSelectedStats* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_ResetSelectedStats_Post(
    const MySQL_ServerStatistics_ResetSelectedStats* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_ResetSelectedStats_Set_MIReturn(
    MySQL_ServerStatistics_ResetSelectedStats* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_ResetSelectedStats_Clear_MIReturn(
    MySQL_ServerStatistics_ResetSelectedStats* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_ResetSelectedStats_Set_SelectedStatistics(
    MySQL_ServerStatistics_ResetSelectedStats* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_ResetSelectedStats_SetPtr_SelectedStatistics(
    MySQL_ServerStatistics_ResetSelectedStats* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_ServerStatistics_ResetSelectedStats_Clear_SelectedStatistics(
    MySQL_ServerStatistics_ResetSelectedStats* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

/*
**==============================================================================
**
** MySQL_ServerStatistics provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MySQL_ServerStatistics_Self MySQL_ServerStatistics_Self;

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_Load(
    MySQL_ServerStatistics_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_Unload(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_EnumerateInstances(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_GetInstance(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_ServerStatistics* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_CreateInstance(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_ServerStatistics* newInstance);

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_ModifyInstance(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_ServerStatistics* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_DeleteInstance(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_ServerStatistics* instanceName);

MI_EXTERN_C void MI_CALL MySQL_ServerStatistics_Invoke_ResetSelectedStats(
    MySQL_ServerStatistics_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySQL_ServerStatistics* instanceName,
    const MySQL_ServerStatistics_ResetSelectedStats* in);


/*
**==============================================================================
**
** MySQL_ServerStatistics_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MySQL_ServerStatistics_Class : public CIM_StatisticalData_Class
{
public:
    
    typedef MySQL_ServerStatistics Self;
    
    MySQL_ServerStatistics_Class() :
        CIM_StatisticalData_Class(&MySQL_ServerStatistics_rtti)
    {
    }
    
    MySQL_ServerStatistics_Class(
        const MySQL_ServerStatistics* instanceName,
        bool keysOnly) :
        CIM_StatisticalData_Class(
            &MySQL_ServerStatistics_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MySQL_ServerStatistics_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_StatisticalData_Class(clDecl, instance, keysOnly)
    {
    }
    
    MySQL_ServerStatistics_Class(
        const MI_ClassDecl* clDecl) :
        CIM_StatisticalData_Class(clDecl)
    {
    }
    
    MySQL_ServerStatistics_Class& operator=(
        const MySQL_ServerStatistics_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MySQL_ServerStatistics_Class(
        const MySQL_ServerStatistics_Class& x) :
        CIM_StatisticalData_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MySQL_ServerStatistics_rtti;
    }

    //
    // MySQL_ServerStatistics_Class.CurrentNumConnections
    //
    
    const Field<Uint32>& CurrentNumConnections() const
    {
        const size_t n = offsetof(Self, CurrentNumConnections);
        return GetField<Uint32>(n);
    }
    
    void CurrentNumConnections(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, CurrentNumConnections);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& CurrentNumConnections_value() const
    {
        const size_t n = offsetof(Self, CurrentNumConnections);
        return GetField<Uint32>(n).value;
    }
    
    void CurrentNumConnections_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, CurrentNumConnections);
        GetField<Uint32>(n).Set(x);
    }
    
    bool CurrentNumConnections_exists() const
    {
        const size_t n = offsetof(Self, CurrentNumConnections);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void CurrentNumConnections_clear()
    {
        const size_t n = offsetof(Self, CurrentNumConnections);
        GetField<Uint32>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.MaxConnections
    //
    
    const Field<Uint32>& MaxConnections() const
    {
        const size_t n = offsetof(Self, MaxConnections);
        return GetField<Uint32>(n);
    }
    
    void MaxConnections(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, MaxConnections);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& MaxConnections_value() const
    {
        const size_t n = offsetof(Self, MaxConnections);
        return GetField<Uint32>(n).value;
    }
    
    void MaxConnections_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, MaxConnections);
        GetField<Uint32>(n).Set(x);
    }
    
    bool MaxConnections_exists() const
    {
        const size_t n = offsetof(Self, MaxConnections);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void MaxConnections_clear()
    {
        const size_t n = offsetof(Self, MaxConnections);
        GetField<Uint32>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.Uptime
    //
    
    const Field<Uint64>& Uptime() const
    {
        const size_t n = offsetof(Self, Uptime);
        return GetField<Uint64>(n);
    }
    
    void Uptime(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, Uptime);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& Uptime_value() const
    {
        const size_t n = offsetof(Self, Uptime);
        return GetField<Uint64>(n).value;
    }
    
    void Uptime_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, Uptime);
        GetField<Uint64>(n).Set(x);
    }
    
    bool Uptime_exists() const
    {
        const size_t n = offsetof(Self, Uptime);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void Uptime_clear()
    {
        const size_t n = offsetof(Self, Uptime);
        GetField<Uint64>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.ServerDiskUseInBytes
    //
    
    const Field<Uint64>& ServerDiskUseInBytes() const
    {
        const size_t n = offsetof(Self, ServerDiskUseInBytes);
        return GetField<Uint64>(n);
    }
    
    void ServerDiskUseInBytes(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, ServerDiskUseInBytes);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& ServerDiskUseInBytes_value() const
    {
        const size_t n = offsetof(Self, ServerDiskUseInBytes);
        return GetField<Uint64>(n).value;
    }
    
    void ServerDiskUseInBytes_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, ServerDiskUseInBytes);
        GetField<Uint64>(n).Set(x);
    }
    
    bool ServerDiskUseInBytes_exists() const
    {
        const size_t n = offsetof(Self, ServerDiskUseInBytes);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void ServerDiskUseInBytes_clear()
    {
        const size_t n = offsetof(Self, ServerDiskUseInBytes);
        GetField<Uint64>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.ConnectionsUsePct
    //
    
    const Field<Uint8>& ConnectionsUsePct() const
    {
        const size_t n = offsetof(Self, ConnectionsUsePct);
        return GetField<Uint8>(n);
    }
    
    void ConnectionsUsePct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, ConnectionsUsePct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& ConnectionsUsePct_value() const
    {
        const size_t n = offsetof(Self, ConnectionsUsePct);
        return GetField<Uint8>(n).value;
    }
    
    void ConnectionsUsePct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, ConnectionsUsePct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool ConnectionsUsePct_exists() const
    {
        const size_t n = offsetof(Self, ConnectionsUsePct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void ConnectionsUsePct_clear()
    {
        const size_t n = offsetof(Self, ConnectionsUsePct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.AbortedConnectionPct
    //
    
    const Field<Uint8>& AbortedConnectionPct() const
    {
        const size_t n = offsetof(Self, AbortedConnectionPct);
        return GetField<Uint8>(n);
    }
    
    void AbortedConnectionPct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, AbortedConnectionPct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& AbortedConnectionPct_value() const
    {
        const size_t n = offsetof(Self, AbortedConnectionPct);
        return GetField<Uint8>(n).value;
    }
    
    void AbortedConnectionPct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, AbortedConnectionPct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool AbortedConnectionPct_exists() const
    {
        const size_t n = offsetof(Self, AbortedConnectionPct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void AbortedConnectionPct_clear()
    {
        const size_t n = offsetof(Self, AbortedConnectionPct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.SlowQueryPct
    //
    
    const Field<Uint8>& SlowQueryPct() const
    {
        const size_t n = offsetof(Self, SlowQueryPct);
        return GetField<Uint8>(n);
    }
    
    void SlowQueryPct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, SlowQueryPct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& SlowQueryPct_value() const
    {
        const size_t n = offsetof(Self, SlowQueryPct);
        return GetField<Uint8>(n).value;
    }
    
    void SlowQueryPct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, SlowQueryPct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool SlowQueryPct_exists() const
    {
        const size_t n = offsetof(Self, SlowQueryPct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void SlowQueryPct_clear()
    {
        const size_t n = offsetof(Self, SlowQueryPct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.KeyCacheHitPct
    //
    
    const Field<Uint8>& KeyCacheHitPct() const
    {
        const size_t n = offsetof(Self, KeyCacheHitPct);
        return GetField<Uint8>(n);
    }
    
    void KeyCacheHitPct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, KeyCacheHitPct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& KeyCacheHitPct_value() const
    {
        const size_t n = offsetof(Self, KeyCacheHitPct);
        return GetField<Uint8>(n).value;
    }
    
    void KeyCacheHitPct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, KeyCacheHitPct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool KeyCacheHitPct_exists() const
    {
        const size_t n = offsetof(Self, KeyCacheHitPct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void KeyCacheHitPct_clear()
    {
        const size_t n = offsetof(Self, KeyCacheHitPct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.KeyCacheWritePct
    //
    
    const Field<Uint8>& KeyCacheWritePct() const
    {
        const size_t n = offsetof(Self, KeyCacheWritePct);
        return GetField<Uint8>(n);
    }
    
    void KeyCacheWritePct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, KeyCacheWritePct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& KeyCacheWritePct_value() const
    {
        const size_t n = offsetof(Self, KeyCacheWritePct);
        return GetField<Uint8>(n).value;
    }
    
    void KeyCacheWritePct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, KeyCacheWritePct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool KeyCacheWritePct_exists() const
    {
        const size_t n = offsetof(Self, KeyCacheWritePct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void KeyCacheWritePct_clear()
    {
        const size_t n = offsetof(Self, KeyCacheWritePct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.KeyCacheUsePct
    //
    
    const Field<Uint8>& KeyCacheUsePct() const
    {
        const size_t n = offsetof(Self, KeyCacheUsePct);
        return GetField<Uint8>(n);
    }
    
    void KeyCacheUsePct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, KeyCacheUsePct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& KeyCacheUsePct_value() const
    {
        const size_t n = offsetof(Self, KeyCacheUsePct);
        return GetField<Uint8>(n).value;
    }
    
    void KeyCacheUsePct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, KeyCacheUsePct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool KeyCacheUsePct_exists() const
    {
        const size_t n = offsetof(Self, KeyCacheUsePct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void KeyCacheUsePct_clear()
    {
        const size_t n = offsetof(Self, KeyCacheUsePct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.QCacheHitPct
    //
    
    const Field<Uint8>& QCacheHitPct() const
    {
        const size_t n = offsetof(Self, QCacheHitPct);
        return GetField<Uint8>(n);
    }
    
    void QCacheHitPct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, QCacheHitPct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& QCacheHitPct_value() const
    {
        const size_t n = offsetof(Self, QCacheHitPct);
        return GetField<Uint8>(n).value;
    }
    
    void QCacheHitPct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, QCacheHitPct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool QCacheHitPct_exists() const
    {
        const size_t n = offsetof(Self, QCacheHitPct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void QCacheHitPct_clear()
    {
        const size_t n = offsetof(Self, QCacheHitPct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.QCachePrunesPct
    //
    
    const Field<Uint8>& QCachePrunesPct() const
    {
        const size_t n = offsetof(Self, QCachePrunesPct);
        return GetField<Uint8>(n);
    }
    
    void QCachePrunesPct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, QCachePrunesPct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& QCachePrunesPct_value() const
    {
        const size_t n = offsetof(Self, QCachePrunesPct);
        return GetField<Uint8>(n).value;
    }
    
    void QCachePrunesPct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, QCachePrunesPct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool QCachePrunesPct_exists() const
    {
        const size_t n = offsetof(Self, QCachePrunesPct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void QCachePrunesPct_clear()
    {
        const size_t n = offsetof(Self, QCachePrunesPct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.QCacheUsePct
    //
    
    const Field<Uint8>& QCacheUsePct() const
    {
        const size_t n = offsetof(Self, QCacheUsePct);
        return GetField<Uint8>(n);
    }
    
    void QCacheUsePct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, QCacheUsePct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& QCacheUsePct_value() const
    {
        const size_t n = offsetof(Self, QCacheUsePct);
        return GetField<Uint8>(n).value;
    }
    
    void QCacheUsePct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, QCacheUsePct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool QCacheUsePct_exists() const
    {
        const size_t n = offsetof(Self, QCacheUsePct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void QCacheUsePct_clear()
    {
        const size_t n = offsetof(Self, QCacheUsePct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.TCacheHitPct
    //
    
    const Field<Uint8>& TCacheHitPct() const
    {
        const size_t n = offsetof(Self, TCacheHitPct);
        return GetField<Uint8>(n);
    }
    
    void TCacheHitPct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, TCacheHitPct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& TCacheHitPct_value() const
    {
        const size_t n = offsetof(Self, TCacheHitPct);
        return GetField<Uint8>(n).value;
    }
    
    void TCacheHitPct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, TCacheHitPct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool TCacheHitPct_exists() const
    {
        const size_t n = offsetof(Self, TCacheHitPct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void TCacheHitPct_clear()
    {
        const size_t n = offsetof(Self, TCacheHitPct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.TableLockContentionPct
    //
    
    const Field<Uint8>& TableLockContentionPct() const
    {
        const size_t n = offsetof(Self, TableLockContentionPct);
        return GetField<Uint8>(n);
    }
    
    void TableLockContentionPct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, TableLockContentionPct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& TableLockContentionPct_value() const
    {
        const size_t n = offsetof(Self, TableLockContentionPct);
        return GetField<Uint8>(n).value;
    }
    
    void TableLockContentionPct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, TableLockContentionPct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool TableLockContentionPct_exists() const
    {
        const size_t n = offsetof(Self, TableLockContentionPct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void TableLockContentionPct_clear()
    {
        const size_t n = offsetof(Self, TableLockContentionPct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.TableCacheUsePct
    //
    
    const Field<Uint8>& TableCacheUsePct() const
    {
        const size_t n = offsetof(Self, TableCacheUsePct);
        return GetField<Uint8>(n);
    }
    
    void TableCacheUsePct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, TableCacheUsePct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& TableCacheUsePct_value() const
    {
        const size_t n = offsetof(Self, TableCacheUsePct);
        return GetField<Uint8>(n).value;
    }
    
    void TableCacheUsePct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, TableCacheUsePct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool TableCacheUsePct_exists() const
    {
        const size_t n = offsetof(Self, TableCacheUsePct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void TableCacheUsePct_clear()
    {
        const size_t n = offsetof(Self, TableCacheUsePct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.IDB_BP_HitPct
    //
    
    const Field<Uint8>& IDB_BP_HitPct() const
    {
        const size_t n = offsetof(Self, IDB_BP_HitPct);
        return GetField<Uint8>(n);
    }
    
    void IDB_BP_HitPct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, IDB_BP_HitPct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& IDB_BP_HitPct_value() const
    {
        const size_t n = offsetof(Self, IDB_BP_HitPct);
        return GetField<Uint8>(n).value;
    }
    
    void IDB_BP_HitPct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, IDB_BP_HitPct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool IDB_BP_HitPct_exists() const
    {
        const size_t n = offsetof(Self, IDB_BP_HitPct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void IDB_BP_HitPct_clear()
    {
        const size_t n = offsetof(Self, IDB_BP_HitPct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.IDB_BP_UsePct
    //
    
    const Field<Uint8>& IDB_BP_UsePct() const
    {
        const size_t n = offsetof(Self, IDB_BP_UsePct);
        return GetField<Uint8>(n);
    }
    
    void IDB_BP_UsePct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, IDB_BP_UsePct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& IDB_BP_UsePct_value() const
    {
        const size_t n = offsetof(Self, IDB_BP_UsePct);
        return GetField<Uint8>(n).value;
    }
    
    void IDB_BP_UsePct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, IDB_BP_UsePct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool IDB_BP_UsePct_exists() const
    {
        const size_t n = offsetof(Self, IDB_BP_UsePct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void IDB_BP_UsePct_clear()
    {
        const size_t n = offsetof(Self, IDB_BP_UsePct);
        GetField<Uint8>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_Class.FullTableScanPct
    //
    
    const Field<Uint8>& FullTableScanPct() const
    {
        const size_t n = offsetof(Self, FullTableScanPct);
        return GetField<Uint8>(n);
    }
    
    void FullTableScanPct(const Field<Uint8>& x)
    {
        const size_t n = offsetof(Self, FullTableScanPct);
        GetField<Uint8>(n) = x;
    }
    
    const Uint8& FullTableScanPct_value() const
    {
        const size_t n = offsetof(Self, FullTableScanPct);
        return GetField<Uint8>(n).value;
    }
    
    void FullTableScanPct_value(const Uint8& x)
    {
        const size_t n = offsetof(Self, FullTableScanPct);
        GetField<Uint8>(n).Set(x);
    }
    
    bool FullTableScanPct_exists() const
    {
        const size_t n = offsetof(Self, FullTableScanPct);
        return GetField<Uint8>(n).exists ? true : false;
    }
    
    void FullTableScanPct_clear()
    {
        const size_t n = offsetof(Self, FullTableScanPct);
        GetField<Uint8>(n).Clear();
    }
};

typedef Array<MySQL_ServerStatistics_Class> MySQL_ServerStatistics_ClassA;

class MySQL_ServerStatistics_ResetSelectedStats_Class : public Instance
{
public:
    
    typedef MySQL_ServerStatistics_ResetSelectedStats Self;
    
    MySQL_ServerStatistics_ResetSelectedStats_Class() :
        Instance(&MySQL_ServerStatistics_ResetSelectedStats_rtti)
    {
    }
    
    MySQL_ServerStatistics_ResetSelectedStats_Class(
        const MySQL_ServerStatistics_ResetSelectedStats* instanceName,
        bool keysOnly) :
        Instance(
            &MySQL_ServerStatistics_ResetSelectedStats_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MySQL_ServerStatistics_ResetSelectedStats_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MySQL_ServerStatistics_ResetSelectedStats_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MySQL_ServerStatistics_ResetSelectedStats_Class& operator=(
        const MySQL_ServerStatistics_ResetSelectedStats_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MySQL_ServerStatistics_ResetSelectedStats_Class(
        const MySQL_ServerStatistics_ResetSelectedStats_Class& x) :
        Instance(x)
    {
    }

    //
    // MySQL_ServerStatistics_ResetSelectedStats_Class.MIReturn
    //
    
    const Field<Uint32>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n);
    }
    
    void MIReturn(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n).value;
    }
    
    void MIReturn_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Uint32>(n).Clear();
    }

    //
    // MySQL_ServerStatistics_ResetSelectedStats_Class.SelectedStatistics
    //
    
    const Field<StringA>& SelectedStatistics() const
    {
        const size_t n = offsetof(Self, SelectedStatistics);
        return GetField<StringA>(n);
    }
    
    void SelectedStatistics(const Field<StringA>& x)
    {
        const size_t n = offsetof(Self, SelectedStatistics);
        GetField<StringA>(n) = x;
    }
    
    const StringA& SelectedStatistics_value() const
    {
        const size_t n = offsetof(Self, SelectedStatistics);
        return GetField<StringA>(n).value;
    }
    
    void SelectedStatistics_value(const StringA& x)
    {
        const size_t n = offsetof(Self, SelectedStatistics);
        GetField<StringA>(n).Set(x);
    }
    
    bool SelectedStatistics_exists() const
    {
        const size_t n = offsetof(Self, SelectedStatistics);
        return GetField<StringA>(n).exists ? true : false;
    }
    
    void SelectedStatistics_clear()
    {
        const size_t n = offsetof(Self, SelectedStatistics);
        GetField<StringA>(n).Clear();
    }
};

typedef Array<MySQL_ServerStatistics_ResetSelectedStats_Class> MySQL_ServerStatistics_ResetSelectedStats_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MySQL_ServerStatistics_h */
