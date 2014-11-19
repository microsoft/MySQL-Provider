/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MySQL_Server_h
#define _MySQL_Server_h

#include <MI.h>
#include "CIM_InstalledProduct.h"

/*
**==============================================================================
**
** MySQL_Server [MySQL_Server]
**
** Keys:
**    ProductIdentifyingNumber
**    ProductName
**    ProductVendor
**    ProductVersion
**    SystemID
**    CollectionID
**
**==============================================================================
*/

typedef struct _MySQL_Server /* extends CIM_InstalledProduct */
{
    MI_Instance __instance;
    /* CIM_ManagedElement properties */
    MI_ConstStringField InstanceID;
    MI_ConstStringField Caption;
    MI_ConstStringField Description;
    MI_ConstStringField ElementName;
    /* CIM_Collection properties */
    /* CIM_InstalledProduct properties */
    /*KEY*/ MI_ConstStringField ProductIdentifyingNumber;
    /*KEY*/ MI_ConstStringField ProductName;
    /*KEY*/ MI_ConstStringField ProductVendor;
    /*KEY*/ MI_ConstStringField ProductVersion;
    /*KEY*/ MI_ConstStringField SystemID;
    /*KEY*/ MI_ConstStringField CollectionID;
    MI_ConstStringField Name;
    /* MySQL_Server properties */
    MI_ConstStringField ConfigurationFile;
    MI_ConstStringField ErrorLogFile;
    MI_ConstStringField Hostname;
    MI_ConstStringField BindAddress;
    MI_ConstUint16Field Port;
    MI_ConstStringField SocketFile;
    MI_ConstStringField DataDirectory;
    MI_ConstStringField OperatingStatus;
}
MySQL_Server;

