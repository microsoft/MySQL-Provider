/* @migen@ */
/*
**==============================================================================
**
** WARNING: THIS FILE WAS AUTOMATICALLY GENERATED. PLEASE DO NOT EDIT.
**
**==============================================================================
*/
#include <ctype.h>
#include <MI.h>
#include "MySQL_Server.h"
#include "MySQL_ServerStatistics.h"
#include "MySQL_Server_Database.h"

/*
**==============================================================================
**
** Schema Declaration
**
**==============================================================================
*/

extern MI_SchemaDecl schemaDecl;

/*
**==============================================================================
**
** Qualifier declarations
**
**==============================================================================
*/

/*
**==============================================================================
**
** CIM_ManagedElement
**
**==============================================================================
*/

/* property CIM_ManagedElement.InstanceID */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_InstanceID_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ManagedElement_Caption_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_ManagedElement_Caption_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ManagedElement_Caption_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedElement_Caption_quals[] =
{
    &CIM_ManagedElement_Caption_MaxLen_qual,
};

/* property CIM_ManagedElement.Caption */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_Caption_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636E07, /* code */
    MI_T("Caption"), /* name */
    CIM_ManagedElement_Caption_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedElement_Caption_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, Caption), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedElement.Description */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_Description_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E0B, /* code */
    MI_T("Description"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, Description), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedElement.ElementName */
static MI_CONST MI_PropertyDecl CIM_ManagedElement_ElementName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650B, /* code */
    MI_T("ElementName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedElement, ElementName), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ManagedElement"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ManagedElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
};

static MI_CONST MI_Char* CIM_ManagedElement_Version_qual_value = MI_T("2.19.0");

static MI_CONST MI_Qualifier CIM_ManagedElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ManagedElement_Version_qual_value
};

static MI_CONST MI_Char* CIM_ManagedElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_ManagedElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ManagedElement_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedElement_quals[] =
{
    &CIM_ManagedElement_Version_qual,
    &CIM_ManagedElement_UMLPackagePath_qual,
};

/* class CIM_ManagedElement */
MI_CONST MI_ClassDecl CIM_ManagedElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637412, /* code */
    MI_T("CIM_ManagedElement"), /* name */
    CIM_ManagedElement_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedElement_quals), /* numQualifiers */
    CIM_ManagedElement_props, /* properties */
    MI_COUNT(CIM_ManagedElement_props), /* numProperties */
    sizeof(CIM_ManagedElement), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Collection
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Collection_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
};

static MI_CONST MI_Char* CIM_Collection_UMLPackagePath_qual_value = MI_T("CIM::Core::Collection");

static MI_CONST MI_Qualifier CIM_Collection_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Collection_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Collection_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_Collection_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Collection_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Collection_quals[] =
{
    &CIM_Collection_UMLPackagePath_qual,
    &CIM_Collection_Version_qual,
};

/* class CIM_Collection */
MI_CONST MI_ClassDecl CIM_Collection_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00636E0E, /* code */
    MI_T("CIM_Collection"), /* name */
    CIM_Collection_quals, /* qualifiers */
    MI_COUNT(CIM_Collection_quals), /* numQualifiers */
    CIM_Collection_props, /* properties */
    MI_COUNT(CIM_Collection_props), /* numProperties */
    sizeof(CIM_Collection), /* size */
    MI_T("CIM_ManagedElement"), /* superClass */
    &CIM_ManagedElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_InstalledProduct
**
**==============================================================================
*/

static MI_CONST MI_Uint32 CIM_InstalledProduct_ProductIdentifyingNumber_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_InstalledProduct_ProductIdentifyingNumber_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_InstalledProduct_ProductIdentifyingNumber_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_InstalledProduct_ProductIdentifyingNumber_Propagated_qual_value = MI_T("CIM_Product.IdentifyingNumber");

static MI_CONST MI_Qualifier CIM_InstalledProduct_ProductIdentifyingNumber_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_InstalledProduct_ProductIdentifyingNumber_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstalledProduct_ProductIdentifyingNumber_quals[] =
{
    &CIM_InstalledProduct_ProductIdentifyingNumber_MaxLen_qual,
    &CIM_InstalledProduct_ProductIdentifyingNumber_Propagated_qual,
};

/* property CIM_InstalledProduct.ProductIdentifyingNumber */
static MI_CONST MI_PropertyDecl CIM_InstalledProduct_ProductIdentifyingNumber_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00707218, /* code */
    MI_T("ProductIdentifyingNumber"), /* name */
    CIM_InstalledProduct_ProductIdentifyingNumber_quals, /* qualifiers */
    MI_COUNT(CIM_InstalledProduct_ProductIdentifyingNumber_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstalledProduct, ProductIdentifyingNumber), /* offset */
    MI_T("CIM_InstalledProduct"), /* origin */
    MI_T("CIM_InstalledProduct"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_InstalledProduct_ProductName_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_InstalledProduct_ProductName_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_InstalledProduct_ProductName_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_InstalledProduct_ProductName_Propagated_qual_value = MI_T("CIM_Product.Name");

static MI_CONST MI_Qualifier CIM_InstalledProduct_ProductName_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_InstalledProduct_ProductName_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstalledProduct_ProductName_quals[] =
{
    &CIM_InstalledProduct_ProductName_MaxLen_qual,
    &CIM_InstalledProduct_ProductName_Propagated_qual,
};

/* property CIM_InstalledProduct.ProductName */
static MI_CONST MI_PropertyDecl CIM_InstalledProduct_ProductName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0070650B, /* code */
    MI_T("ProductName"), /* name */
    CIM_InstalledProduct_ProductName_quals, /* qualifiers */
    MI_COUNT(CIM_InstalledProduct_ProductName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstalledProduct, ProductName), /* offset */
    MI_T("CIM_InstalledProduct"), /* origin */
    MI_T("CIM_InstalledProduct"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_InstalledProduct_ProductVendor_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_InstalledProduct_ProductVendor_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_InstalledProduct_ProductVendor_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_InstalledProduct_ProductVendor_Propagated_qual_value = MI_T("CIM_Product.Vendor");

static MI_CONST MI_Qualifier CIM_InstalledProduct_ProductVendor_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_InstalledProduct_ProductVendor_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstalledProduct_ProductVendor_quals[] =
{
    &CIM_InstalledProduct_ProductVendor_MaxLen_qual,
    &CIM_InstalledProduct_ProductVendor_Propagated_qual,
};

/* property CIM_InstalledProduct.ProductVendor */
static MI_CONST MI_PropertyDecl CIM_InstalledProduct_ProductVendor_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0070720D, /* code */
    MI_T("ProductVendor"), /* name */
    CIM_InstalledProduct_ProductVendor_quals, /* qualifiers */
    MI_COUNT(CIM_InstalledProduct_ProductVendor_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstalledProduct, ProductVendor), /* offset */
    MI_T("CIM_InstalledProduct"), /* origin */
    MI_T("CIM_InstalledProduct"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_InstalledProduct_ProductVersion_MaxLen_qual_value = 64U;

static MI_CONST MI_Qualifier CIM_InstalledProduct_ProductVersion_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_InstalledProduct_ProductVersion_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_InstalledProduct_ProductVersion_Propagated_qual_value = MI_T("CIM_Product.Version");

static MI_CONST MI_Qualifier CIM_InstalledProduct_ProductVersion_Propagated_qual =
{
    MI_T("Propagated"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_InstalledProduct_ProductVersion_Propagated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstalledProduct_ProductVersion_quals[] =
{
    &CIM_InstalledProduct_ProductVersion_MaxLen_qual,
    &CIM_InstalledProduct_ProductVersion_Propagated_qual,
};

/* property CIM_InstalledProduct.ProductVersion */
static MI_CONST MI_PropertyDecl CIM_InstalledProduct_ProductVersion_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00706E0E, /* code */
    MI_T("ProductVersion"), /* name */
    CIM_InstalledProduct_ProductVersion_quals, /* qualifiers */
    MI_COUNT(CIM_InstalledProduct_ProductVersion_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstalledProduct, ProductVersion), /* offset */
    MI_T("CIM_InstalledProduct"), /* origin */
    MI_T("CIM_InstalledProduct"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_InstalledProduct_SystemID_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_InstalledProduct_SystemID_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_InstalledProduct_SystemID_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstalledProduct_SystemID_quals[] =
{
    &CIM_InstalledProduct_SystemID_MaxLen_qual,
};

/* property CIM_InstalledProduct.SystemID */
static MI_CONST MI_PropertyDecl CIM_InstalledProduct_SystemID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x00736408, /* code */
    MI_T("SystemID"), /* name */
    CIM_InstalledProduct_SystemID_quals, /* qualifiers */
    MI_COUNT(CIM_InstalledProduct_SystemID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstalledProduct, SystemID), /* offset */
    MI_T("CIM_InstalledProduct"), /* origin */
    MI_T("CIM_InstalledProduct"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_InstalledProduct_CollectionID_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_InstalledProduct_CollectionID_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_InstalledProduct_CollectionID_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstalledProduct_CollectionID_quals[] =
{
    &CIM_InstalledProduct_CollectionID_MaxLen_qual,
};

/* property CIM_InstalledProduct.CollectionID */
static MI_CONST MI_PropertyDecl CIM_InstalledProduct_CollectionID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0063640C, /* code */
    MI_T("CollectionID"), /* name */
    CIM_InstalledProduct_CollectionID_quals, /* qualifiers */
    MI_COUNT(CIM_InstalledProduct_CollectionID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstalledProduct, CollectionID), /* offset */
    MI_T("CIM_InstalledProduct"), /* origin */
    MI_T("CIM_InstalledProduct"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_InstalledProduct_Name_MaxLen_qual_value = 256U;

static MI_CONST MI_Qualifier CIM_InstalledProduct_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_InstalledProduct_Name_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstalledProduct_Name_quals[] =
{
    &CIM_InstalledProduct_Name_MaxLen_qual,
};

/* property CIM_InstalledProduct.Name */
static MI_CONST MI_PropertyDecl CIM_InstalledProduct_Name_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_InstalledProduct_Name_quals, /* qualifiers */
    MI_COUNT(CIM_InstalledProduct_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_InstalledProduct, Name), /* offset */
    MI_T("CIM_InstalledProduct"), /* origin */
    MI_T("CIM_InstalledProduct"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_InstalledProduct_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_InstalledProduct_ProductIdentifyingNumber_prop,
    &CIM_InstalledProduct_ProductName_prop,
    &CIM_InstalledProduct_ProductVendor_prop,
    &CIM_InstalledProduct_ProductVersion_prop,
    &CIM_InstalledProduct_SystemID_prop,
    &CIM_InstalledProduct_CollectionID_prop,
    &CIM_InstalledProduct_Name_prop,
};

static MI_CONST MI_Char* CIM_InstalledProduct_UMLPackagePath_qual_value = MI_T("CIM::Application::InstalledProduct");

static MI_CONST MI_Qualifier CIM_InstalledProduct_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_InstalledProduct_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_InstalledProduct_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_InstalledProduct_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_InstalledProduct_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_InstalledProduct_quals[] =
{
    &CIM_InstalledProduct_UMLPackagePath_qual,
    &CIM_InstalledProduct_Version_qual,
};

/* class CIM_InstalledProduct */
MI_CONST MI_ClassDecl CIM_InstalledProduct_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00637414, /* code */
    MI_T("CIM_InstalledProduct"), /* name */
    CIM_InstalledProduct_quals, /* qualifiers */
    MI_COUNT(CIM_InstalledProduct_quals), /* numQualifiers */
    CIM_InstalledProduct_props, /* properties */
    MI_COUNT(CIM_InstalledProduct_props), /* numProperties */
    sizeof(CIM_InstalledProduct), /* size */
    MI_T("CIM_Collection"), /* superClass */
    &CIM_Collection_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySQL_Server
**
**==============================================================================
*/

/* property MySQL_Server.ConfigurationFile */
static MI_CONST MI_PropertyDecl MySQL_Server_ConfigurationFile_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636511, /* code */
    MI_T("ConfigurationFile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server, ConfigurationFile), /* offset */
    MI_T("MySQL_Server"), /* origin */
    MI_T("MySQL_Server"), /* propagator */
    NULL,
};

/* property MySQL_Server.ErrorLogFile */
static MI_CONST MI_PropertyDecl MySQL_Server_ErrorLogFile_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650C, /* code */
    MI_T("ErrorLogFile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server, ErrorLogFile), /* offset */
    MI_T("MySQL_Server"), /* origin */
    MI_T("MySQL_Server"), /* propagator */
    NULL,
};

/* property MySQL_Server.Hostname */
static MI_CONST MI_PropertyDecl MySQL_Server_Hostname_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00686508, /* code */
    MI_T("Hostname"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server, Hostname), /* offset */
    MI_T("MySQL_Server"), /* origin */
    MI_T("MySQL_Server"), /* propagator */
    NULL,
};

/* property MySQL_Server.BindAddress */
static MI_CONST MI_PropertyDecl MySQL_Server_BindAddress_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0062730B, /* code */
    MI_T("BindAddress"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server, BindAddress), /* offset */
    MI_T("MySQL_Server"), /* origin */
    MI_T("MySQL_Server"), /* propagator */
    NULL,
};

/* property MySQL_Server.Port */
static MI_CONST MI_PropertyDecl MySQL_Server_Port_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707404, /* code */
    MI_T("Port"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server, Port), /* offset */
    MI_T("MySQL_Server"), /* origin */
    MI_T("MySQL_Server"), /* propagator */
    NULL,
};

/* property MySQL_Server.SocketFile */
static MI_CONST MI_PropertyDecl MySQL_Server_SocketFile_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650A, /* code */
    MI_T("SocketFile"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server, SocketFile), /* offset */
    MI_T("MySQL_Server"), /* origin */
    MI_T("MySQL_Server"), /* propagator */
    NULL,
};

/* property MySQL_Server.DataDirectory */
static MI_CONST MI_PropertyDecl MySQL_Server_DataDirectory_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064790D, /* code */
    MI_T("DataDirectory"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server, DataDirectory), /* offset */
    MI_T("MySQL_Server"), /* origin */
    MI_T("MySQL_Server"), /* propagator */
    NULL,
};

/* property MySQL_Server.OperatingStatus */
static MI_CONST MI_PropertyDecl MySQL_Server_OperatingStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F730F, /* code */
    MI_T("OperatingStatus"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server, OperatingStatus), /* offset */
    MI_T("MySQL_Server"), /* origin */
    MI_T("MySQL_Server"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MySQL_Server_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_InstalledProduct_ProductIdentifyingNumber_prop,
    &CIM_InstalledProduct_ProductName_prop,
    &CIM_InstalledProduct_ProductVendor_prop,
    &CIM_InstalledProduct_ProductVersion_prop,
    &CIM_InstalledProduct_SystemID_prop,
    &CIM_InstalledProduct_CollectionID_prop,
    &CIM_InstalledProduct_Name_prop,
    &MySQL_Server_ConfigurationFile_prop,
    &MySQL_Server_ErrorLogFile_prop,
    &MySQL_Server_Hostname_prop,
    &MySQL_Server_BindAddress_prop,
    &MySQL_Server_Port_prop,
    &MySQL_Server_SocketFile_prop,
    &MySQL_Server_DataDirectory_prop,
    &MySQL_Server_OperatingStatus_prop,
};

/* parameter MySQL_Server.UpdateCredentials(): Port */
static MI_CONST MI_ParameterDecl MySQL_Server_UpdateCredentials_Port_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00707404, /* code */
    MI_T("Port"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_UpdateCredentials, Port), /* offset */
};

/* parameter MySQL_Server.UpdateCredentials(): BindAddress */
static MI_CONST MI_ParameterDecl MySQL_Server_UpdateCredentials_BindAddress_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0062730B, /* code */
    MI_T("BindAddress"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_UpdateCredentials, BindAddress), /* offset */
};

/* parameter MySQL_Server.UpdateCredentials(): Username */
static MI_CONST MI_ParameterDecl MySQL_Server_UpdateCredentials_Username_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00756508, /* code */
    MI_T("Username"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_UpdateCredentials, Username), /* offset */
};

