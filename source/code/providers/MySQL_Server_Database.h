/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MySQL_Server_Database_h
#define _MySQL_Server_Database_h

#include <MI.h>
#include "CIM_CommonDatabase.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** MySQL_Server_Database [MySQL_Server_Database]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _MySQL_Server_Database /* extends CIM_CommonDatabase */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_ManagedSystemElement properties */
    MI_ConstDatetimeField InstallDate;
    MI_ConstStringField Name;
    MI_ConstUint16AField OperationalStatus;
    MI_ConstStringAField StatusDescriptions;
    MI_ConstStringField Status;
    MI_ConstUint16Field HealthState;
    MI_ConstUint16Field CommunicationStatus;
    MI_ConstUint16Field DetailedStatus;
    MI_ConstUint16Field OperatingStatus;
    MI_ConstUint16Field PrimaryStatus;
    /* CIM_LogicalElement properties */
    /* CIM_EnabledLogicalElement properties */
    MI_ConstUint16Field EnabledState;
    MI_ConstStringField OtherEnabledState;
    MI_ConstUint16Field RequestedState;
    MI_ConstUint16Field EnabledDefault;
    MI_ConstDatetimeField TimeOfLastStateChange;
    MI_ConstUint16AField AvailableRequestedStates;
    MI_ConstUint16Field TransitioningToState;
    /* CIM_CommonDatabase properties */
    MI_ConstStringField DatabaseVersion;
    MI_ConstDatetimeField LastBackup;
    MI_ConstUint32Field SizeAllocated;
    MI_ConstUint16Field SizeUnits;
    /* MySQL_Server_Database properties */
    MI_ConstStringField DatabaseName;
    MI_ConstUint64Field NumberOfTables;
    MI_ConstUint64Field DiskSpaceInBytes;
}
MySQL_Server_Database;

