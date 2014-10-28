/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _CIM_CommonDatabase_h
#define _CIM_CommonDatabase_h

#include <MI.h>
#include "CIM_EnabledLogicalElement.h"
#include "CIM_ConcreteJob.h"

/*
**==============================================================================
**
** CIM_CommonDatabase [CIM_CommonDatabase]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _CIM_CommonDatabase /* extends CIM_EnabledLogicalElement */
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
}
CIM_CommonDatabase;

typedef struct _CIM_CommonDatabase_Ref
{
    CIM_CommonDatabase* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_CommonDatabase_Ref;

typedef struct _CIM_CommonDatabase_ConstRef
{
    MI_CONST CIM_CommonDatabase* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_CommonDatabase_ConstRef;

typedef struct _CIM_CommonDatabase_Array
{
    struct _CIM_CommonDatabase** data;
    MI_Uint32 size;
}
CIM_CommonDatabase_Array;

typedef struct _CIM_CommonDatabase_ConstArray
{
    struct _CIM_CommonDatabase MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
CIM_CommonDatabase_ConstArray;

typedef struct _CIM_CommonDatabase_ArrayRef
{
    CIM_CommonDatabase_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_CommonDatabase_ArrayRef;

typedef struct _CIM_CommonDatabase_ConstArrayRef
{
    CIM_CommonDatabase_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
CIM_CommonDatabase_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl CIM_CommonDatabase_rtti;

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Construct(
    CIM_CommonDatabase* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &CIM_CommonDatabase_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clone(
    const CIM_CommonDatabase* self,
    CIM_CommonDatabase** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL CIM_CommonDatabase_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &CIM_CommonDatabase_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Destruct(CIM_CommonDatabase* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Delete(CIM_CommonDatabase* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Post(
    const CIM_CommonDatabase* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_InstanceID(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_InstanceID(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_InstanceID(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_Caption(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_Caption(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_Caption(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_Description(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_Description(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_Description(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_ElementName(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_ElementName(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_ElementName(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_InstallDate(
    CIM_CommonDatabase* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->InstallDate)->value = x;
    ((MI_DatetimeField*)&self->InstallDate)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_InstallDate(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->InstallDate, 0, sizeof(self->InstallDate));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_Name(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_Name(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_Name(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_OperationalStatus(
    CIM_CommonDatabase* self,
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

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_OperationalStatus(
    CIM_CommonDatabase* self,
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

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_OperationalStatus(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_StatusDescriptions(
    CIM_CommonDatabase* self,
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

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_StatusDescriptions(
    CIM_CommonDatabase* self,
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

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_StatusDescriptions(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_Status(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_Status(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_Status(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_HealthState(
    CIM_CommonDatabase* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->HealthState)->value = x;
    ((MI_Uint16Field*)&self->HealthState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_HealthState(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->HealthState, 0, sizeof(self->HealthState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_CommunicationStatus(
    CIM_CommonDatabase* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->CommunicationStatus)->value = x;
    ((MI_Uint16Field*)&self->CommunicationStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_CommunicationStatus(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->CommunicationStatus, 0, sizeof(self->CommunicationStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_DetailedStatus(
    CIM_CommonDatabase* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->DetailedStatus)->value = x;
    ((MI_Uint16Field*)&self->DetailedStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_DetailedStatus(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->DetailedStatus, 0, sizeof(self->DetailedStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_OperatingStatus(
    CIM_CommonDatabase* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->OperatingStatus)->value = x;
    ((MI_Uint16Field*)&self->OperatingStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_OperatingStatus(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->OperatingStatus, 0, sizeof(self->OperatingStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_PrimaryStatus(
    CIM_CommonDatabase* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->PrimaryStatus)->value = x;
    ((MI_Uint16Field*)&self->PrimaryStatus)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_PrimaryStatus(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->PrimaryStatus, 0, sizeof(self->PrimaryStatus));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_EnabledState(
    CIM_CommonDatabase* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledState)->value = x;
    ((MI_Uint16Field*)&self->EnabledState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_EnabledState(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->EnabledState, 0, sizeof(self->EnabledState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_OtherEnabledState(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_OtherEnabledState(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        15,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_OtherEnabledState(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        15);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_RequestedState(
    CIM_CommonDatabase* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_RequestedState(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_EnabledDefault(
    CIM_CommonDatabase* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->EnabledDefault)->value = x;
    ((MI_Uint16Field*)&self->EnabledDefault)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_EnabledDefault(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->EnabledDefault, 0, sizeof(self->EnabledDefault));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_TimeOfLastStateChange(
    CIM_CommonDatabase* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->value = x;
    ((MI_DatetimeField*)&self->TimeOfLastStateChange)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_TimeOfLastStateChange(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->TimeOfLastStateChange, 0, sizeof(self->TimeOfLastStateChange));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_AvailableRequestedStates(
    CIM_CommonDatabase* self,
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

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_AvailableRequestedStates(
    CIM_CommonDatabase* self,
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

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_AvailableRequestedStates(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        19);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_TransitioningToState(
    CIM_CommonDatabase* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->TransitioningToState)->value = x;
    ((MI_Uint16Field*)&self->TransitioningToState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_TransitioningToState(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->TransitioningToState, 0, sizeof(self->TransitioningToState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_DatabaseVersion(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_SetPtr_DatabaseVersion(
    CIM_CommonDatabase* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        21,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_DatabaseVersion(
    CIM_CommonDatabase* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        21);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_LastBackup(
    CIM_CommonDatabase* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->LastBackup)->value = x;
    ((MI_DatetimeField*)&self->LastBackup)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_LastBackup(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->LastBackup, 0, sizeof(self->LastBackup));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_SizeAllocated(
    CIM_CommonDatabase* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->SizeAllocated)->value = x;
    ((MI_Uint32Field*)&self->SizeAllocated)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_SizeAllocated(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->SizeAllocated, 0, sizeof(self->SizeAllocated));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Set_SizeUnits(
    CIM_CommonDatabase* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->SizeUnits)->value = x;
    ((MI_Uint16Field*)&self->SizeUnits)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_Clear_SizeUnits(
    CIM_CommonDatabase* self)
{
    memset((void*)&self->SizeUnits, 0, sizeof(self->SizeUnits));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** CIM_CommonDatabase.RequestStateChange()
**
**==============================================================================
*/

typedef struct _CIM_CommonDatabase_RequestStateChange
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstUint32Field MIReturn;
    /*IN*/ MI_ConstUint16Field RequestedState;
    /*OUT*/ CIM_ConcreteJob_ConstRef Job;
    /*IN*/ MI_ConstDatetimeField TimeoutPeriod;
}
CIM_CommonDatabase_RequestStateChange;

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_RequestStateChange_Set_MIReturn(
    CIM_CommonDatabase_RequestStateChange* self,
    MI_Uint32 x)
{
    ((MI_Uint32Field*)&self->MIReturn)->value = x;
    ((MI_Uint32Field*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_RequestStateChange_Clear_MIReturn(
    CIM_CommonDatabase_RequestStateChange* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_RequestStateChange_Set_RequestedState(
    CIM_CommonDatabase_RequestStateChange* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->RequestedState)->value = x;
    ((MI_Uint16Field*)&self->RequestedState)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_RequestStateChange_Clear_RequestedState(
    CIM_CommonDatabase_RequestStateChange* self)
{
    memset((void*)&self->RequestedState, 0, sizeof(self->RequestedState));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_RequestStateChange_Set_Job(
    CIM_CommonDatabase_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        0);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_RequestStateChange_SetPtr_Job(
    CIM_CommonDatabase_RequestStateChange* self,
    const CIM_ConcreteJob* x)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&x,
        MI_REFERENCE,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_RequestStateChange_Clear_Job(
    CIM_CommonDatabase_RequestStateChange* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_RequestStateChange_Set_TimeoutPeriod(
    CIM_CommonDatabase_RequestStateChange* self,
    MI_Datetime x)
{
    ((MI_DatetimeField*)&self->TimeoutPeriod)->value = x;
    ((MI_DatetimeField*)&self->TimeoutPeriod)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL CIM_CommonDatabase_RequestStateChange_Clear_TimeoutPeriod(
    CIM_CommonDatabase_RequestStateChange* self)
{
    memset((void*)&self->TimeoutPeriod, 0, sizeof(self->TimeoutPeriod));
    return MI_RESULT_OK;
}


/*
**==============================================================================
**
** CIM_CommonDatabase_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class CIM_CommonDatabase_Class : public CIM_EnabledLogicalElement_Class
{
public:
    
    typedef CIM_CommonDatabase Self;
    
    CIM_CommonDatabase_Class() :
        CIM_EnabledLogicalElement_Class(&CIM_CommonDatabase_rtti)
    {
    }
    
    CIM_CommonDatabase_Class(
        const CIM_CommonDatabase* instanceName,
        bool keysOnly) :
        CIM_EnabledLogicalElement_Class(
            &CIM_CommonDatabase_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    CIM_CommonDatabase_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_EnabledLogicalElement_Class(clDecl, instance, keysOnly)
    {
    }
    
    CIM_CommonDatabase_Class(
        const MI_ClassDecl* clDecl) :
        CIM_EnabledLogicalElement_Class(clDecl)
    {
    }
    
    CIM_CommonDatabase_Class& operator=(
        const CIM_CommonDatabase_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    CIM_CommonDatabase_Class(
        const CIM_CommonDatabase_Class& x) :
        CIM_EnabledLogicalElement_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &CIM_CommonDatabase_rtti;
    }

    //
    // CIM_CommonDatabase_Class.DatabaseVersion
    //
    
    const Field<String>& DatabaseVersion() const
    {
        const size_t n = offsetof(Self, DatabaseVersion);
        return GetField<String>(n);
    }
    
    void DatabaseVersion(const Field<String>& x)
    {
        const size_t n = offsetof(Self, DatabaseVersion);
        GetField<String>(n) = x;
    }
    
    const String& DatabaseVersion_value() const
    {
        const size_t n = offsetof(Self, DatabaseVersion);
        return GetField<String>(n).value;
    }
    
    void DatabaseVersion_value(const String& x)
    {
        const size_t n = offsetof(Self, DatabaseVersion);
        GetField<String>(n).Set(x);
    }
    
    bool DatabaseVersion_exists() const
    {
        const size_t n = offsetof(Self, DatabaseVersion);
        return GetField<String>(n).exists ? true : false;
    }
    
    void DatabaseVersion_clear()
    {
        const size_t n = offsetof(Self, DatabaseVersion);
        GetField<String>(n).Clear();
    }

    //
    // CIM_CommonDatabase_Class.LastBackup
    //
    
    const Field<Datetime>& LastBackup() const
    {
        const size_t n = offsetof(Self, LastBackup);
        return GetField<Datetime>(n);
    }
    
    void LastBackup(const Field<Datetime>& x)
    {
        const size_t n = offsetof(Self, LastBackup);
        GetField<Datetime>(n) = x;
    }
    
    const Datetime& LastBackup_value() const
    {
        const size_t n = offsetof(Self, LastBackup);
        return GetField<Datetime>(n).value;
    }
    
    void LastBackup_value(const Datetime& x)
    {
        const size_t n = offsetof(Self, LastBackup);
        GetField<Datetime>(n).Set(x);
    }
    
    bool LastBackup_exists() const
    {
        const size_t n = offsetof(Self, LastBackup);
        return GetField<Datetime>(n).exists ? true : false;
    }
    
    void LastBackup_clear()
    {
        const size_t n = offsetof(Self, LastBackup);
        GetField<Datetime>(n).Clear();
    }

    //
    // CIM_CommonDatabase_Class.SizeAllocated
    //
    
    const Field<Uint32>& SizeAllocated() const
    {
        const size_t n = offsetof(Self, SizeAllocated);
        return GetField<Uint32>(n);
    }
    
    void SizeAllocated(const Field<Uint32>& x)
    {
        const size_t n = offsetof(Self, SizeAllocated);
        GetField<Uint32>(n) = x;
    }
    
    const Uint32& SizeAllocated_value() const
    {
        const size_t n = offsetof(Self, SizeAllocated);
        return GetField<Uint32>(n).value;
    }
    
    void SizeAllocated_value(const Uint32& x)
    {
        const size_t n = offsetof(Self, SizeAllocated);
        GetField<Uint32>(n).Set(x);
    }
    
    bool SizeAllocated_exists() const
    {
        const size_t n = offsetof(Self, SizeAllocated);
        return GetField<Uint32>(n).exists ? true : false;
    }
    
    void SizeAllocated_clear()
    {
        const size_t n = offsetof(Self, SizeAllocated);
        GetField<Uint32>(n).Clear();
    }

    //
    // CIM_CommonDatabase_Class.SizeUnits
    //
    
    const Field<Uint16>& SizeUnits() const
    {
        const size_t n = offsetof(Self, SizeUnits);
        return GetField<Uint16>(n);
    }
    
    void SizeUnits(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, SizeUnits);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& SizeUnits_value() const
    {
        const size_t n = offsetof(Self, SizeUnits);
        return GetField<Uint16>(n).value;
    }
    
    void SizeUnits_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, SizeUnits);
        GetField<Uint16>(n).Set(x);
    }
    
    bool SizeUnits_exists() const
    {
        const size_t n = offsetof(Self, SizeUnits);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void SizeUnits_clear()
    {
        const size_t n = offsetof(Self, SizeUnits);
        GetField<Uint16>(n).Clear();
    }
};

typedef Array<CIM_CommonDatabase_Class> CIM_CommonDatabase_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _CIM_CommonDatabase_h */