/* parameter MySQL_Server.UpdateCredentials(): Password */
static MI_CONST MI_ParameterDecl MySQL_Server_UpdateCredentials_Password_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00706408, /* code */
    MI_T("Password"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_UpdateCredentials, Password), /* offset */
};

/* parameter MySQL_Server.UpdateCredentials(): B64Encoded */
static MI_CONST MI_ParameterDecl MySQL_Server_UpdateCredentials_B64Encoded_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0062640A, /* code */
    MI_T("B64Encoded"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_UpdateCredentials, B64Encoded), /* offset */
};

/* parameter MySQL_Server.UpdateCredentials(): MIReturn */
static MI_CONST MI_ParameterDecl MySQL_Server_UpdateCredentials_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_UpdateCredentials, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySQL_Server_UpdateCredentials_params[] =
{
    &MySQL_Server_UpdateCredentials_MIReturn_param,
    &MySQL_Server_UpdateCredentials_Port_param,
    &MySQL_Server_UpdateCredentials_BindAddress_param,
    &MySQL_Server_UpdateCredentials_Username_param,
    &MySQL_Server_UpdateCredentials_Password_param,
    &MySQL_Server_UpdateCredentials_B64Encoded_param,
};

/* method MySQL_Server.UpdateCredentials() */
MI_CONST MI_MethodDecl MySQL_Server_UpdateCredentials_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00757311, /* code */
    MI_T("UpdateCredentials"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySQL_Server_UpdateCredentials_params, /* parameters */
    MI_COUNT(MySQL_Server_UpdateCredentials_params), /* numParameters */
    sizeof(MySQL_Server_UpdateCredentials), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MySQL_Server"), /* origin */
    MI_T("MySQL_Server"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySQL_Server_Invoke_UpdateCredentials, /* method */
};

/* parameter MySQL_Server.DeleteCredentials(): Port */
static MI_CONST MI_ParameterDecl MySQL_Server_DeleteCredentials_Port_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00707404, /* code */
    MI_T("Port"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_DeleteCredentials, Port), /* offset */
};

/* parameter MySQL_Server.DeleteCredentials(): MIReturn */
static MI_CONST MI_ParameterDecl MySQL_Server_DeleteCredentials_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_DeleteCredentials, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySQL_Server_DeleteCredentials_params[] =
{
    &MySQL_Server_DeleteCredentials_MIReturn_param,
    &MySQL_Server_DeleteCredentials_Port_param,
};