typedef struct _MySQL_Server_Database_Ref
{
    MySQL_Server_Database* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_Server_Database_Ref;

typedef struct _MySQL_Server_Database_ConstRef
{
    MI_CONST MySQL_Server_Database* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_Server_Database_ConstRef;

typedef struct _MySQL_Server_Database_Array
{
    struct _MySQL_Server_Database** data;
    MI_Uint32 size;
}
MySQL_Server_Database_Array;

typedef struct _MySQL_Server_Database_ConstArray
{
    struct _MySQL_Server_Database MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MySQL_Server_Database_ConstArray;

typedef struct _MySQL_Server_Database_ArrayRef
{
    MySQL_Server_Database_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_Server_Database_ArrayRef;

typedef struct _MySQL_Server_Database_ConstArrayRef
{
    MySQL_Server_Database_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_Server_Database_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MySQL_Server_Database_rtti;

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Construct(
    MySQL_Server_Database* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MySQL_Server_Database_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clone(
    const MySQL_Server_Database* self,
    MySQL_Server_Database** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MySQL_Server_Database_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MySQL_Server_Database_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Destruct(MySQL_Server_Database* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Delete(MySQL_Server_Database* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Post(
    const MySQL_Server_Database* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_InstanceID(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_InstanceID(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_InstanceID(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_Caption(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_Caption(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_Caption(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_Description(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_Description(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_Description(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_ElementName(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_ElementName(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_ElementName(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_InstallDate(
    MySQL_Server_Database* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_InstallDate(
    MySQL_Server_Database* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_Name(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_Name(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_Name(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_OperationalStatus(
    MySQL_Server_Database* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_OperationalStatus(
    MySQL_Server_Database* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_OperationalStatus(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_StatusDescriptions(
    MySQL_Server_Database* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_StatusDescriptions(
    MySQL_Server_Database* self,
    const MI_Char** data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&arr,
        MI_STRINGA,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_StatusDescriptions(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_Status(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_Status(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_Status(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_HealthState(
    MySQL_Server_Database* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_HealthState(
    MySQL_Server_Database* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_CommunicationStatus(
    MySQL_Server_Database* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_CommunicationStatus(
    MySQL_Server_Database* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_DetailedStatus(
    MySQL_Server_Database* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_DetailedStatus(
    MySQL_Server_Database* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_OperatingStatus(
    MySQL_Server_Database* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_OperatingStatus(
    MySQL_Server_Database* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_PrimaryStatus(
    MySQL_Server_Database* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_PrimaryStatus(
    MySQL_Server_Database* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_EnabledState(
    MySQL_Server_Database* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_EnabledState(
    MySQL_Server_Database* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_OtherEnabledState(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_OtherEnabledState(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_OtherEnabledState(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_RequestedState(
    MySQL_Server_Database* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_RequestedState(
    MySQL_Server_Database* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_EnabledDefault(
    MySQL_Server_Database* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_EnabledDefault(
    MySQL_Server_Database* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_TimeOfLastStateChange(
    MySQL_Server_Database* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_TimeOfLastStateChange(
    MySQL_Server_Database* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_AvailableRequestedStates(
    MySQL_Server_Database* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_UINT16A,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_AvailableRequestedStates(
    MySQL_Server_Database* self,
    const MI_Uint16* data,
    MI_Uint32 size)
{
    MI_Array arr;
    arr.data = (void*)data;
    arr.size = size;
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        19,
        (MI_Value*)&arr,
        MI_UINT16A,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_AvailableRequestedStates(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_TransitioningToState(
    MySQL_Server_Database* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_TransitioningToState(
    MySQL_Server_Database* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_DatabaseVersion(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_DatabaseVersion(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_DatabaseVersion(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_LastBackup(
    MySQL_Server_Database* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->LastBackup)->value = x;
    ((MI_DatetimeField*)&self->LastBackup)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_LastBackup(
    MySQL_Server_Database* self)
{
    memset((void*)&self->LastBackup, 0, sizeof(self->LastBackup));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_SizeAllocated(
    MySQL_Server_Database* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SizeAllocated)->value = x;
    ((MI_Uint32Field*)&self->SizeAllocated)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_SizeAllocated(
    MySQL_Server_Database* self)
{
    memset((void*)&self->SizeAllocated, 0, sizeof(self->SizeAllocated));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_SizeUnits(
    MySQL_Server_Database* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SizeUnits)->value = x;
    ((MI_Uint16Field*)&self->SizeUnits)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_SizeUnits(
    MySQL_Server_Database* self)
{
    memset((void*)&self->SizeUnits, 0, sizeof(self->SizeUnits));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_DatabaseName(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_SetPtr_DatabaseName(
    MySQL_Server_Database* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        25,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_DatabaseName(
    MySQL_Server_Database* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        25);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_NumberOfTables(
    MySQL_Server_Database* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->NumberOfTables)->value = x;
    ((MI_Uint64Field*)&self->NumberOfTables)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_NumberOfTables(
    MySQL_Server_Database* self)
{
    memset((void*)&self->NumberOfTables, 0, sizeof(self->NumberOfTables));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Set_DiskSpaceInBytes(
    MySQL_Server_Database* self,
    MI_Uint64 x)
{
    ((MI_Uint64Field*)&self->DiskSpaceInBytes)->value = x;
    ((MI_Uint64Field*)&self->DiskSpaceInBytes)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_Clear_DiskSpaceInBytes(
    MySQL_Server_Database* self)
{
    memset((void*)&self->DiskSpaceInBytes, 0, sizeof(self->DiskSpaceInBytes));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySQL_Server_Database.RequestStateChange()
**
**==============================================================================
*/

typedef struct _MySQL_Server_Database_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
MySQL_Server_Database_RequestStateChange;

MI_EXTERN_C MI_CONST MI_MethodDecl MySQL_Server_Database_RequestStateChange_rtti;

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Construct(
    MySQL_Server_Database_RequestStateChange* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySQL_Server_Database_RequestStateChange_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Clone(
    const MySQL_Server_Database_RequestStateChange* self,
    MySQL_Server_Database_RequestStateChange** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Destruct(
    MySQL_Server_Database_RequestStateChange* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Delete(
    MySQL_Server_Database_RequestStateChange* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Post(
    const MySQL_Server_Database_RequestStateChange* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Set_MIReturn(
    MySQL_Server_Database_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Clear_MIReturn(
    MySQL_Server_Database_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Set_RequestedState(
    MySQL_Server_Database_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Clear_RequestedState(
    MySQL_Server_Database_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Set_Job(
    MySQL_Server_Database_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_SetPtr_Job(
    MySQL_Server_Database_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Clear_Job(
    MySQL_Server_Database_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Set_TimeoutPeriod(
    MySQL_Server_Database_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Database_RequestStateChange_Clear_TimeoutPeriod(
    MySQL_Server_Database_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySQL_Server_Database provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MySQL_Server_Database_Self MySQL_Server_Database_Self;

MI_EXTERN_C void MI_CALL MySQL_Server_Database_Load(
    MySQL_Server_Database_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySQL_Server_Database_Unload(
    MySQL_Server_Database_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySQL_Server_Database_EnumerateInstances(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MySQL_Server_Database_GetInstance(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server_Database* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MySQL_Server_Database_CreateInstance(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server_Database* newInstance);

MI_EXTERN_C void MI_CALL MySQL_Server_Database_ModifyInstance(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server_Database* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MySQL_Server_Database_DeleteInstance(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server_Database* instanceName);

MI_EXTERN_C void MI_CALL MySQL_Server_Database_Invoke_RequestStateChange(
    MySQL_Server_Database_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySQL_Server_Database* instanceName,
    const MySQL_Server_Database_RequestStateChange* in);


/*
**==============================================================================
**
** MySQL_Server_Database_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MySQL_Server_Database_Class : public CIM_CommonDatabase_Class
{
public:
    
    typedef MySQL_Server_Database Self;
    
    MySQL_Server_Database_Class() :
        CIM_CommonDatabase_Class(&MySQL_Server_Database_rtti)
    {
    }
    
    MySQL_Server_Database_Class(
        const MySQL_Server_Database* instanceName,
        bool keysOnly) :
        CIM_CommonDatabase_Class(
            &MySQL_Server_Database_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MySQL_Server_Database_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_CommonDatabase_Class(clDecl, instance, keysOnly)
    {
    }
    
    MySQL_Server_Database_Class(
        const MI_ClassDecl* clDecl) :
        CIM_CommonDatabase_Class(clDecl)
    {
    }
    
    MySQL_Server_Database_Class& operator=(
        const MySQL_Server_Database_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MySQL_Server_Database_Class(
        const MySQL_Server_Database_Class& x) :
        CIM_CommonDatabase_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MySQL_Server_Database_rtti;
    }

    //
    // MySQL_Server_Database_Class.DatabaseName
    //
    
    const Field<String>& DatabaseName() const
    {
        const size_t n = offsetof(Self, DatabaseName);
        return GetField<String>(n);
    }
    
    void DatabaseName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, DatabaseName);
        GetField<String>(n) = x;
    }
    
    const String& DatabaseName_value() const
    {
        const size_t n = offsetof(Self, DatabaseName);
        return GetField<String>(n).value;
    }
    
    void DatabaseName_value(const String& x)
    {
        const size_t n = offsetof(Self, DatabaseName);
        GetField<String>(n).Set(x);
    }
    
    bool DatabaseName_exists() const
    {
        const size_t n = offsetof(Self, DatabaseName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void DatabaseName_clear()
    {
        const size_t n = offsetof(Self, DatabaseName);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_Server_Database_Class.NumberOfTables
    //
    
    const Field<Uint64>& NumberOfTables() const
    {
        const size_t n = offsetof(Self, NumberOfTables);
        return GetField<Uint64>(n);
    }
    
    void NumberOfTables(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, NumberOfTables);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& NumberOfTables_value() const
    {
        const size_t n = offsetof(Self, NumberOfTables);
        return GetField<Uint64>(n).value;
    }
    
    void NumberOfTables_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, NumberOfTables);
        GetField<Uint64>(n).Set(x);
    }
    
    bool NumberOfTables_exists() const
    {
        const size_t n = offsetof(Self, NumberOfTables);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void NumberOfTables_clear()
    {
        const size_t n = offsetof(Self, NumberOfTables);
        GetField<Uint64>(n).Clear();
    }

    //
    // MySQL_Server_Database_Class.DiskSpaceInBytes
    //
    
    const Field<Uint64>& DiskSpaceInBytes() const
    {
        const size_t n = offsetof(Self, DiskSpaceInBytes);
        return GetField<Uint64>(n);
    }
    
    void DiskSpaceInBytes(const Field<Uint64>& x)
    {
        const size_t n = offsetof(Self, DiskSpaceInBytes);
        GetField<Uint64>(n) = x;
    }
    
    const Uint64& DiskSpaceInBytes_value() const
    {
        const size_t n = offsetof(Self, DiskSpaceInBytes);
        return GetField<Uint64>(n).value;
    }
    
    void DiskSpaceInBytes_value(const Uint64& x)
    {
        const size_t n = offsetof(Self, DiskSpaceInBytes);
        GetField<Uint64>(n).Set(x);
    }
    
    bool DiskSpaceInBytes_exists() const
    {
        const size_t n = offsetof(Self, DiskSpaceInBytes);
        return GetField<Uint64>(n).exists ? true : false;
    }
    
    void DiskSpaceInBytes_clear()
    {
        const size_t n = offsetof(Self, DiskSpaceInBytes);
        GetField<Uint64>(n).Clear();
    }
};

typedef Array<MySQL_Server_Database_Class> MySQL_Server_Database_ClassA;

class MySQL_Server_Database_RequestStateChange_Class : public Instance
{
public:
    
    typedef MySQL_Server_Database_RequestStateChange Self;
    
    MySQL_Server_Database_RequestStateChange_Class() :
        Instance(&MySQL_Server_Database_RequestStateChange_rtti)
    {
    }
    
    MySQL_Server_Database_RequestStateChange_Class(
        const MySQL_Server_Database_RequestStateChange* instanceName,
        bool keysOnly) :
        Instance(
            &MySQL_Server_Database_RequestStateChange_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MySQL_Server_Database_RequestStateChange_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MySQL_Server_Database_RequestStateChange_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MySQL_Server_Database_RequestStateChange_Class& operator=(
        const MySQL_Server_Database_RequestStateChange_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MySQL_Server_Database_RequestStateChange_Class(
        const MySQL_Server_Database_RequestStateChange_Class& x) :
        Instance(x)
    {
    }

    //
    // MySQL_Server_Database_RequestStateChange_Class.MIReturn
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
    // MySQL_Server_Database_RequestStateChange_Class.RequestedState
    //
    
    const Field<Uint16>& RequestedState() const
    {
        const size_t n = offsetof(Self, RequestedState);
        return GetField<Uint16>(n);
    }
    
    void RequestedState(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, RequestedState);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& RequestedState_value() const
    {
        const size_t n = offsetof(Self, RequestedState);
        return GetField<Uint16>(n).value;
    }
    
    void RequestedState_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, RequestedState);
        GetField<Uint16>(n).Set(x);
    }
    
    bool RequestedState_exists() const
    {
        const size_t n = offsetof(Self, RequestedState);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void RequestedState_clear()
    {
        const size_t n = offsetof(Self, RequestedState);
        GetField<Uint16>(n).Clear();
    }

    //
    // MySQL_Server_Database_RequestStateChange_Class.Job
    //
    
    const Field<CIM_ConcreteJob_Class>& Job() const
    {
        const size_t n = offsetof(Self, Job);
        return GetField<CIM_ConcreteJob_Class>(n);
    }
    
    void Job(const Field<CIM_ConcreteJob_Class>& x)
    {
        const size_t n = offsetof(Self, Job);
        GetField<CIM_ConcreteJob_Class>(n) = x;
    }
    
    const CIM_ConcreteJob_Class& Job_value() const
    {
        const size_t n = offsetof(Self, Job);
        return GetField<CIM_ConcreteJob_Class>(n).value;
    }
    
    void Job_value(const CIM_ConcreteJob_Class& x)
    {
        const size_t n = offsetof(Self, Job);
        GetField<CIM_ConcreteJob_Class>(n).Set(x);
    }
    
    bool Job_exists() const
    {
        const size_t n = offsetof(Self, Job);
        return GetField<CIM_ConcreteJob_Class>(n).exists ? true : false;
    }
    
    void Job_clear()
    {
        const size_t n = offsetof(Self, Job);
        GetField<CIM_ConcreteJob_Class>(n).Clear();
    }

    //
    // MySQL_Server_Database_RequestStateChange_Class.TimeoutPeriod
    //
    
    const Field<Datetime>& TimeoutPeriod() const
    {
        const size_t n = offsetof(Self, TimeoutPeriod);
        return GetField<Datetime>(n);
    }
    
    void TimeoutPeriod(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, TimeoutPeriod);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& TimeoutPeriod_value() const
    {
        const size_t n = offsetof(Self, TimeoutPeriod);
        return GetField<Datetime>(n).value;
    }
    
    void TimeoutPeriod_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, TimeoutPeriod);
        GetField<Datetime>(n).Set(x);
    }
    
    bool TimeoutPeriod_exists() const
    {
        const size_t n = offsetof(Self, TimeoutPeriod);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void TimeoutPeriod_clear()
    {
        const size_t n = offsetof(Self, TimeoutPeriod);
        GetField<Datetime>(n).Clear();
    }
};

typedef Array<MySQL_Server_Database_RequestStateChange_Class> MySQL_Server_Database_RequestStateChange_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MySQL_Server_Database_h */
