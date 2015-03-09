/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#ifndef _MySQL_StoredProcedureRow_AsXML_h
#define _MySQL_StoredProcedureRow_AsXML_h

#include <MI.h>

/*
**==============================================================================
**
** MySQL_StoredProcedureRow_AsXML [MySQL_StoredProcedureRow_AsXML]
**
** Keys:
**    InstanceID
**
**==============================================================================
*/

typedef struct _MySQL_StoredProcedureRow_AsXML
{
    MI_Instance __instance;
    /* MySQL_StoredProcedureRow_AsXML properties */
    /*KEY*/ MI_ConstStringField InstanceID;
    MI_ConstUint16Field Port;
    MI_ConstStringField DatabaseName;
    MI_ConstStringField StoredProcedureName;
    MI_ConstStringField Parameters;
    MI_ConstStringField RowXMLValue;
    MI_ConstBooleanField IsTruncated;
}
MySQL_StoredProcedureRow_AsXML;

typedef struct _MySQL_StoredProcedureRow_AsXML_Ref
{
    MySQL_StoredProcedureRow_AsXML* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_StoredProcedureRow_AsXML_Ref;

typedef struct _MySQL_StoredProcedureRow_AsXML_ConstRef
{
    MI_CONST MySQL_StoredProcedureRow_AsXML* value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_StoredProcedureRow_AsXML_ConstRef;

typedef struct _MySQL_StoredProcedureRow_AsXML_Array
{
    struct _MySQL_StoredProcedureRow_AsXML** data;
    MI_Uint32 size;
}
MySQL_StoredProcedureRow_AsXML_Array;

typedef struct _MySQL_StoredProcedureRow_AsXML_ConstArray
{
    struct _MySQL_StoredProcedureRow_AsXML MI_CONST* MI_CONST* data;
    MI_Uint32 size;
}
MySQL_StoredProcedureRow_AsXML_ConstArray;

typedef struct _MySQL_StoredProcedureRow_AsXML_ArrayRef
{
    MySQL_StoredProcedureRow_AsXML_Array value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_StoredProcedureRow_AsXML_ArrayRef;

typedef struct _MySQL_StoredProcedureRow_AsXML_ConstArrayRef
{
    MySQL_StoredProcedureRow_AsXML_ConstArray value;
    MI_Boolean exists;
    MI_Uint8 flags;
}
MySQL_StoredProcedureRow_AsXML_ConstArrayRef;

MI_EXTERN_C MI_CONST MI_ClassDecl MySQL_StoredProcedureRow_AsXML_rtti;

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Construct(
    MySQL_StoredProcedureRow_AsXML* self,
    MI_Context* context)
{
    return MI_ConstructInstance(context, &MySQL_StoredProcedureRow_AsXML_rtti,
        (MI_Instance*)&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Clone(
    const MySQL_StoredProcedureRow_AsXML* self,
    MySQL_StoredProcedureRow_AsXML** newInstance)
{
    return MI_Instance_Clone(
        &self->__instance, (MI_Instance**)newInstance);
}

MI_INLINE MI_Boolean MI_CALL MySQL_StoredProcedureRow_AsXML_IsA(
    const MI_Instance* self)
{
    MI_Boolean res = MI_FALSE;
    return MI_Instance_IsA(self, &MySQL_StoredProcedureRow_AsXML_rtti, &res) == MI_RESULT_OK && res;
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Destruct(MySQL_StoredProcedureRow_AsXML* self)
{
    return MI_Instance_Destruct(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Delete(MySQL_StoredProcedureRow_AsXML* self)
{
    return MI_Instance_Delete(&self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Post(
    const MySQL_StoredProcedureRow_AsXML* self,
    MI_Context* context)
{
    return MI_PostInstance(context, &self->__instance);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Set_InstanceID(
    MySQL_StoredProcedureRow_AsXML* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_SetPtr_InstanceID(
    MySQL_StoredProcedureRow_AsXML* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        0,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Clear_InstanceID(
    MySQL_StoredProcedureRow_AsXML* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Set_Port(
    MySQL_StoredProcedureRow_AsXML* self,
    MI_Uint16 x)
{
    ((MI_Uint16Field*)&self->Port)->value = x;
    ((MI_Uint16Field*)&self->Port)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Clear_Port(
    MySQL_StoredProcedureRow_AsXML* self)
{
    memset((void*)&self->Port, 0, sizeof(self->Port));
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Set_DatabaseName(
    MySQL_StoredProcedureRow_AsXML* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_SetPtr_DatabaseName(
    MySQL_StoredProcedureRow_AsXML* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        2,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Clear_DatabaseName(
    MySQL_StoredProcedureRow_AsXML* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        2);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Set_StoredProcedureName(
    MySQL_StoredProcedureRow_AsXML* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_SetPtr_StoredProcedureName(
    MySQL_StoredProcedureRow_AsXML* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        3,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Clear_StoredProcedureName(
    MySQL_StoredProcedureRow_AsXML* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        3);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Set_Parameters(
    MySQL_StoredProcedureRow_AsXML* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_SetPtr_Parameters(
    MySQL_StoredProcedureRow_AsXML* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        4,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Clear_Parameters(
    MySQL_StoredProcedureRow_AsXML* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        4);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Set_RowXMLValue(
    MySQL_StoredProcedureRow_AsXML* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        0);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_SetPtr_RowXMLValue(
    MySQL_StoredProcedureRow_AsXML* self,
    const MI_Char* str)
{
    return self->__instance.ft->SetElementAt(
        (MI_Instance*)&self->__instance,
        5,
        (MI_Value*)&str,
        MI_STRING,
        MI_FLAG_BORROW);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Clear_RowXMLValue(
    MySQL_StoredProcedureRow_AsXML* self)
{
    return self->__instance.ft->ClearElementAt(
        (MI_Instance*)&self->__instance,
        5);
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Set_IsTruncated(
    MySQL_StoredProcedureRow_AsXML* self,
    MI_Boolean x)
{
    ((MI_BooleanField*)&self->IsTruncated)->value = x;
    ((MI_BooleanField*)&self->IsTruncated)->exists = 1;
    return MI_RESULT_OK;
}

MI_INLINE MI_Result MI_CALL MySQL_StoredProcedureRow_AsXML_Clear_IsTruncated(
    MySQL_StoredProcedureRow_AsXML* self)
{
    memset((void*)&self->IsTruncated, 0, sizeof(self->IsTruncated));
    return MI_RESULT_OK;
}

/*
**==============================================================================
**
** MySQL_StoredProcedureRow_AsXML provider function prototypes
**
**==============================================================================
*/

/* The developer may optionally define this structure */
typedef struct _MySQL_StoredProcedureRow_AsXML_Self MySQL_StoredProcedureRow_AsXML_Self;

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_Load(
    MySQL_StoredProcedureRow_AsXML_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_Unload(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context);

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_EnumerateInstances(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_PropertySet* propertySet,
    MI_Boolean keysOnly,
    const MI_Filter* filter);

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_GetInstance(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_StoredProcedureRow_AsXML* instanceName,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_CreateInstance(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_StoredProcedureRow_AsXML* newInstance);

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_ModifyInstance(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_StoredProcedureRow_AsXML* modifiedInstance,
    const MI_PropertySet* propertySet);

MI_EXTERN_C void MI_CALL MySQL_StoredProcedureRow_AsXML_DeleteInstance(
    MySQL_StoredProcedureRow_AsXML_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MySQL_StoredProcedureRow_AsXML* instanceName);


/*
**==============================================================================
**
** MySQL_StoredProcedureRow_AsXML_Class
**
**==============================================================================
*/

#ifdef __cplusplus
# include <micxx/micxx.h>

MI_BEGIN_NAMESPACE

class MySQL_StoredProcedureRow_AsXML_Class : public Instance
{
public:
    
    typedef MySQL_StoredProcedureRow_AsXML Self;
    
    MySQL_StoredProcedureRow_AsXML_Class() :
        Instance(&MySQL_StoredProcedureRow_AsXML_rtti)
    {
    }
    
    MySQL_StoredProcedureRow_AsXML_Class(
        const MySQL_StoredProcedureRow_AsXML* instanceName,
        bool keysOnly) :
        Instance(
            &MySQL_StoredProcedureRow_AsXML_rtti,
            &instanceName->__instance,
            keysOnly)
    {
    }
    
    MySQL_StoredProcedureRow_AsXML_Class(
        const MI_ClassDecl* clDecl,
        const MI_Instance* instance,
        bool keysOnly) :
        Instance(clDecl, instance, keysOnly)
    {
    }
    
    MySQL_StoredProcedureRow_AsXML_Class(
        const MI_ClassDecl* clDecl) :
        Instance(clDecl)
    {
    }
    
    MySQL_StoredProcedureRow_AsXML_Class& operator=(
        const MySQL_StoredProcedureRow_AsXML_Class& x)
    {
        CopyRef(x);
        return *this;
    }
    
    MySQL_StoredProcedureRow_AsXML_Class(
        const MySQL_StoredProcedureRow_AsXML_Class& x) :
        Instance(x)
    {
    }

    static const MI_ClassDecl* GetClassDecl()
    {
        return &MySQL_StoredProcedureRow_AsXML_rtti;
    }

    //
    // MySQL_StoredProcedureRow_AsXML_Class.InstanceID
    //
    
    const Field<String>& InstanceID() const
    {
        const size_t n = offsetof(Self, InstanceID);
        return GetField<String>(n);
    }
    
    void InstanceID(const Field<String>& x)
    {
        const size_t n = offsetof(Self, InstanceID);
        GetField<String>(n) = x;
    }
    
    const String& InstanceID_value() const
    {
        const size_t n = offsetof(Self, InstanceID);
        return GetField<String>(n).value;
    }
    
    void InstanceID_value(const String& x)
    {
        const size_t n = offsetof(Self, InstanceID);
        GetField<String>(n).Set(x);
    }
    
    bool InstanceID_exists() const
    {
        const size_t n = offsetof(Self, InstanceID);
        return GetField<String>(n).exists ? true : false;
    }
    
    void InstanceID_clear()
    {
        const size_t n = offsetof(Self, InstanceID);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_StoredProcedureRow_AsXML_Class.Port
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
    // MySQL_StoredProcedureRow_AsXML_Class.DatabaseName
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
    // MySQL_StoredProcedureRow_AsXML_Class.StoredProcedureName
    //
    
    const Field<String>& StoredProcedureName() const
    {
        const size_t n = offsetof(Self, StoredProcedureName);
        return GetField<String>(n);
    }
    
    void StoredProcedureName(const Field<String>& x)
    {
        const size_t n = offsetof(Self, StoredProcedureName);
        GetField<String>(n) = x;
    }
    
    const String& StoredProcedureName_value() const
    {
        const size_t n = offsetof(Self, StoredProcedureName);
        return GetField<String>(n).value;
    }
    
    void StoredProcedureName_value(const String& x)
    {
        const size_t n = offsetof(Self, StoredProcedureName);
        GetField<String>(n).Set(x);
    }
    
    bool StoredProcedureName_exists() const
    {
        const size_t n = offsetof(Self, StoredProcedureName);
        return GetField<String>(n).exists ? true : false;
    }
    
    void StoredProcedureName_clear()
    {
        const size_t n = offsetof(Self, StoredProcedureName);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_StoredProcedureRow_AsXML_Class.Parameters
    //
    
    const Field<String>& Parameters() const
    {
        const size_t n = offsetof(Self, Parameters);
        return GetField<String>(n);
    }
    
    void Parameters(const Field<String>& x)
    {
        const size_t n = offsetof(Self, Parameters);
        GetField<String>(n) = x;
    }
    
    const String& Parameters_value() const
    {
        const size_t n = offsetof(Self, Parameters);
        return GetField<String>(n).value;
    }
    
    void Parameters_value(const String& x)
    {
        const size_t n = offsetof(Self, Parameters);
        GetField<String>(n).Set(x);
    }
    
    bool Parameters_exists() const
    {
        const size_t n = offsetof(Self, Parameters);
        return GetField<String>(n).exists ? true : false;
    }
    
    void Parameters_clear()
    {
        const size_t n = offsetof(Self, Parameters);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_StoredProcedureRow_AsXML_Class.RowXMLValue
    //
    
    const Field<String>& RowXMLValue() const
    {
        const size_t n = offsetof(Self, RowXMLValue);
        return GetField<String>(n);
    }
    
    void RowXMLValue(const Field<String>& x)
    {
        const size_t n = offsetof(Self, RowXMLValue);
        GetField<String>(n) = x;
    }
    
    const String& RowXMLValue_value() const
    {
        const size_t n = offsetof(Self, RowXMLValue);
        return GetField<String>(n).value;
    }
    
    void RowXMLValue_value(const String& x)
    {
        const size_t n = offsetof(Self, RowXMLValue);
        GetField<String>(n).Set(x);
    }
    
    bool RowXMLValue_exists() const
    {
        const size_t n = offsetof(Self, RowXMLValue);
        return GetField<String>(n).exists ? true : false;
    }
    
    void RowXMLValue_clear()
    {
        const size_t n = offsetof(Self, RowXMLValue);
        GetField<String>(n).Clear();
    }

    //
    // MySQL_StoredProcedureRow_AsXML_Class.IsTruncated
    //
    
    const Field<Boolean>& IsTruncated() const
    {
        const size_t n = offsetof(Self, IsTruncated);
        return GetField<Boolean>(n);
    }
    
    void IsTruncated(const Field<Boolean>& x)
    {
        const size_t n = offsetof(Self, IsTruncated);
        GetField<Boolean>(n) = x;
    }
    
    const Boolean& IsTruncated_value() const
    {
        const size_t n = offsetof(Self, IsTruncated);
        return GetField<Boolean>(n).value;
    }
    
    void IsTruncated_value(const Boolean& x)
    {
        const size_t n = offsetof(Self, IsTruncated);
        GetField<Boolean>(n).Set(x);
    }
    
    bool IsTruncated_exists() const
    {
        const size_t n = offsetof(Self, IsTruncated);
        return GetField<Boolean>(n).exists ? true : false;
    }
    
    void IsTruncated_clear()
    {
        const size_t n = offsetof(Self, IsTruncated);
        GetField<Boolean>(n).Clear();
    }
};

typedef Array<MySQL_StoredProcedureRow_AsXML_Class> MySQL_StoredProcedureRow_AsXML_ClassA;

MI_END_NAMESPACE

#endif /* __cplusplus */

#endif /* _MySQL_StoredProcedureRow_AsXML_h */