/* method MySQL_Server.DeleteCredentials() */
MI_CONST MI_MethodDecl MySQL_Server_DeleteCredentials_rtti =
{
    MI_FLAG_METHOD|MI_FLAG_STATIC, /* flags */
    0x00647311, /* code */
    MI_T("DeleteCredentials"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySQL_Server_DeleteCredentials_params, /* parameters */
    MI_COUNT(MySQL_Server_DeleteCredentials_params), /* numParameters */
    sizeof(MySQL_Server_DeleteCredentials), /* size */
    MI_BOOLEAN, /* returnType */
    MI_T("MySQL_Server"), /* origin */
    MI_T("MySQL_Server"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySQL_Server_Invoke_DeleteCredentials, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MySQL_Server_meths[] =
{
    &MySQL_Server_UpdateCredentials_rtti,
    &MySQL_Server_DeleteCredentials_rtti,
};

static MI_CONST MI_ProviderFT MySQL_Server_funcs =
{
  (MI_ProviderFT_Load)MySQL_Server_Load,
  (MI_ProviderFT_Unload)MySQL_Server_Unload,
  (MI_ProviderFT_GetInstance)MySQL_Server_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MySQL_Server_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MySQL_Server_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MySQL_Server_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MySQL_Server_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* MySQL_Server_UMLPackagePath_qual_value = MI_T("CIM::Application::InstalledProduct");

static MI_CONST MI_Qualifier MySQL_Server_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &MySQL_Server_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* MySQL_Server_Version_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MySQL_Server_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &MySQL_Server_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySQL_Server_quals[] =
{
    &MySQL_Server_UMLPackagePath_qual,
    &MySQL_Server_Version_qual,
};

/* class MySQL_Server */
MI_CONST MI_ClassDecl MySQL_Server_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D720C, /* code */
    MI_T("MySQL_Server"), /* name */
    MySQL_Server_quals, /* qualifiers */
    MI_COUNT(MySQL_Server_quals), /* numQualifiers */
    MySQL_Server_props, /* properties */
    MI_COUNT(MySQL_Server_props), /* numProperties */
    sizeof(MySQL_Server), /* size */
    MI_T("CIM_InstalledProduct"), /* superClass */
    &CIM_InstalledProduct_rtti, /* superClassDecl */
    MySQL_Server_meths, /* methods */
    MI_COUNT(MySQL_Server_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MySQL_Server_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_StatisticalData
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_StatisticalData_InstanceID_Override_qual_value = MI_T("InstanceID");

static MI_CONST MI_Qualifier CIM_StatisticalData_InstanceID_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_StatisticalData_InstanceID_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_StatisticalData_InstanceID_quals[] =
{
    &CIM_StatisticalData_InstanceID_Override_qual,
};

/* property CIM_StatisticalData.InstanceID */
static MI_CONST MI_PropertyDecl CIM_StatisticalData_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    CIM_StatisticalData_InstanceID_quals, /* qualifiers */
    MI_COUNT(CIM_StatisticalData_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_StatisticalData, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_StatisticalData"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_StatisticalData_ElementName_Override_qual_value = MI_T("ElementName");

static MI_CONST MI_Qualifier CIM_StatisticalData_ElementName_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_StatisticalData_ElementName_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_StatisticalData_ElementName_quals[] =
{
    &CIM_StatisticalData_ElementName_Override_qual,
};

/* property CIM_StatisticalData.ElementName */
static MI_CONST MI_PropertyDecl CIM_StatisticalData_ElementName_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x0065650B, /* code */
    MI_T("ElementName"), /* name */
    CIM_StatisticalData_ElementName_quals, /* qualifiers */
    MI_COUNT(CIM_StatisticalData_ElementName_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_StatisticalData, ElementName), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_StatisticalData"), /* propagator */
    NULL,
};

/* property CIM_StatisticalData.StartStatisticTime */
static MI_CONST MI_PropertyDecl CIM_StatisticalData_StartStatisticTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736512, /* code */
    MI_T("StartStatisticTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_StatisticalData, StartStatisticTime), /* offset */
    MI_T("CIM_StatisticalData"), /* origin */
    MI_T("CIM_StatisticalData"), /* propagator */
    NULL,
};

/* property CIM_StatisticalData.StatisticTime */
static MI_CONST MI_PropertyDecl CIM_StatisticalData_StatisticTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073650D, /* code */
    MI_T("StatisticTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_StatisticalData, StatisticTime), /* offset */
    MI_T("CIM_StatisticalData"), /* origin */
    MI_T("CIM_StatisticalData"), /* propagator */
    NULL,
};

static MI_CONST MI_Datetime CIM_StatisticalData_SampleInterval_value = {0,{{0,0,0,0,0}}};

/* property CIM_StatisticalData.SampleInterval */
static MI_CONST MI_PropertyDecl CIM_StatisticalData_SampleInterval_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736C0E, /* code */
    MI_T("SampleInterval"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_StatisticalData, SampleInterval), /* offset */
    MI_T("CIM_StatisticalData"), /* origin */
    MI_T("CIM_StatisticalData"), /* propagator */
    &CIM_StatisticalData_SampleInterval_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_StatisticalData_props[] =
{
    &CIM_StatisticalData_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_StatisticalData_ElementName_prop,
    &CIM_StatisticalData_StartStatisticTime_prop,
    &CIM_StatisticalData_StatisticTime_prop,
    &CIM_StatisticalData_SampleInterval_prop,
};

/* parameter CIM_StatisticalData.ResetSelectedStats(): SelectedStatistics */
static MI_CONST MI_ParameterDecl CIM_StatisticalData_ResetSelectedStats_SelectedStatistics_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00737312, /* code */
    MI_T("SelectedStatistics"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_StatisticalData_ResetSelectedStats, SelectedStatistics), /* offset */
};

/* parameter CIM_StatisticalData.ResetSelectedStats(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_StatisticalData_ResetSelectedStats_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_StatisticalData_ResetSelectedStats, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_StatisticalData_ResetSelectedStats_params[] =
{
    &CIM_StatisticalData_ResetSelectedStats_MIReturn_param,
    &CIM_StatisticalData_ResetSelectedStats_SelectedStatistics_param,
};

/* method CIM_StatisticalData.ResetSelectedStats() */
MI_CONST MI_MethodDecl CIM_StatisticalData_ResetSelectedStats_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727312, /* code */
    MI_T("ResetSelectedStats"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_StatisticalData_ResetSelectedStats_params, /* parameters */
    MI_COUNT(CIM_StatisticalData_ResetSelectedStats_params), /* numParameters */
    sizeof(CIM_StatisticalData_ResetSelectedStats), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_StatisticalData"), /* origin */
    MI_T("CIM_StatisticalData"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_StatisticalData_meths[] =
{
    &CIM_StatisticalData_ResetSelectedStats_rtti,
};

static MI_CONST MI_Char* CIM_StatisticalData_UMLPackagePath_qual_value = MI_T("CIM::Core::Statistics");

static MI_CONST MI_Qualifier CIM_StatisticalData_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_StatisticalData_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_StatisticalData_Version_qual_value = MI_T("2.19.0");

static MI_CONST MI_Qualifier CIM_StatisticalData_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_StatisticalData_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_StatisticalData_quals[] =
{
    &CIM_StatisticalData_UMLPackagePath_qual,
    &CIM_StatisticalData_Version_qual,
};

/* class CIM_StatisticalData */
MI_CONST MI_ClassDecl CIM_StatisticalData_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00636113, /* code */
    MI_T("CIM_StatisticalData"), /* name */
    CIM_StatisticalData_quals, /* qualifiers */
    MI_COUNT(CIM_StatisticalData_quals), /* numQualifiers */
    CIM_StatisticalData_props, /* properties */
    MI_COUNT(CIM_StatisticalData_props), /* numProperties */
    sizeof(CIM_StatisticalData), /* size */
    MI_T("CIM_ManagedElement"), /* superClass */
    &CIM_ManagedElement_rtti, /* superClassDecl */
    CIM_StatisticalData_meths, /* methods */
    MI_COUNT(CIM_StatisticalData_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySQL_ServerStatistics
**
**==============================================================================
*/

/* property MySQL_ServerStatistics.NumConnections */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_NumConnections_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E730E, /* code */
    MI_T("NumConnections"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, NumConnections), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.MaxConnections */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_MaxConnections_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D730E, /* code */
    MI_T("MaxConnections"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, MaxConnections), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.FailedConnections */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_FailedConnections_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00667311, /* code */
    MI_T("FailedConnections"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, FailedConnections), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.Uptime */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_Uptime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756506, /* code */
    MI_T("Uptime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, Uptime), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.ServerDiskUseInBytes */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_ServerDiskUseInBytes_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737314, /* code */
    MI_T("ServerDiskUseInBytes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, ServerDiskUseInBytes), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.SlowQueryPct */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_SlowQueryPct_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073740C, /* code */
    MI_T("SlowQueryPct"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, SlowQueryPct), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.KeyCacheHitPct */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_KeyCacheHitPct_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006B740E, /* code */
    MI_T("KeyCacheHitPct"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, KeyCacheHitPct), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.KeyCacheWritePct */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_KeyCacheWritePct_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006B7410, /* code */
    MI_T("KeyCacheWritePct"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, KeyCacheWritePct), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.QCacheHitPct */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_QCacheHitPct_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0071740C, /* code */
    MI_T("QCacheHitPct"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, QCacheHitPct), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.QCachePrunesPct */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_QCachePrunesPct_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0071740F, /* code */
    MI_T("QCachePrunesPct"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, QCachePrunesPct), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.TCacheHitPct */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_TCacheHitPct_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074740C, /* code */
    MI_T("TCacheHitPct"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, TCacheHitPct), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.TableLockContentionPct */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_TableLockContentionPct_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00747416, /* code */
    MI_T("TableLockContentionPct"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, TableLockContentionPct), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.IDB_BP_HitPct */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_IDB_BP_HitPct_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069740D, /* code */
    MI_T("IDB_BP_HitPct"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, IDB_BP_HitPct), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.IDB_BP_UsePct */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_IDB_BP_UsePct_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069740D, /* code */
    MI_T("IDB_BP_UsePct"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, IDB_BP_UsePct), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

/* property MySQL_ServerStatistics.FullTableScanPct */
static MI_CONST MI_PropertyDecl MySQL_ServerStatistics_FullTableScanPct_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00667410, /* code */
    MI_T("FullTableScanPct"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics, FullTableScanPct), /* offset */
    MI_T("MySQL_ServerStatistics"), /* origin */
    MI_T("MySQL_ServerStatistics"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MySQL_ServerStatistics_props[] =
{
    &CIM_StatisticalData_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_StatisticalData_ElementName_prop,
    &CIM_StatisticalData_StartStatisticTime_prop,
    &CIM_StatisticalData_StatisticTime_prop,
    &CIM_StatisticalData_SampleInterval_prop,
    &MySQL_ServerStatistics_NumConnections_prop,
    &MySQL_ServerStatistics_MaxConnections_prop,
    &MySQL_ServerStatistics_FailedConnections_prop,
    &MySQL_ServerStatistics_Uptime_prop,
    &MySQL_ServerStatistics_ServerDiskUseInBytes_prop,
    &MySQL_ServerStatistics_SlowQueryPct_prop,
    &MySQL_ServerStatistics_KeyCacheHitPct_prop,
    &MySQL_ServerStatistics_KeyCacheWritePct_prop,
    &MySQL_ServerStatistics_QCacheHitPct_prop,
    &MySQL_ServerStatistics_QCachePrunesPct_prop,
    &MySQL_ServerStatistics_TCacheHitPct_prop,
    &MySQL_ServerStatistics_TableLockContentionPct_prop,
    &MySQL_ServerStatistics_IDB_BP_HitPct_prop,
    &MySQL_ServerStatistics_IDB_BP_UsePct_prop,
    &MySQL_ServerStatistics_FullTableScanPct_prop,
};

/* parameter MySQL_ServerStatistics.ResetSelectedStats(): SelectedStatistics */
static MI_CONST MI_ParameterDecl MySQL_ServerStatistics_ResetSelectedStats_SelectedStatistics_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00737312, /* code */
    MI_T("SelectedStatistics"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics_ResetSelectedStats, SelectedStatistics), /* offset */
};

/* parameter MySQL_ServerStatistics.ResetSelectedStats(): MIReturn */
static MI_CONST MI_ParameterDecl MySQL_ServerStatistics_ResetSelectedStats_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_ServerStatistics_ResetSelectedStats, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySQL_ServerStatistics_ResetSelectedStats_params[] =
{
    &MySQL_ServerStatistics_ResetSelectedStats_MIReturn_param,
    &MySQL_ServerStatistics_ResetSelectedStats_SelectedStatistics_param,
};

/* method MySQL_ServerStatistics.ResetSelectedStats() */
MI_CONST MI_MethodDecl MySQL_ServerStatistics_ResetSelectedStats_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00727312, /* code */
    MI_T("ResetSelectedStats"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySQL_ServerStatistics_ResetSelectedStats_params, /* parameters */
    MI_COUNT(MySQL_ServerStatistics_ResetSelectedStats_params), /* numParameters */
    sizeof(MySQL_ServerStatistics_ResetSelectedStats), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_StatisticalData"), /* origin */
    MI_T("CIM_StatisticalData"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySQL_ServerStatistics_Invoke_ResetSelectedStats, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MySQL_ServerStatistics_meths[] =
{
    &MySQL_ServerStatistics_ResetSelectedStats_rtti,
};

static MI_CONST MI_ProviderFT MySQL_ServerStatistics_funcs =
{
  (MI_ProviderFT_Load)MySQL_ServerStatistics_Load,
  (MI_ProviderFT_Unload)MySQL_ServerStatistics_Unload,
  (MI_ProviderFT_GetInstance)MySQL_ServerStatistics_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MySQL_ServerStatistics_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MySQL_ServerStatistics_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MySQL_ServerStatistics_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MySQL_ServerStatistics_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* MySQL_ServerStatistics_UMLPackagePath_qual_value = MI_T("CIM::Core::Statistics");

static MI_CONST MI_Qualifier MySQL_ServerStatistics_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &MySQL_ServerStatistics_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* MySQL_ServerStatistics_Version_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MySQL_ServerStatistics_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &MySQL_ServerStatistics_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySQL_ServerStatistics_quals[] =
{
    &MySQL_ServerStatistics_UMLPackagePath_qual,
    &MySQL_ServerStatistics_Version_qual,
};

/* class MySQL_ServerStatistics */
MI_CONST MI_ClassDecl MySQL_ServerStatistics_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D7316, /* code */
    MI_T("MySQL_ServerStatistics"), /* name */
    MySQL_ServerStatistics_quals, /* qualifiers */
    MI_COUNT(MySQL_ServerStatistics_quals), /* numQualifiers */
    MySQL_ServerStatistics_props, /* properties */
    MI_COUNT(MySQL_ServerStatistics_props), /* numProperties */
    sizeof(MySQL_ServerStatistics), /* size */
    MI_T("CIM_StatisticalData"), /* superClass */
    &CIM_StatisticalData_rtti, /* superClassDecl */
    MySQL_ServerStatistics_meths, /* methods */
    MI_COUNT(MySQL_ServerStatistics_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MySQL_ServerStatistics_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_ManagedSystemElement
**
**==============================================================================
*/

/* property CIM_ManagedSystemElement.InstallDate */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_InstallDate_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0069650B, /* code */
    MI_T("InstallDate"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, InstallDate), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ManagedSystemElement_Name_MaxLen_qual_value = 1024U;

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ManagedSystemElement_Name_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_Name_quals[] =
{
    &CIM_ManagedSystemElement_Name_MaxLen_qual,
};

/* property CIM_ManagedSystemElement.Name */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_Name_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_ManagedSystemElement_Name_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, Name), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_OperationalStatus_quals[] =
{
    &CIM_ManagedSystemElement_OperationalStatus_ArrayType_qual,
};

/* property CIM_ManagedSystemElement.OperationalStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_OperationalStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7311, /* code */
    MI_T("OperationalStatus"), /* name */
    CIM_ManagedSystemElement_OperationalStatus_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_OperationalStatus_quals), /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, OperationalStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual_value = MI_T("Indexed");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual =
{
    MI_T("ArrayType"),
    MI_STRING,
    MI_FLAG_DISABLEOVERRIDE|MI_FLAG_TOSUBCLASS,
    &CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_StatusDescriptions_quals[] =
{
    &CIM_ManagedSystemElement_StatusDescriptions_ArrayType_qual,
};

/* property CIM_ManagedSystemElement.StatusDescriptions */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_StatusDescriptions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737312, /* code */
    MI_T("StatusDescriptions"), /* name */
    CIM_ManagedSystemElement_StatusDescriptions_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_StatusDescriptions_quals), /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, StatusDescriptions), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_Status_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ManagedSystemElement.OperationalStatus"),
};

static MI_CONST MI_ConstStringA CIM_ManagedSystemElement_Status_Deprecated_qual_value =
{
    CIM_ManagedSystemElement_Status_Deprecated_qual_data_value,
    MI_COUNT(CIM_ManagedSystemElement_Status_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Status_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ManagedSystemElement_Status_Deprecated_qual_value
};

static MI_CONST MI_Uint32 CIM_ManagedSystemElement_Status_MaxLen_qual_value = 10U;

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Status_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ManagedSystemElement_Status_MaxLen_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_Status_quals[] =
{
    &CIM_ManagedSystemElement_Status_Deprecated_qual,
    &CIM_ManagedSystemElement_Status_MaxLen_qual,
};

/* property CIM_ManagedSystemElement.Status */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_Status_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737306, /* code */
    MI_T("Status"), /* name */
    CIM_ManagedSystemElement_Status_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_Status_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, Status), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedSystemElement.HealthState */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_HealthState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0068650B, /* code */
    MI_T("HealthState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, HealthState), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedSystemElement.CommunicationStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_CommunicationStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00637313, /* code */
    MI_T("CommunicationStatus"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, CommunicationStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedSystemElement.DetailedStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_DetailedStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064730E, /* code */
    MI_T("DetailedStatus"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, DetailedStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedSystemElement.OperatingStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_OperatingStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F730F, /* code */
    MI_T("OperatingStatus"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, OperatingStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

/* property CIM_ManagedSystemElement.PrimaryStatus */
static MI_CONST MI_PropertyDecl CIM_ManagedSystemElement_PrimaryStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070730D, /* code */
    MI_T("PrimaryStatus"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ManagedSystemElement, PrimaryStatus), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ManagedSystemElement"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ManagedSystemElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ManagedSystemElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_ManagedSystemElement_Version_qual_value = MI_T("2.28.0");

static MI_CONST MI_Qualifier CIM_ManagedSystemElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ManagedSystemElement_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ManagedSystemElement_quals[] =
{
    &CIM_ManagedSystemElement_UMLPackagePath_qual,
    &CIM_ManagedSystemElement_Version_qual,
};

/* class CIM_ManagedSystemElement */
MI_CONST MI_ClassDecl CIM_ManagedSystemElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637418, /* code */
    MI_T("CIM_ManagedSystemElement"), /* name */
    CIM_ManagedSystemElement_quals, /* qualifiers */
    MI_COUNT(CIM_ManagedSystemElement_quals), /* numQualifiers */
    CIM_ManagedSystemElement_props, /* properties */
    MI_COUNT(CIM_ManagedSystemElement_props), /* numProperties */
    sizeof(CIM_ManagedSystemElement), /* size */
    MI_T("CIM_ManagedElement"), /* superClass */
    &CIM_ManagedElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_LogicalElement
**
**==============================================================================
*/

static MI_PropertyDecl MI_CONST* MI_CONST CIM_LogicalElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
};

static MI_CONST MI_Char* CIM_LogicalElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_LogicalElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_LogicalElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_LogicalElement_Version_qual_value = MI_T("2.6.0");

static MI_CONST MI_Qualifier CIM_LogicalElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_LogicalElement_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_LogicalElement_quals[] =
{
    &CIM_LogicalElement_UMLPackagePath_qual,
    &CIM_LogicalElement_Version_qual,
};

/* class CIM_LogicalElement */
MI_CONST MI_ClassDecl CIM_LogicalElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637412, /* code */
    MI_T("CIM_LogicalElement"), /* name */
    CIM_LogicalElement_quals, /* qualifiers */
    MI_COUNT(CIM_LogicalElement_quals), /* numQualifiers */
    CIM_LogicalElement_props, /* properties */
    MI_COUNT(CIM_LogicalElement_props), /* numProperties */
    sizeof(CIM_LogicalElement), /* size */
    MI_T("CIM_ManagedSystemElement"), /* superClass */
    &CIM_ManagedSystemElement_rtti, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Job
**
**==============================================================================
*/

/* property CIM_Job.JobStatus */
static MI_CONST MI_PropertyDecl CIM_Job_JobStatus_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006A7309, /* code */
    MI_T("JobStatus"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, JobStatus), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.TimeSubmitted */
static MI_CONST MI_PropertyDecl CIM_Job_TimeSubmitted_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0074640D, /* code */
    MI_T("TimeSubmitted"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, TimeSubmitted), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_ScheduledStartTime_Deprecated_qual_data_value[] =
{
    MI_T("CIM_Job.RunMonth"),
    MI_T("CIM_Job.RunDay"),
    MI_T("CIM_Job.RunDayOfWeek"),
    MI_T("CIM_Job.RunStartInterval"),
};

static MI_CONST MI_ConstStringA CIM_Job_ScheduledStartTime_Deprecated_qual_value =
{
    CIM_Job_ScheduledStartTime_Deprecated_qual_data_value,
    MI_COUNT(CIM_Job_ScheduledStartTime_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_ScheduledStartTime_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Job_ScheduledStartTime_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_ScheduledStartTime_quals[] =
{
    &CIM_Job_ScheduledStartTime_Deprecated_qual,
};

/* property CIM_Job.ScheduledStartTime */
static MI_CONST MI_PropertyDecl CIM_Job_ScheduledStartTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736512, /* code */
    MI_T("ScheduledStartTime"), /* name */
    CIM_Job_ScheduledStartTime_quals, /* qualifiers */
    MI_COUNT(CIM_Job_ScheduledStartTime_quals), /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ScheduledStartTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.StartTime */
static MI_CONST MI_PropertyDecl CIM_Job_StartTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00736509, /* code */
    MI_T("StartTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, StartTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.ElapsedTime */
static MI_CONST MI_PropertyDecl CIM_Job_ElapsedTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650B, /* code */
    MI_T("ElapsedTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ElapsedTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_Job_JobRunTimes_value = 1U;

/* property CIM_Job.JobRunTimes */
static MI_CONST MI_PropertyDecl CIM_Job_JobRunTimes_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006A730B, /* code */
    MI_T("JobRunTimes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, JobRunTimes), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    &CIM_Job_JobRunTimes_value,
};

/* property CIM_Job.RunMonth */
static MI_CONST MI_PropertyDecl CIM_Job_RunMonth_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726808, /* code */
    MI_T("RunMonth"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunMonth), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Sint64 CIM_Job_RunDay_MinValue_qual_value = -MI_LL(31);

static MI_CONST MI_Qualifier CIM_Job_RunDay_MinValue_qual =
{
    MI_T("MinValue"),
    MI_SINT64,
    0,
    &CIM_Job_RunDay_MinValue_qual_value
};

static MI_CONST MI_Sint64 CIM_Job_RunDay_MaxValue_qual_value = MI_LL(31);

static MI_CONST MI_Qualifier CIM_Job_RunDay_MaxValue_qual =
{
    MI_T("MaxValue"),
    MI_SINT64,
    0,
    &CIM_Job_RunDay_MaxValue_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_RunDay_quals[] =
{
    &CIM_Job_RunDay_MinValue_qual,
    &CIM_Job_RunDay_MaxValue_qual,
};

/* property CIM_Job.RunDay */
static MI_CONST MI_PropertyDecl CIM_Job_RunDay_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727906, /* code */
    MI_T("RunDay"), /* name */
    CIM_Job_RunDay_quals, /* qualifiers */
    MI_COUNT(CIM_Job_RunDay_quals), /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunDay), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.RunDayOfWeek */
static MI_CONST MI_PropertyDecl CIM_Job_RunDayOfWeek_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726B0C, /* code */
    MI_T("RunDayOfWeek"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_SINT8, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunDayOfWeek), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.RunStartInterval */
static MI_CONST MI_PropertyDecl CIM_Job_RunStartInterval_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726C10, /* code */
    MI_T("RunStartInterval"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RunStartInterval), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.LocalOrUtcTime */
static MI_CONST MI_PropertyDecl CIM_Job_LocalOrUtcTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C650E, /* code */
    MI_T("LocalOrUtcTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, LocalOrUtcTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.UntilTime */
static MI_CONST MI_PropertyDecl CIM_Job_UntilTime_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00756509, /* code */
    MI_T("UntilTime"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, UntilTime), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.Notify */
static MI_CONST MI_PropertyDecl CIM_Job_Notify_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E7906, /* code */
    MI_T("Notify"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, Notify), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.Owner */
static MI_CONST MI_PropertyDecl CIM_Job_Owner_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7205, /* code */
    MI_T("Owner"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, Owner), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.Priority */
static MI_CONST MI_PropertyDecl CIM_Job_Priority_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707908, /* code */
    MI_T("Priority"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, Priority), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_CONST MI_Char* CIM_Job_PercentComplete_Units_qual_value = MI_T("Percent");

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_Units_qual =
{
    MI_T("Units"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TOSUBCLASS|MI_FLAG_TRANSLATABLE,
    &CIM_Job_PercentComplete_Units_qual_value
};

static MI_CONST MI_Sint64 CIM_Job_PercentComplete_MinValue_qual_value = MI_LL(0);

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_MinValue_qual =
{
    MI_T("MinValue"),
    MI_SINT64,
    0,
    &CIM_Job_PercentComplete_MinValue_qual_value
};

static MI_CONST MI_Sint64 CIM_Job_PercentComplete_MaxValue_qual_value = MI_LL(101);

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_MaxValue_qual =
{
    MI_T("MaxValue"),
    MI_SINT64,
    0,
    &CIM_Job_PercentComplete_MaxValue_qual_value
};

static MI_CONST MI_Char* CIM_Job_PercentComplete_PUnit_qual_value = MI_T("percent");

static MI_CONST MI_Qualifier CIM_Job_PercentComplete_PUnit_qual =
{
    MI_T("PUnit"),
    MI_STRING,
    0,
    &CIM_Job_PercentComplete_PUnit_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_PercentComplete_quals[] =
{
    &CIM_Job_PercentComplete_Units_qual,
    &CIM_Job_PercentComplete_MinValue_qual,
    &CIM_Job_PercentComplete_MaxValue_qual,
    &CIM_Job_PercentComplete_PUnit_qual,
};

/* property CIM_Job.PercentComplete */
static MI_CONST MI_PropertyDecl CIM_Job_PercentComplete_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070650F, /* code */
    MI_T("PercentComplete"), /* name */
    CIM_Job_PercentComplete_quals, /* qualifiers */
    MI_COUNT(CIM_Job_PercentComplete_quals), /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, PercentComplete), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.DeleteOnCompletion */
static MI_CONST MI_PropertyDecl CIM_Job_DeleteOnCompletion_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E12, /* code */
    MI_T("DeleteOnCompletion"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, DeleteOnCompletion), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.ErrorCode */
static MI_CONST MI_PropertyDecl CIM_Job_ErrorCode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656509, /* code */
    MI_T("ErrorCode"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ErrorCode), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.ErrorDescription */
static MI_CONST MI_PropertyDecl CIM_Job_ErrorDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656E10, /* code */
    MI_T("ErrorDescription"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, ErrorDescription), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.RecoveryAction */
static MI_CONST MI_PropertyDecl CIM_Job_RecoveryAction_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00726E0E, /* code */
    MI_T("RecoveryAction"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, RecoveryAction), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

/* property CIM_Job.OtherRecoveryAction */
static MI_CONST MI_PropertyDecl CIM_Job_OtherRecoveryAction_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6E13, /* code */
    MI_T("OtherRecoveryAction"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job, OtherRecoveryAction), /* offset */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Job_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_Job_JobStatus_prop,
    &CIM_Job_TimeSubmitted_prop,
    &CIM_Job_ScheduledStartTime_prop,
    &CIM_Job_StartTime_prop,
    &CIM_Job_ElapsedTime_prop,
    &CIM_Job_JobRunTimes_prop,
    &CIM_Job_RunMonth_prop,
    &CIM_Job_RunDay_prop,
    &CIM_Job_RunDayOfWeek_prop,
    &CIM_Job_RunStartInterval_prop,
    &CIM_Job_LocalOrUtcTime_prop,
    &CIM_Job_UntilTime_prop,
    &CIM_Job_Notify_prop,
    &CIM_Job_Owner_prop,
    &CIM_Job_Priority_prop,
    &CIM_Job_PercentComplete_prop,
    &CIM_Job_DeleteOnCompletion_prop,
    &CIM_Job_ErrorCode_prop,
    &CIM_Job_ErrorDescription_prop,
    &CIM_Job_RecoveryAction_prop,
    &CIM_Job_OtherRecoveryAction_prop,
};

static MI_CONST MI_Char* CIM_Job_KillJob_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.RequestStateChange()"),
};

static MI_CONST MI_ConstStringA CIM_Job_KillJob_Deprecated_qual_value =
{
    CIM_Job_KillJob_Deprecated_qual_data_value,
    MI_COUNT(CIM_Job_KillJob_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_KillJob_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Job_KillJob_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_KillJob_quals[] =
{
    &CIM_Job_KillJob_Deprecated_qual,
};

/* parameter CIM_Job.KillJob(): DeleteOnKill */
static MI_CONST MI_ParameterDecl CIM_Job_KillJob_DeleteOnKill_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x00646C0C, /* code */
    MI_T("DeleteOnKill"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_BOOLEAN, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job_KillJob, DeleteOnKill), /* offset */
};

static MI_CONST MI_Char* CIM_Job_KillJob_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.RequestStateChange()"),
};

static MI_CONST MI_ConstStringA CIM_Job_KillJob_MIReturn_Deprecated_qual_value =
{
    CIM_Job_KillJob_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_Job_KillJob_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_Job_KillJob_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_Job_KillJob_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_KillJob_MIReturn_quals[] =
{
    &CIM_Job_KillJob_MIReturn_Deprecated_qual,
};

/* parameter CIM_Job.KillJob(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_Job_KillJob_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_Job_KillJob_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_Job_KillJob_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Job_KillJob, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_Job_KillJob_params[] =
{
    &CIM_Job_KillJob_MIReturn_param,
    &CIM_Job_KillJob_DeleteOnKill_param,
};

/* method CIM_Job.KillJob() */
MI_CONST MI_MethodDecl CIM_Job_KillJob_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x006B6207, /* code */
    MI_T("KillJob"), /* name */
    CIM_Job_KillJob_quals, /* qualifiers */
    MI_COUNT(CIM_Job_KillJob_quals), /* numQualifiers */
    CIM_Job_KillJob_params, /* parameters */
    MI_COUNT(CIM_Job_KillJob_params), /* numParameters */
    sizeof(CIM_Job_KillJob), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_Job"), /* origin */
    MI_T("CIM_Job"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_Job_meths[] =
{
    &CIM_Job_KillJob_rtti,
};

static MI_CONST MI_Char* CIM_Job_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_Job_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Job_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_Job_Version_qual_value = MI_T("2.10.0");

static MI_CONST MI_Qualifier CIM_Job_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Job_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Job_quals[] =
{
    &CIM_Job_UMLPackagePath_qual,
    &CIM_Job_Version_qual,
};

/* class CIM_Job */
MI_CONST MI_ClassDecl CIM_Job_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00636207, /* code */
    MI_T("CIM_Job"), /* name */
    CIM_Job_quals, /* qualifiers */
    MI_COUNT(CIM_Job_quals), /* numQualifiers */
    CIM_Job_props, /* properties */
    MI_COUNT(CIM_Job_props), /* numProperties */
    sizeof(CIM_Job), /* size */
    MI_T("CIM_LogicalElement"), /* superClass */
    &CIM_LogicalElement_rtti, /* superClassDecl */
    CIM_Job_meths, /* methods */
    MI_COUNT(CIM_Job_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_Error
**
**==============================================================================
*/

/* property CIM_Error.ErrorType */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00656509, /* code */
    MI_T("ErrorType"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorType), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.OtherErrorType */
static MI_CONST MI_PropertyDecl CIM_Error_OtherErrorType_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F650E, /* code */
    MI_T("OtherErrorType"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OtherErrorType), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.OwningEntity */
static MI_CONST MI_PropertyDecl CIM_Error_OwningEntity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F790C, /* code */
    MI_T("OwningEntity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OwningEntity), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.MessageID */
static MI_CONST MI_PropertyDecl CIM_Error_MessageID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x006D6409, /* code */
    MI_T("MessageID"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, MessageID), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.Message */
static MI_CONST MI_PropertyDecl CIM_Error_Message_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D6507, /* code */
    MI_T("Message"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, Message), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.MessageArguments */
static MI_CONST MI_PropertyDecl CIM_Error_MessageArguments_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006D7310, /* code */
    MI_T("MessageArguments"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, MessageArguments), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.PerceivedSeverity */
static MI_CONST MI_PropertyDecl CIM_Error_PerceivedSeverity_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00707911, /* code */
    MI_T("PerceivedSeverity"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, PerceivedSeverity), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.ProbableCause */
static MI_CONST MI_PropertyDecl CIM_Error_ProbableCause_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0070650D, /* code */
    MI_T("ProbableCause"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ProbableCause), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.ProbableCauseDescription */
static MI_CONST MI_PropertyDecl CIM_Error_ProbableCauseDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00706E18, /* code */
    MI_T("ProbableCauseDescription"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ProbableCauseDescription), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.RecommendedActions */
static MI_CONST MI_PropertyDecl CIM_Error_RecommendedActions_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00727312, /* code */
    MI_T("RecommendedActions"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRINGA, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, RecommendedActions), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.ErrorSource */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorSource_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650B, /* code */
    MI_T("ErrorSource"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorSource), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint16 CIM_Error_ErrorSourceFormat_value = 0;

/* property CIM_Error.ErrorSourceFormat */
static MI_CONST MI_PropertyDecl CIM_Error_ErrorSourceFormat_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00657411, /* code */
    MI_T("ErrorSourceFormat"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, ErrorSourceFormat), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    &CIM_Error_ErrorSourceFormat_value,
};

/* property CIM_Error.OtherErrorSourceFormat */
static MI_CONST MI_PropertyDecl CIM_Error_OtherErrorSourceFormat_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F7416, /* code */
    MI_T("OtherErrorSourceFormat"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, OtherErrorSourceFormat), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.CIMStatusCode */
static MI_CONST MI_PropertyDecl CIM_Error_CIMStatusCode_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0063650D, /* code */
    MI_T("CIMStatusCode"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, CIMStatusCode), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

/* property CIM_Error.CIMStatusCodeDescription */
static MI_CONST MI_PropertyDecl CIM_Error_CIMStatusCodeDescription_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00636E18, /* code */
    MI_T("CIMStatusCodeDescription"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_Error, CIMStatusCodeDescription), /* offset */
    MI_T("CIM_Error"), /* origin */
    MI_T("CIM_Error"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_Error_props[] =
{
    &CIM_Error_ErrorType_prop,
    &CIM_Error_OtherErrorType_prop,
    &CIM_Error_OwningEntity_prop,
    &CIM_Error_MessageID_prop,
    &CIM_Error_Message_prop,
    &CIM_Error_MessageArguments_prop,
    &CIM_Error_PerceivedSeverity_prop,
    &CIM_Error_ProbableCause_prop,
    &CIM_Error_ProbableCauseDescription_prop,
    &CIM_Error_RecommendedActions_prop,
    &CIM_Error_ErrorSource_prop,
    &CIM_Error_ErrorSourceFormat_prop,
    &CIM_Error_OtherErrorSourceFormat_prop,
    &CIM_Error_CIMStatusCode_prop,
    &CIM_Error_CIMStatusCodeDescription_prop,
};

static MI_CONST MI_Char* CIM_Error_Version_qual_value = MI_T("2.22.1");

static MI_CONST MI_Qualifier CIM_Error_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_Error_Version_qual_value
};

static MI_CONST MI_Char* CIM_Error_UMLPackagePath_qual_value = MI_T("CIM::Interop");

static MI_CONST MI_Qualifier CIM_Error_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_Error_UMLPackagePath_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_Error_quals[] =
{
    &CIM_Error_Version_qual,
    &CIM_Error_UMLPackagePath_qual,
};

/* class CIM_Error */
MI_CONST MI_ClassDecl CIM_Error_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_INDICATION, /* flags */
    0x00637209, /* code */
    MI_T("CIM_Error"), /* name */
    CIM_Error_quals, /* qualifiers */
    MI_COUNT(CIM_Error_quals), /* numQualifiers */
    CIM_Error_props, /* properties */
    MI_COUNT(CIM_Error_props), /* numProperties */
    sizeof(CIM_Error), /* size */
    NULL, /* superClass */
    NULL, /* superClassDecl */
    NULL, /* methods */
    0, /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_ConcreteJob
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_ConcreteJob_InstanceID_Override_qual_value = MI_T("InstanceID");

static MI_CONST MI_Qualifier CIM_ConcreteJob_InstanceID_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_InstanceID_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_InstanceID_quals[] =
{
    &CIM_ConcreteJob_InstanceID_Override_qual,
};

/* property CIM_ConcreteJob.InstanceID */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    CIM_ConcreteJob_InstanceID_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint32 CIM_ConcreteJob_Name_MaxLen_qual_value = 1024U;

static MI_CONST MI_Qualifier CIM_ConcreteJob_Name_MaxLen_qual =
{
    MI_T("MaxLen"),
    MI_UINT32,
    0,
    &CIM_ConcreteJob_Name_MaxLen_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_Name_Override_qual_value = MI_T("Name");

static MI_CONST MI_Qualifier CIM_ConcreteJob_Name_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_Name_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_Name_quals[] =
{
    &CIM_ConcreteJob_Name_MaxLen_qual,
    &CIM_ConcreteJob_Name_Override_qual,
};

/* property CIM_ConcreteJob.Name */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_Name_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x006E6504, /* code */
    MI_T("Name"), /* name */
    CIM_ConcreteJob_Name_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_Name_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, Name), /* offset */
    MI_T("CIM_ManagedSystemElement"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

/* property CIM_ConcreteJob.JobState */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_JobState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006A6508, /* code */
    MI_T("JobState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, JobState), /* offset */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

/* property CIM_ConcreteJob.TimeOfLastStateChange */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_TimeOfLastStateChange_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746515, /* code */
    MI_T("TimeOfLastStateChange"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, TimeOfLastStateChange), /* offset */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    NULL,
};

static MI_CONST MI_Datetime CIM_ConcreteJob_TimeBeforeRemoval_value = {0,{{0,0,5,0,0}}};

/* property CIM_ConcreteJob.TimeBeforeRemoval */
static MI_CONST MI_PropertyDecl CIM_ConcreteJob_TimeBeforeRemoval_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_REQUIRED, /* flags */
    0x00746C11, /* code */
    MI_T("TimeBeforeRemoval"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob, TimeBeforeRemoval), /* offset */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &CIM_ConcreteJob_TimeBeforeRemoval_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_ConcreteJob_props[] =
{
    &CIM_ConcreteJob_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ConcreteJob_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_Job_JobStatus_prop,
    &CIM_Job_TimeSubmitted_prop,
    &CIM_Job_ScheduledStartTime_prop,
    &CIM_Job_StartTime_prop,
    &CIM_Job_ElapsedTime_prop,
    &CIM_Job_JobRunTimes_prop,
    &CIM_Job_RunMonth_prop,
    &CIM_Job_RunDay_prop,
    &CIM_Job_RunDayOfWeek_prop,
    &CIM_Job_RunStartInterval_prop,
    &CIM_Job_LocalOrUtcTime_prop,
    &CIM_Job_UntilTime_prop,
    &CIM_Job_Notify_prop,
    &CIM_Job_Owner_prop,
    &CIM_Job_Priority_prop,
    &CIM_Job_PercentComplete_prop,
    &CIM_Job_DeleteOnCompletion_prop,
    &CIM_Job_ErrorCode_prop,
    &CIM_Job_ErrorDescription_prop,
    &CIM_Job_RecoveryAction_prop,
    &CIM_Job_OtherRecoveryAction_prop,
    &CIM_ConcreteJob_JobState_prop,
    &CIM_ConcreteJob_TimeOfLastStateChange_prop,
    &CIM_ConcreteJob_TimeBeforeRemoval_prop,
};

/* parameter CIM_ConcreteJob.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_RequestStateChange, RequestedState), /* offset */
};

/* parameter CIM_ConcreteJob.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_RequestStateChange, TimeoutPeriod), /* offset */
};

/* parameter CIM_ConcreteJob.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_ConcreteJob_RequestStateChange_params[] =
{
    &CIM_ConcreteJob_RequestStateChange_MIReturn_param,
    &CIM_ConcreteJob_RequestStateChange_RequestedState_param,
    &CIM_ConcreteJob_RequestStateChange_TimeoutPeriod_param,
};

/* method CIM_ConcreteJob.RequestStateChange() */
MI_CONST MI_MethodDecl CIM_ConcreteJob_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_ConcreteJob_RequestStateChange_params, /* parameters */
    MI_COUNT(CIM_ConcreteJob_RequestStateChange_params), /* numParameters */
    sizeof(CIM_ConcreteJob_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.GetErrors"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_GetError_Deprecated_qual_value =
{
    CIM_ConcreteJob_GetError_Deprecated_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_GetError_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_GetError_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetError_quals[] =
{
    &CIM_ConcreteJob_GetError_Deprecated_qual,
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual_value = MI_T("CIM_Error");

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetError_Error_quals[] =
{
    &CIM_ConcreteJob_GetError_Error_EmbeddedInstance_qual,
};

/* parameter CIM_ConcreteJob.GetError(): Error */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_GetError_Error_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00657205, /* code */
    MI_T("Error"), /* name */
    CIM_ConcreteJob_GetError_Error_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetError_Error_quals), /* numQualifiers */
    MI_INSTANCE, /* type */
    MI_T("CIM_Error"), /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_GetError, Error), /* offset */
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.GetErrors"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual_value =
{
    CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetError_MIReturn_quals[] =
{
    &CIM_ConcreteJob_GetError_MIReturn_Deprecated_qual,
};

/* parameter CIM_ConcreteJob.GetError(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_GetError_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    CIM_ConcreteJob_GetError_MIReturn_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetError_MIReturn_quals), /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_GetError, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_ConcreteJob_GetError_params[] =
{
    &CIM_ConcreteJob_GetError_MIReturn_param,
    &CIM_ConcreteJob_GetError_Error_param,
};

/* method CIM_ConcreteJob.GetError() */
MI_CONST MI_MethodDecl CIM_ConcreteJob_GetError_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677208, /* code */
    MI_T("GetError"), /* name */
    CIM_ConcreteJob_GetError_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetError_quals), /* numQualifiers */
    CIM_ConcreteJob_GetError_params, /* parameters */
    MI_COUNT(CIM_ConcreteJob_GetError_params), /* numParameters */
    sizeof(CIM_ConcreteJob_GetError), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_CONST MI_Char* CIM_ConcreteJob_GetErrors_Errors_EmbeddedInstance_qual_value = MI_T("CIM_Error");

static MI_CONST MI_Qualifier CIM_ConcreteJob_GetErrors_Errors_EmbeddedInstance_qual =
{
    MI_T("EmbeddedInstance"),
    MI_STRING,
    0,
    &CIM_ConcreteJob_GetErrors_Errors_EmbeddedInstance_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_GetErrors_Errors_quals[] =
{
    &CIM_ConcreteJob_GetErrors_Errors_EmbeddedInstance_qual,
};

/* parameter CIM_ConcreteJob.GetErrors(): Errors */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_GetErrors_Errors_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x00657306, /* code */
    MI_T("Errors"), /* name */
    CIM_ConcreteJob_GetErrors_Errors_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_GetErrors_Errors_quals), /* numQualifiers */
    MI_INSTANCEA, /* type */
    MI_T("CIM_Error"), /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_GetErrors, Errors), /* offset */
};

/* parameter CIM_ConcreteJob.GetErrors(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_ConcreteJob_GetErrors_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_ConcreteJob_GetErrors, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_ConcreteJob_GetErrors_params[] =
{
    &CIM_ConcreteJob_GetErrors_MIReturn_param,
    &CIM_ConcreteJob_GetErrors_Errors_param,
};

/* method CIM_ConcreteJob.GetErrors() */
MI_CONST MI_MethodDecl CIM_ConcreteJob_GetErrors_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00677309, /* code */
    MI_T("GetErrors"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_ConcreteJob_GetErrors_params, /* parameters */
    MI_COUNT(CIM_ConcreteJob_GetErrors_params), /* numParameters */
    sizeof(CIM_ConcreteJob_GetErrors), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_ConcreteJob"), /* origin */
    MI_T("CIM_ConcreteJob"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_ConcreteJob_meths[] =
{
    &CIM_Job_KillJob_rtti,
    &CIM_ConcreteJob_RequestStateChange_rtti,
    &CIM_ConcreteJob_GetError_rtti,
    &CIM_ConcreteJob_GetErrors_rtti,
};

static MI_CONST MI_Char* CIM_ConcreteJob_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_ConcreteJob_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_ConcreteJob_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_Deprecated_qual_data_value[] =
{
    MI_T("CIM_ConcreteJob.GetErrors"),
};

static MI_CONST MI_ConstStringA CIM_ConcreteJob_Deprecated_qual_value =
{
    CIM_ConcreteJob_Deprecated_qual_data_value,
    MI_COUNT(CIM_ConcreteJob_Deprecated_qual_data_value),
};

static MI_CONST MI_Qualifier CIM_ConcreteJob_Deprecated_qual =
{
    MI_T("Deprecated"),
    MI_STRINGA,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_Deprecated_qual_value
};

static MI_CONST MI_Char* CIM_ConcreteJob_Version_qual_value = MI_T("2.31.1");

static MI_CONST MI_Qualifier CIM_ConcreteJob_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_ConcreteJob_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_ConcreteJob_quals[] =
{
    &CIM_ConcreteJob_UMLPackagePath_qual,
    &CIM_ConcreteJob_Deprecated_qual,
    &CIM_ConcreteJob_Version_qual,
};

/* class CIM_ConcreteJob */
MI_CONST MI_ClassDecl CIM_ConcreteJob_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x0063620F, /* code */
    MI_T("CIM_ConcreteJob"), /* name */
    CIM_ConcreteJob_quals, /* qualifiers */
    MI_COUNT(CIM_ConcreteJob_quals), /* numQualifiers */
    CIM_ConcreteJob_props, /* properties */
    MI_COUNT(CIM_ConcreteJob_props), /* numProperties */
    sizeof(CIM_ConcreteJob), /* size */
    MI_T("CIM_Job"), /* superClass */
    &CIM_Job_rtti, /* superClassDecl */
    CIM_ConcreteJob_meths, /* methods */
    MI_COUNT(CIM_ConcreteJob_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_EnabledLogicalElement
**
**==============================================================================
*/

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_EnabledState_value = 5;

/* property CIM_EnabledLogicalElement.EnabledState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_EnabledState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065650C, /* code */
    MI_T("EnabledState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, EnabledState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_EnabledState_value,
};

/* property CIM_EnabledLogicalElement.OtherEnabledState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_OtherEnabledState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006F6511, /* code */
    MI_T("OtherEnabledState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, OtherEnabledState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_RequestedState_value = 12;

/* property CIM_EnabledLogicalElement.RequestedState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_RequestedState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, RequestedState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_RequestedState_value,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_EnabledDefault_value = 2;

/* property CIM_EnabledLogicalElement.EnabledDefault */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_EnabledDefault_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0065740E, /* code */
    MI_T("EnabledDefault"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, EnabledDefault), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_EnabledDefault_value,
};

/* property CIM_EnabledLogicalElement.TimeOfLastStateChange */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_TimeOfLastStateChange_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746515, /* code */
    MI_T("TimeOfLastStateChange"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, TimeOfLastStateChange), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    NULL,
};

/* property CIM_EnabledLogicalElement.AvailableRequestedStates */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_AvailableRequestedStates_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00617318, /* code */
    MI_T("AvailableRequestedStates"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16A, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, AvailableRequestedStates), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    NULL,
};

static MI_CONST MI_Uint16 CIM_EnabledLogicalElement_TransitioningToState_value = 12;

/* property CIM_EnabledLogicalElement.TransitioningToState */
static MI_CONST MI_PropertyDecl CIM_EnabledLogicalElement_TransitioningToState_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00746514, /* code */
    MI_T("TransitioningToState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement, TransitioningToState), /* offset */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &CIM_EnabledLogicalElement_TransitioningToState_value,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_EnabledLogicalElement_props[] =
{
    &CIM_ManagedElement_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, RequestedState), /* offset */
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): Job */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_Job_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006A6203, /* code */
    MI_T("Job"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ConcreteJob"), /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, Job), /* offset */
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, TimeoutPeriod), /* offset */
};

/* parameter CIM_EnabledLogicalElement.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl CIM_EnabledLogicalElement_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_EnabledLogicalElement_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST CIM_EnabledLogicalElement_RequestStateChange_params[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_MIReturn_param,
    &CIM_EnabledLogicalElement_RequestStateChange_RequestedState_param,
    &CIM_EnabledLogicalElement_RequestStateChange_Job_param,
    &CIM_EnabledLogicalElement_RequestStateChange_TimeoutPeriod_param,
};

/* method CIM_EnabledLogicalElement.RequestStateChange() */
MI_CONST MI_MethodDecl CIM_EnabledLogicalElement_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    CIM_EnabledLogicalElement_RequestStateChange_params, /* parameters */
    MI_COUNT(CIM_EnabledLogicalElement_RequestStateChange_params), /* numParameters */
    sizeof(CIM_EnabledLogicalElement_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &schemaDecl, /* schema */
    NULL, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_EnabledLogicalElement_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_UMLPackagePath_qual_value = MI_T("CIM::Core::CoreElements");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_EnabledLogicalElement_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_EnabledLogicalElement_Version_qual_value = MI_T("2.22.0");

static MI_CONST MI_Qualifier CIM_EnabledLogicalElement_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_EnabledLogicalElement_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_EnabledLogicalElement_quals[] =
{
    &CIM_EnabledLogicalElement_UMLPackagePath_qual,
    &CIM_EnabledLogicalElement_Version_qual,
};

/* class CIM_EnabledLogicalElement */
MI_CONST MI_ClassDecl CIM_EnabledLogicalElement_rtti =
{
    MI_FLAG_CLASS|MI_FLAG_ABSTRACT, /* flags */
    0x00637419, /* code */
    MI_T("CIM_EnabledLogicalElement"), /* name */
    CIM_EnabledLogicalElement_quals, /* qualifiers */
    MI_COUNT(CIM_EnabledLogicalElement_quals), /* numQualifiers */
    CIM_EnabledLogicalElement_props, /* properties */
    MI_COUNT(CIM_EnabledLogicalElement_props), /* numProperties */
    sizeof(CIM_EnabledLogicalElement), /* size */
    MI_T("CIM_LogicalElement"), /* superClass */
    &CIM_LogicalElement_rtti, /* superClassDecl */
    CIM_EnabledLogicalElement_meths, /* methods */
    MI_COUNT(CIM_EnabledLogicalElement_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** CIM_CommonDatabase
**
**==============================================================================
*/

static MI_CONST MI_Char* CIM_CommonDatabase_InstanceID_Override_qual_value = MI_T("InstanceID");

static MI_CONST MI_Qualifier CIM_CommonDatabase_InstanceID_Override_qual =
{
    MI_T("Override"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_RESTRICTED,
    &CIM_CommonDatabase_InstanceID_Override_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_CommonDatabase_InstanceID_quals[] =
{
    &CIM_CommonDatabase_InstanceID_Override_qual,
};

/* property CIM_CommonDatabase.InstanceID */
static MI_CONST MI_PropertyDecl CIM_CommonDatabase_InstanceID_prop =
{
    MI_FLAG_PROPERTY|MI_FLAG_KEY, /* flags */
    0x0069640A, /* code */
    MI_T("InstanceID"), /* name */
    CIM_CommonDatabase_InstanceID_quals, /* qualifiers */
    MI_COUNT(CIM_CommonDatabase_InstanceID_quals), /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_CommonDatabase, InstanceID), /* offset */
    MI_T("CIM_ManagedElement"), /* origin */
    MI_T("CIM_CommonDatabase"), /* propagator */
    NULL,
};

/* property CIM_CommonDatabase.DatabaseVersion */
static MI_CONST MI_PropertyDecl CIM_CommonDatabase_DatabaseVersion_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00646E0F, /* code */
    MI_T("DatabaseVersion"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_CommonDatabase, DatabaseVersion), /* offset */
    MI_T("CIM_CommonDatabase"), /* origin */
    MI_T("CIM_CommonDatabase"), /* propagator */
    NULL,
};

/* property CIM_CommonDatabase.LastBackup */
static MI_CONST MI_PropertyDecl CIM_CommonDatabase_LastBackup_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006C700A, /* code */
    MI_T("LastBackup"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_CommonDatabase, LastBackup), /* offset */
    MI_T("CIM_CommonDatabase"), /* origin */
    MI_T("CIM_CommonDatabase"), /* propagator */
    NULL,
};

/* property CIM_CommonDatabase.SizeAllocated */
static MI_CONST MI_PropertyDecl CIM_CommonDatabase_SizeAllocated_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0073640D, /* code */
    MI_T("SizeAllocated"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_CommonDatabase, SizeAllocated), /* offset */
    MI_T("CIM_CommonDatabase"), /* origin */
    MI_T("CIM_CommonDatabase"), /* propagator */
    NULL,
};

/* property CIM_CommonDatabase.SizeUnits */
static MI_CONST MI_PropertyDecl CIM_CommonDatabase_SizeUnits_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00737309, /* code */
    MI_T("SizeUnits"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(CIM_CommonDatabase, SizeUnits), /* offset */
    MI_T("CIM_CommonDatabase"), /* origin */
    MI_T("CIM_CommonDatabase"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST CIM_CommonDatabase_props[] =
{
    &CIM_CommonDatabase_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_CommonDatabase_DatabaseVersion_prop,
    &CIM_CommonDatabase_LastBackup_prop,
    &CIM_CommonDatabase_SizeAllocated_prop,
    &CIM_CommonDatabase_SizeUnits_prop,
};

static MI_MethodDecl MI_CONST* MI_CONST CIM_CommonDatabase_meths[] =
{
    &CIM_EnabledLogicalElement_RequestStateChange_rtti,
};

static MI_CONST MI_Char* CIM_CommonDatabase_UMLPackagePath_qual_value = MI_T("CIM::Database::System");

static MI_CONST MI_Qualifier CIM_CommonDatabase_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &CIM_CommonDatabase_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* CIM_CommonDatabase_Version_qual_value = MI_T("2.19.0");

static MI_CONST MI_Qualifier CIM_CommonDatabase_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &CIM_CommonDatabase_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST CIM_CommonDatabase_quals[] =
{
    &CIM_CommonDatabase_UMLPackagePath_qual,
    &CIM_CommonDatabase_Version_qual,
};

/* class CIM_CommonDatabase */
MI_CONST MI_ClassDecl CIM_CommonDatabase_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x00636512, /* code */
    MI_T("CIM_CommonDatabase"), /* name */
    CIM_CommonDatabase_quals, /* qualifiers */
    MI_COUNT(CIM_CommonDatabase_quals), /* numQualifiers */
    CIM_CommonDatabase_props, /* properties */
    MI_COUNT(CIM_CommonDatabase_props), /* numProperties */
    sizeof(CIM_CommonDatabase), /* size */
    MI_T("CIM_EnabledLogicalElement"), /* superClass */
    &CIM_EnabledLogicalElement_rtti, /* superClassDecl */
    CIM_CommonDatabase_meths, /* methods */
    MI_COUNT(CIM_CommonDatabase_meths), /* numMethods */
    &schemaDecl, /* schema */
    NULL, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** MySQL_Server_Database
**
**==============================================================================
*/

/* property MySQL_Server_Database.DatabaseName */
static MI_CONST MI_PropertyDecl MySQL_Server_Database_DatabaseName_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x0064650C, /* code */
    MI_T("DatabaseName"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_STRING, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_Database, DatabaseName), /* offset */
    MI_T("MySQL_Server_Database"), /* origin */
    MI_T("MySQL_Server_Database"), /* propagator */
    NULL,
};

/* property MySQL_Server_Database.NumberOfTables */
static MI_CONST MI_PropertyDecl MySQL_Server_Database_NumberOfTables_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x006E730E, /* code */
    MI_T("NumberOfTables"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_Database, NumberOfTables), /* offset */
    MI_T("MySQL_Server_Database"), /* origin */
    MI_T("MySQL_Server_Database"), /* propagator */
    NULL,
};

/* property MySQL_Server_Database.DiskSpaceInBytes */
static MI_CONST MI_PropertyDecl MySQL_Server_Database_DiskSpaceInBytes_prop =
{
    MI_FLAG_PROPERTY, /* flags */
    0x00647310, /* code */
    MI_T("DiskSpaceInBytes"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT64, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_Database, DiskSpaceInBytes), /* offset */
    MI_T("MySQL_Server_Database"), /* origin */
    MI_T("MySQL_Server_Database"), /* propagator */
    NULL,
};

static MI_PropertyDecl MI_CONST* MI_CONST MySQL_Server_Database_props[] =
{
    &CIM_CommonDatabase_InstanceID_prop,
    &CIM_ManagedElement_Caption_prop,
    &CIM_ManagedElement_Description_prop,
    &CIM_ManagedElement_ElementName_prop,
    &CIM_ManagedSystemElement_InstallDate_prop,
    &CIM_ManagedSystemElement_Name_prop,
    &CIM_ManagedSystemElement_OperationalStatus_prop,
    &CIM_ManagedSystemElement_StatusDescriptions_prop,
    &CIM_ManagedSystemElement_Status_prop,
    &CIM_ManagedSystemElement_HealthState_prop,
    &CIM_ManagedSystemElement_CommunicationStatus_prop,
    &CIM_ManagedSystemElement_DetailedStatus_prop,
    &CIM_ManagedSystemElement_OperatingStatus_prop,
    &CIM_ManagedSystemElement_PrimaryStatus_prop,
    &CIM_EnabledLogicalElement_EnabledState_prop,
    &CIM_EnabledLogicalElement_OtherEnabledState_prop,
    &CIM_EnabledLogicalElement_RequestedState_prop,
    &CIM_EnabledLogicalElement_EnabledDefault_prop,
    &CIM_EnabledLogicalElement_TimeOfLastStateChange_prop,
    &CIM_EnabledLogicalElement_AvailableRequestedStates_prop,
    &CIM_EnabledLogicalElement_TransitioningToState_prop,
    &CIM_CommonDatabase_DatabaseVersion_prop,
    &CIM_CommonDatabase_LastBackup_prop,
    &CIM_CommonDatabase_SizeAllocated_prop,
    &CIM_CommonDatabase_SizeUnits_prop,
    &MySQL_Server_Database_DatabaseName_prop,
    &MySQL_Server_Database_NumberOfTables_prop,
    &MySQL_Server_Database_DiskSpaceInBytes_prop,
};

/* parameter MySQL_Server_Database.RequestStateChange(): RequestedState */
static MI_CONST MI_ParameterDecl MySQL_Server_Database_RequestStateChange_RequestedState_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0072650E, /* code */
    MI_T("RequestedState"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT16, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_Database_RequestStateChange, RequestedState), /* offset */
};

/* parameter MySQL_Server_Database.RequestStateChange(): Job */
static MI_CONST MI_ParameterDecl MySQL_Server_Database_RequestStateChange_Job_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006A6203, /* code */
    MI_T("Job"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_REFERENCE, /* type */
    MI_T("CIM_ConcreteJob"), /* className */
    0, /* subscript */
    offsetof(MySQL_Server_Database_RequestStateChange, Job), /* offset */
};

/* parameter MySQL_Server_Database.RequestStateChange(): TimeoutPeriod */
static MI_CONST MI_ParameterDecl MySQL_Server_Database_RequestStateChange_TimeoutPeriod_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_IN, /* flags */
    0x0074640D, /* code */
    MI_T("TimeoutPeriod"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_DATETIME, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_Database_RequestStateChange, TimeoutPeriod), /* offset */
};

/* parameter MySQL_Server_Database.RequestStateChange(): MIReturn */
static MI_CONST MI_ParameterDecl MySQL_Server_Database_RequestStateChange_MIReturn_param =
{
    MI_FLAG_PARAMETER|MI_FLAG_OUT, /* flags */
    0x006D6E08, /* code */
    MI_T("MIReturn"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MI_UINT32, /* type */
    NULL, /* className */
    0, /* subscript */
    offsetof(MySQL_Server_Database_RequestStateChange, MIReturn), /* offset */
};

static MI_ParameterDecl MI_CONST* MI_CONST MySQL_Server_Database_RequestStateChange_params[] =
{
    &MySQL_Server_Database_RequestStateChange_MIReturn_param,
    &MySQL_Server_Database_RequestStateChange_RequestedState_param,
    &MySQL_Server_Database_RequestStateChange_Job_param,
    &MySQL_Server_Database_RequestStateChange_TimeoutPeriod_param,
};

/* method MySQL_Server_Database.RequestStateChange() */
MI_CONST MI_MethodDecl MySQL_Server_Database_RequestStateChange_rtti =
{
    MI_FLAG_METHOD, /* flags */
    0x00726512, /* code */
    MI_T("RequestStateChange"), /* name */
    NULL, /* qualifiers */
    0, /* numQualifiers */
    MySQL_Server_Database_RequestStateChange_params, /* parameters */
    MI_COUNT(MySQL_Server_Database_RequestStateChange_params), /* numParameters */
    sizeof(MySQL_Server_Database_RequestStateChange), /* size */
    MI_UINT32, /* returnType */
    MI_T("CIM_EnabledLogicalElement"), /* origin */
    MI_T("CIM_EnabledLogicalElement"), /* propagator */
    &schemaDecl, /* schema */
    (MI_ProviderFT_Invoke)MySQL_Server_Database_Invoke_RequestStateChange, /* method */
};

static MI_MethodDecl MI_CONST* MI_CONST MySQL_Server_Database_meths[] =
{
    &MySQL_Server_Database_RequestStateChange_rtti,
};

static MI_CONST MI_ProviderFT MySQL_Server_Database_funcs =
{
  (MI_ProviderFT_Load)MySQL_Server_Database_Load,
  (MI_ProviderFT_Unload)MySQL_Server_Database_Unload,
  (MI_ProviderFT_GetInstance)MySQL_Server_Database_GetInstance,
  (MI_ProviderFT_EnumerateInstances)MySQL_Server_Database_EnumerateInstances,
  (MI_ProviderFT_CreateInstance)MySQL_Server_Database_CreateInstance,
  (MI_ProviderFT_ModifyInstance)MySQL_Server_Database_ModifyInstance,
  (MI_ProviderFT_DeleteInstance)MySQL_Server_Database_DeleteInstance,
  (MI_ProviderFT_AssociatorInstances)NULL,
  (MI_ProviderFT_ReferenceInstances)NULL,
  (MI_ProviderFT_EnableIndications)NULL,
  (MI_ProviderFT_DisableIndications)NULL,
  (MI_ProviderFT_Subscribe)NULL,
  (MI_ProviderFT_Unsubscribe)NULL,
  (MI_ProviderFT_Invoke)NULL,
};

static MI_CONST MI_Char* MySQL_Server_Database_UMLPackagePath_qual_value = MI_T("CIM::Database::System");

static MI_CONST MI_Qualifier MySQL_Server_Database_UMLPackagePath_qual =
{
    MI_T("UMLPackagePath"),
    MI_STRING,
    0,
    &MySQL_Server_Database_UMLPackagePath_qual_value
};

static MI_CONST MI_Char* MySQL_Server_Database_Version_qual_value = MI_T("1.0.0");

static MI_CONST MI_Qualifier MySQL_Server_Database_Version_qual =
{
    MI_T("Version"),
    MI_STRING,
    MI_FLAG_ENABLEOVERRIDE|MI_FLAG_TRANSLATABLE|MI_FLAG_RESTRICTED,
    &MySQL_Server_Database_Version_qual_value
};

static MI_Qualifier MI_CONST* MI_CONST MySQL_Server_Database_quals[] =
{
    &MySQL_Server_Database_UMLPackagePath_qual,
    &MySQL_Server_Database_Version_qual,
};

/* class MySQL_Server_Database */
MI_CONST MI_ClassDecl MySQL_Server_Database_rtti =
{
    MI_FLAG_CLASS, /* flags */
    0x006D6515, /* code */
    MI_T("MySQL_Server_Database"), /* name */
    MySQL_Server_Database_quals, /* qualifiers */
    MI_COUNT(MySQL_Server_Database_quals), /* numQualifiers */
    MySQL_Server_Database_props, /* properties */
    MI_COUNT(MySQL_Server_Database_props), /* numProperties */
    sizeof(MySQL_Server_Database), /* size */
    MI_T("CIM_CommonDatabase"), /* superClass */
    &CIM_CommonDatabase_rtti, /* superClassDecl */
    MySQL_Server_Database_meths, /* methods */
    MI_COUNT(MySQL_Server_Database_meths), /* numMethods */
    &schemaDecl, /* schema */
    &MySQL_Server_Database_funcs, /* functions */
    NULL, /* owningClass */
};

/*
**==============================================================================
**
** __mi_server
**
**==============================================================================
*/

MI_Server* __mi_server;
/*
**==============================================================================
**
** Schema
**
**==============================================================================
*/

static MI_ClassDecl MI_CONST* MI_CONST classes[] =
{
    &CIM_Collection_rtti,
    &CIM_CommonDatabase_rtti,
    &CIM_ConcreteJob_rtti,
    &CIM_EnabledLogicalElement_rtti,
    &CIM_Error_rtti,
    &CIM_InstalledProduct_rtti,
    &CIM_Job_rtti,
    &CIM_LogicalElement_rtti,
    &CIM_ManagedElement_rtti,
    &CIM_ManagedSystemElement_rtti,
    &CIM_StatisticalData_rtti,
    &MySQL_Server_rtti,
    &MySQL_ServerStatistics_rtti,
    &MySQL_Server_Database_rtti,
};

MI_SchemaDecl schemaDecl =
{
    NULL, /* qualifierDecls */
    0, /* numQualifierDecls */
    classes, /* classDecls */
    MI_COUNT(classes), /* classDecls */
};

/*
**==============================================================================
**
** MI_Server Methods
**
**==============================================================================
*/

MI_Result MI_CALL MI_Server_GetVersion(
    MI_Uint32* version){
    return __mi_server->serverFT->GetVersion(version);
}

MI_Result MI_CALL MI_Server_GetSystemName(
    const MI_Char** systemName)
{
    return __mi_server->serverFT->GetSystemName(systemName);
}