typedef struct _MySQL_Server_Ref
{
    MySQL_Server* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_Server_Ref;

typedef struct _MySQL_Server_ConstRef
{
    MI_CONST MySQL_Server* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_Server_ConstRef;

typedef struct _MySQL_Server_Array
{
    struct _MySQL_Server** data;
    MI_Uint32 size;
}
MySQL_Server_Array;

typedef struct _MySQL_Server_ConstArray
{
    struct _MySQL_Server MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MySQL_Server_ConstArray;

typedef struct _MySQL_Server_ArrayRef
{
    MySQL_Server_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_Server_ArrayRef;

typedef struct _MySQL_Server_ConstArrayRef
{
    MySQL_Server_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_Server_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MySQL_Server_rtti;

MI_INLINE MI_Result MI_CALL MySQL_Server_Construct(
    MySQL_Server* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MySQL_Server_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clone(
    const MySQL_Server* self,
    MySQL_Server** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MySQL_Server_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MySQL_Server_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Destruct(MySQL_Server* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Delete(MySQL_Server* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Post(
    const MySQL_Server* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_InstanceID(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_InstanceID(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_InstanceID(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_Caption(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_Caption(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        1,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_Caption(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        1);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_Description(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_Description(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_Description(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_ElementName(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_ElementName(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_ElementName(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_ProductIdentifyingNumber(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_ProductIdentifyingNumber(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_ProductIdentifyingNumber(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_ProductName(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_ProductName(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_ProductName(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_ProductVendor(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_ProductVendor(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        6,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_ProductVendor(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        6);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_ProductVersion(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_ProductVersion(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        7,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_ProductVersion(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        7);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_SystemID(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_SystemID(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        8,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_SystemID(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        8);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_CollectionID(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_CollectionID(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        9,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_CollectionID(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        9);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_Name(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_Name(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        10,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_Name(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        10);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_ConfigurationFile(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_ConfigurationFile(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        11,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_ConfigurationFile(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        11);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_ErrorLogFile(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_ErrorLogFile(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        12,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_ErrorLogFile(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        12);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_Hostname(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_Hostname(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        13,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_Hostname(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        13);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_BindAddress(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_BindAddress(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        14,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_BindAddress(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        14);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_Port(
    MySQL_Server* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Port)->value = x;
    ((MI_Uint16Field*)&self->Port)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_Port(
    MySQL_Server* self)
{
    memset((void*)&self->Port, 0, sizeof(self->Port));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_SocketFile(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_SocketFile(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        16,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_SocketFile(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        16);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_DataDirectory(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_DataDirectory(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        17,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_DataDirectory(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        17);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Set_OperatingStatus(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_SetPtr_OperatingStatus(
    MySQL_Server* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        18,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_Clear_OperatingStatus(
    MySQL_Server* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        18);
}

/*
**==============================================================================
**
** MySQL_Server.UpdateCredentials()
**
**==============================================================================
*/

typedef struct _MySQL_Server_UpdateCredentials
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
    /*IN*/ MI_ConstUint16Field Port;
    /*IN*/ MI_ConstStringField BindAddress;
    /*IN*/ MI_ConstStringField Username;
    /*IN*/ MI_ConstStringField Password;
}
MySQL_Server_UpdateCredentials;

MI_EXTERN_C MI_CONST MI_MethodDecl MySQL_Server_UpdateCredentials_rtti;

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Construct(
    MySQL_Server_UpdateCredentials* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySQL_Server_UpdateCredentials_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Clone(
    const MySQL_Server_UpdateCredentials* self,
    MySQL_Server_UpdateCredentials** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Destruct(
    MySQL_Server_UpdateCredentials* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Delete(
    MySQL_Server_UpdateCredentials* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Post(
    const MySQL_Server_UpdateCredentials* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Set_MIReturn(
    MySQL_Server_UpdateCredentials* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Clear_MIReturn(
    MySQL_Server_UpdateCredentials* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Set_Port(
    MySQL_Server_UpdateCredentials* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Port)->value = x;
    ((MI_Uint16Field*)&self->Port)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Clear_Port(
    MySQL_Server_UpdateCredentials* self)
{
    memset((void*)&self->Port, 0, sizeof(self->Port));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Set_BindAddress(
    MySQL_Server_UpdateCredentials* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_SetPtr_BindAddress(
    MySQL_Server_UpdateCredentials* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Clear_BindAddress(
    MySQL_Server_UpdateCredentials* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Set_Username(
    MySQL_Server_UpdateCredentials* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_SetPtr_Username(
    MySQL_Server_UpdateCredentials* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Clear_Username(
    MySQL_Server_UpdateCredentials* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Set_Password(
    MySQL_Server_UpdateCredentials* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_SetPtr_Password(
    MySQL_Server_UpdateCredentials* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_UpdateCredentials_Clear_Password(
    MySQL_Server_UpdateCredentials* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

/*
**==============================================================================
**
** MySQL_Server.DeleteCredentials()
**
**==============================================================================
*/

typedef struct _MySQL_Server_DeleteCredentials
{
    MI_Instance __instance;
    /*OUT*/ MI_ConstBooleanField MIReturn;
    /*IN*/ MI_ConstUint16Field Port;
}
MySQL_Server_DeleteCredentials;

MI_EXTERN_C MI_CONST MI_MethodDecl MySQL_Server_DeleteCredentials_rtti;

MI_INLINE MI_Result MI_CALL MySQL_Server_DeleteCredentials_Construct(
    MySQL_Server_DeleteCredentials* self,
    MI_Context* context)
{
    return MI_ConstructParameters(context, &MySQL_Server_DeleteCredentials_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_DeleteCredentials_Clone(
    const MySQL_Server_DeleteCredentials* self,
    MySQL_Server_DeleteCredentials** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_DeleteCredentials_Destruct(
    MySQL_Server_DeleteCredentials* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_DeleteCredentials_Delete(
    MySQL_Server_DeleteCredentials* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_DeleteCredentials_Post(
    const MySQL_Server_DeleteCredentials* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_Server_DeleteCredentials_Set_MIReturn(
    MySQL_Server_DeleteCredentials* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->MIReturn)->value = x;
    ((MI_BooleanField*)&self->MIReturn)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_DeleteCredentials_Clear_MIReturn(
    MySQL_Server_DeleteCredentials* self)
{
    memset((void*)&self->MIReturn, 0, sizeof(self->MIReturn));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_DeleteCredentials_Set_Port(
    MySQL_Server_DeleteCredentials* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Port)->value = x;
    ((MI_Uint16Field*)&self->Port)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_Server_DeleteCredentials_Clear_Port(
    MySQL_Server_DeleteCredentials* self)
{
    memset((void*)&self->Port, 0, sizeof(self->Port));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySQL_Server provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MySQL_Server_Self MySQL_Server_Self;

MI_EXTERN_C void MI_CALL MySQL_Server_Load(
    MySQL_Server_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySQL_Server_Unload(
    MySQL_Server_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySQL_Server_EnumerateInstances(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MySQL_Server_GetInstance(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MySQL_Server_CreateInstance(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server* newInstance);

MI_EXTERN_C void MI_CALL MySQL_Server_ModifyInstance(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MySQL_Server_DeleteInstance(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_Server* instanceName);

MI_EXTERN_C void MI_CALL MySQL_Server_Invoke_UpdateCredentials(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySQL_Server* instanceName,
    const MySQL_Server_UpdateCredentials* in);

MI_EXTERN_C void MI_CALL MySQL_Server_Invoke_DeleteCredentials(
    MySQL_Server_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Char* methodName,
    const MySQL_Server* instanceName,
    const MySQL_Server_DeleteCredentials* in);


/*
**==============================================================================
**
** MySQL_Server_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MySQL_Server_Class : public CIM_InstalledProduct_Class
{
public:
    
    typedef MySQL_Server Self;
    
    MySQL_Server_Class() :
        CIM_InstalledProduct_Class(&MySQL_Server_rtti)
    {
    }
    
    MySQL_Server_Class(
        const MySQL_Server* instanceName,
        bool keysOnly) :
        CIM_InstalledProduct_Class(
            &MySQL_Server_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MySQL_Server_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        CIM_InstalledProduct_Class(clDecl, instance, keysOnly)
    {
    }
    
    MySQL_Server_Class(
        const MI_ClassDecl* clDecl) :
        CIM_InstalledProduct_Class(clDecl)
    {
    }
    
    MySQL_Server_Class& operator=(
        const MySQL_Server_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MySQL_Server_Class(
        const MySQL_Server_Class& x) :
        CIM_InstalledProduct_Class(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MySQL_Server_rtti;
    }

    //
    // MySQL_Server_Class.ConfigurationFile
    //
    
    const Field<String>& ConfigurationFile() const
    {
        const size_t n = offsetof(Self, ConfigurationFile);
        return GetField<String>(n);
    }
    
    void ConfigurationFile(const Field<String>& x)
    {
        const size_t n = offsetof(Self, ConfigurationFile);
        GetField<String>(n) = x;
    }
    
    const String& ConfigurationFile_value() const
    {
        const size_t n = offsetof(Self, ConfigurationFile);
        return GetField<String>(n).value;
    }
    
    void ConfigurationFile_value(const String& x)
    {
        const size_t n = offsetof(Self, ConfigurationFile);
        GetField<String>(n).Set(x);
    }
    
    bool ConfigurationFile_exists() const
    {
        const size_t n = offsetof(Self, ConfigurationFile);
        return GetField<String>(n).exists ? true : false;
    }
    
    void ConfigurationFile_clear()
    {
        const size_t n = offsetof(Self, ConfigurationFile);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_Server_Class.ErrorLogFile
    //
    
    const Field<String>& ErrorLogFile() const
    {
        const size_t n = offsetof(Self, ErrorLogFile);
        return GetField<String>(n);
    }
    
    void ErrorLogFile(const Field<String>& x)
    {
        const size_t n = offsetof(Self, ErrorLogFile);
        GetField<String>(n) = x;
    }
    
    const String& ErrorLogFile_value() const
    {
        const size_t n = offsetof(Self, ErrorLogFile);
        return GetField<String>(n).value;
    }
    
    void ErrorLogFile_value(const String& x)
    {
        const size_t n = offsetof(Self, ErrorLogFile);
        GetField<String>(n).Set(x);
    }
    
    bool ErrorLogFile_exists() const
    {
        const size_t n = offsetof(Self, ErrorLogFile);
        return GetField<String>(n).exists ? true : false;
    }
    
    void ErrorLogFile_clear()
    {
        const size_t n = offsetof(Self, ErrorLogFile);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_Server_Class.Hostname
    //
    
    const Field<String>& Hostname() const
    {
        const size_t n = offsetof(Self, Hostname);
        return GetField<String>(n);
    }
    
    void Hostname(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Hostname);
        GetField<String>(n) = x;
    }
    
    const String& Hostname_value() const
    {
        const size_t n = offsetof(Self, Hostname);
        return GetField<String>(n).value;
    }
    
    void Hostname_value(const String& x)
    {
        const size_t n = offsetof(Self, Hostname);
        GetField<String>(n).Set(x);
    }
    
    bool Hostname_exists() const
    {
        const size_t n = offsetof(Self, Hostname);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Hostname_clear()
    {
        const size_t n = offsetof(Self, Hostname);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_Server_Class.BindAddress
    //
    
    const Field<String>& BindAddress() const
    {
        const size_t n = offsetof(Self, BindAddress);
        return GetField<String>(n);
    }
    
    void BindAddress(const Field<String>& x)
    {
        const size_t n = offsetof(Self, BindAddress);
        GetField<String>(n) = x;
    }
    
    const String& BindAddress_value() const
    {
        const size_t n = offsetof(Self, BindAddress);
        return GetField<String>(n).value;
    }
    
    void BindAddress_value(const String& x)
    {
        const size_t n = offsetof(Self, BindAddress);
        GetField<String>(n).Set(x);
    }
    
    bool BindAddress_exists() const
    {
        const size_t n = offsetof(Self, BindAddress);
        return GetField<String>(n).exists ? true : false;
    }
    
    void BindAddress_clear()
    {
        const size_t n = offsetof(Self, BindAddress);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_Server_Class.Port
    //
    
    const Field<Uint16>& Port() const
    {
        const size_t n = offsetof(Self, Port);
        return GetField<Uint16>(n);
    }
    
    void Port(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, Port);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& Port_value() const
    {
        const size_t n = offsetof(Self, Port);
        return GetField<Uint16>(n).value;
    }
    
    void Port_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, Port);
        GetField<Uint16>(n).Set(x);
    }
    
    bool Port_exists() const
    {
        const size_t n = offsetof(Self, Port);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void Port_clear()
    {
        const size_t n = offsetof(Self, Port);
        GetField<Uint16>(n).Clear();
    }

    //
    // MySQL_Server_Class.SocketFile
    //
    
    const Field<String>& SocketFile() const
    {
        const size_t n = offsetof(Self, SocketFile);
        return GetField<String>(n);
    }
    
    void SocketFile(const Field<String>& x)
    {
        const size_t n = offsetof(Self, SocketFile);
        GetField<String>(n) = x;
    }
    
    const String& SocketFile_value() const
    {
        const size_t n = offsetof(Self, SocketFile);
        return GetField<String>(n).value;
    }
    
    void SocketFile_value(const String& x)
    {
        const size_t n = offsetof(Self, SocketFile);
        GetField<String>(n).Set(x);
    }
    
    bool SocketFile_exists() const
    {
        const size_t n = offsetof(Self, SocketFile);
        return GetField<String>(n).exists ? true : false;
    }
    
    void SocketFile_clear()
    {
        const size_t n = offsetof(Self, SocketFile);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_Server_Class.DataDirectory
    //
    
    const Field<String>& DataDirectory() const
    {
        const size_t n = offsetof(Self, DataDirectory);
        return GetField<String>(n);
    }
    
    void DataDirectory(const Field<String>& x)
    {
        const size_t n = offsetof(Self, DataDirectory);
        GetField<String>(n) = x;
    }
    
    const String& DataDirectory_value() const
    {
        const size_t n = offsetof(Self, DataDirectory);
        return GetField<String>(n).value;
    }
    
    void DataDirectory_value(const String& x)
    {
        const size_t n = offsetof(Self, DataDirectory);
        GetField<String>(n).Set(x);
    }
    
    bool DataDirectory_exists() const
    {
        const size_t n = offsetof(Self, DataDirectory);
        return GetField<String>(n).exists ? true : false;
    }
    
    void DataDirectory_clear()
    {
        const size_t n = offsetof(Self, DataDirectory);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_Server_Class.OperatingStatus
    //
    
    const Field<String>& OperatingStatus() const
    {
        const size_t n = offsetof(Self, OperatingStatus);
        return GetField<String>(n);
    }
    
    void OperatingStatus(const Field<String>& x)
    {
        const size_t n = offsetof(Self, OperatingStatus);
        GetField<String>(n) = x;
    }
    
    const String& OperatingStatus_value() const
    {
        const size_t n = offsetof(Self, OperatingStatus);
        return GetField<String>(n).value;
    }
    
    void OperatingStatus_value(const String& x)
    {
        const size_t n = offsetof(Self, OperatingStatus);
        GetField<String>(n).Set(x);
    }
    
    bool OperatingStatus_exists() const
    {
        const size_t n = offsetof(Self, OperatingStatus);
        return GetField<String>(n).exists ? true : false;
    }
    
    void OperatingStatus_clear()
    {
        const size_t n = offsetof(Self, OperatingStatus);
        GetField<String>(n).Clear();
    }
};

typedef Array<MySQL_Server_Class> MySQL_Server_ClassA;

class MySQL_Server_UpdateCredentials_Class : public Instance
{
public:
    
    typedef MySQL_Server_UpdateCredentials Self;
    
    MySQL_Server_UpdateCredentials_Class() :
        Instance(&MySQL_Server_UpdateCredentials_rtti)
    {
    }
    
    MySQL_Server_UpdateCredentials_Class(
        const MySQL_Server_UpdateCredentials* instanceName,
        bool keysOnly) :
        Instance(
            &MySQL_Server_UpdateCredentials_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MySQL_Server_UpdateCredentials_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MySQL_Server_UpdateCredentials_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MySQL_Server_UpdateCredentials_Class& operator=(
        const MySQL_Server_UpdateCredentials_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MySQL_Server_UpdateCredentials_Class(
        const MySQL_Server_UpdateCredentials_Class& x) :
        Instance(x)
    {
    }

    //
    // MySQL_Server_UpdateCredentials_Class.MIReturn
    //
    
    const Field<Boolean>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Boolean>(n);
    }
    
    void MIReturn(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Boolean>(n).value;
    }
    
    void MIReturn_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Boolean>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Boolean>(n).Clear();
    }

    //
    // MySQL_Server_UpdateCredentials_Class.Port
    //
    
    const Field<Uint16>& Port() const
    {
        const size_t n = offsetof(Self, Port);
        return GetField<Uint16>(n);
    }
    
    void Port(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, Port);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& Port_value() const
    {
        const size_t n = offsetof(Self, Port);
        return GetField<Uint16>(n).value;
    }
    
    void Port_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, Port);
        GetField<Uint16>(n).Set(x);
    }
    
    bool Port_exists() const
    {
        const size_t n = offsetof(Self, Port);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void Port_clear()
    {
        const size_t n = offsetof(Self, Port);
        GetField<Uint16>(n).Clear();
    }

    //
    // MySQL_Server_UpdateCredentials_Class.BindAddress
    //
    
    const Field<String>& BindAddress() const
    {
        const size_t n = offsetof(Self, BindAddress);
        return GetField<String>(n);
    }
    
    void BindAddress(const Field<String>& x)
    {
        const size_t n = offsetof(Self, BindAddress);
        GetField<String>(n) = x;
    }
    
    const String& BindAddress_value() const
    {
        const size_t n = offsetof(Self, BindAddress);
        return GetField<String>(n).value;
    }
    
    void BindAddress_value(const String& x)
    {
        const size_t n = offsetof(Self, BindAddress);
        GetField<String>(n).Set(x);
    }
    
    bool BindAddress_exists() const
    {
        const size_t n = offsetof(Self, BindAddress);
        return GetField<String>(n).exists ? true : false;
    }
    
    void BindAddress_clear()
    {
        const size_t n = offsetof(Self, BindAddress);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_Server_UpdateCredentials_Class.Username
    //
    
    const Field<String>& Username() const
    {
        const size_t n = offsetof(Self, Username);
        return GetField<String>(n);
    }
    
    void Username(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Username);
        GetField<String>(n) = x;
    }
    
    const String& Username_value() const
    {
        const size_t n = offsetof(Self, Username);
        return GetField<String>(n).value;
    }
    
    void Username_value(const String& x)
    {
        const size_t n = offsetof(Self, Username);
        GetField<String>(n).Set(x);
    }
    
    bool Username_exists() const
    {
        const size_t n = offsetof(Self, Username);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Username_clear()
    {
        const size_t n = offsetof(Self, Username);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_Server_UpdateCredentials_Class.Password
    //
    
    const Field<String>& Password() const
    {
        const size_t n = offsetof(Self, Password);
        return GetField<String>(n);
    }
    
    void Password(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Password);
        GetField<String>(n) = x;
    }
    
    const String& Password_value() const
    {
        const size_t n = offsetof(Self, Password);
        return GetField<String>(n).value;
    }
    
    void Password_value(const String& x)
    {
        const size_t n = offsetof(Self, Password);
        GetField<String>(n).Set(x);
    }
    
    bool Password_exists() const
    {
        const size_t n = offsetof(Self, Password);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Password_clear()
    {
        const size_t n = offsetof(Self, Password);
        GetField<String>(n).Clear();
    }
};

typedef Array<MySQL_Server_UpdateCredentials_Class> MySQL_Server_UpdateCredentials_ClassA;

class MySQL_Server_DeleteCredentials_Class : public Instance
{
public:
    
    typedef MySQL_Server_DeleteCredentials Self;
    
    MySQL_Server_DeleteCredentials_Class() :
        Instance(&MySQL_Server_DeleteCredentials_rtti)
    {
    }
    
    MySQL_Server_DeleteCredentials_Class(
        const MySQL_Server_DeleteCredentials* instanceName,
        bool keysOnly) :
        Instance(
            &MySQL_Server_DeleteCredentials_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MySQL_Server_DeleteCredentials_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MySQL_Server_DeleteCredentials_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MySQL_Server_DeleteCredentials_Class& operator=(
        const MySQL_Server_DeleteCredentials_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MySQL_Server_DeleteCredentials_Class(
        const MySQL_Server_DeleteCredentials_Class& x) :
        Instance(x)
    {
    }

    //
    // MySQL_Server_DeleteCredentials_Class.MIReturn
    //
    
    const Field<Boolean>& MIReturn() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Boolean>(n);
    }
    
    void MIReturn(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& MIReturn_value() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Boolean>(n).value;
    }
    
    void MIReturn_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Boolean>(n).Set(x);
    }
    
    bool MIReturn_exists() const
    {
        const size_t n = offsetof(Self, MIReturn);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void MIReturn_clear()
    {
        const size_t n = offsetof(Self, MIReturn);
        GetField<Boolean>(n).Clear();
    }

    //
    // MySQL_Server_DeleteCredentials_Class.Port
    //
    
    const Field<Uint16>& Port() const
    {
        const size_t n = offsetof(Self, Port);
        return GetField<Uint16>(n);
    }
    
    void Port(const Field<Uint16>& x)
    {
        const size_t n = offsetof(Self, Port);
        GetField<Uint16>(n) = x;
    }
    
    const Uint16& Port_value() const
    {
        const size_t n = offsetof(Self, Port);
        return GetField<Uint16>(n).value;
    }
    
    void Port_value(const Uint16& x)
    {
        const size_t n = offsetof(Self, Port);
        GetField<Uint16>(n).Set(x);
    }
    
    bool Port_exists() const
    {
        const size_t n = offsetof(Self, Port);
        return GetField<Uint16>(n).exists ? true : false;
    }
    
    void Port_clear()
    {
        const size_t n = offsetof(Self, Port);
        GetField<Uint16>(n).Clear();
    }
};

typedef Array<MySQL_Server_DeleteCredentials_Class> MySQL_Server_DeleteCredentials_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MySQL_Server_h */
