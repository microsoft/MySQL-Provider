/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.

    Created date    2014-11-20 07:40:00

    MySQL_Server_Class_Provider unit tests.

    Only tests the functionality of the provider class.

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/scxfile.h>
#include <scxcorelib/scxnameresolver.h>
#include <scxcorelib/stringaid.h>
#include <util/Base64Helper.h>
#include <testutils/scxunit.h>
#include <testutils/providertestutils.h>

#include "MySQL_Server_Class_Provider.h"
#include "sqlbinding.h"
#include "sqlcredentials.h"
#include "testablefactory.h"

#include <iostream> // for cout


#if defined(PF_DISTRO_ULINUX)

static const std::wstring s_sql_Version( L"5.0.26" );
static const std::wstring s_sql_Server_id( L"1" );
static const std::wstring s_sql_Version_compile_os( L"suse-linux" );
static const std::wstring s_sql_log_error( L"" );

#elif defined(PF_DISTRO_REDHAT)

static const std::wstring s_sql_Version( L"5.1.52" );
static const std::wstring s_sql_Server_id( L"0" );
static const std::wstring s_sql_Version_compile_os( L"redhat-linux-gnu" );
static const std::wstring s_sql_log_error( L"/var/log/mysqld.log" );

#else
#error Unknown configuration
#endif


using namespace SCXCoreLib;

class MySQL_Server_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( MySQL_Server_Test );

    CPPUNIT_TEST( TestEnumerateInstancesKeysOnly );
    CPPUNIT_TEST( TestEnumerateInstances );
    CPPUNIT_TEST( TestVerifyKeyCompletePartial );
    CPPUNIT_TEST( TestGetInstance );

    // Note that MySQL_Authentication has a rich set of tests; we just do very basic testing
    // here, just to insure proper handling of parameters, in order to avoid test duplication
    CPPUNIT_TEST( TestInvoke_UpdateCredentials_NoPort_Fails );
    CPPUNIT_TEST( TestInvoke_UpdateCredentials_AllParameters );
    CPPUNIT_TEST( TestInvoke_UpdateCredentials_OptionalParameters );
    CPPUNIT_TEST( TestInvoke_UpdateCredentials_WithEncodedPassword );
    CPPUNIT_TEST( TestInvoke_DeleteCredentials_NoPort_Fails );
    CPPUNIT_TEST( TestInvoke_DeleteCredentials_WithPort_Succeeds );

    SCXUNIT_TEST_ATTRIBUTE(TestEnumerateInstancesKeysOnly, SLOW);
    SCXUNIT_TEST_ATTRIBUTE(TestEnumerateInstances, SLOW);
    SCXUNIT_TEST_ATTRIBUTE(TestVerifyKeyCompletePartial, SLOW);
    SCXUNIT_TEST_ATTRIBUTE(TestGetInstance, SLOW);
    CPPUNIT_TEST_SUITE_END();

private:
    std::vector<std::wstring> m_keyNames;

public:
    void setUp(void)
    {
        // Use the testable factory for control over dependencies
        g_pFactory = NULL;
        g_pFactory = new MySQL_TestableFactory();

        // Load the provider
        std::wstring errMsg;
        TestableContext context;
        SetUpAgent<mi::MySQL_Server_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

        m_keyNames.push_back(L"ProductIdentifyingNumber");
        m_keyNames.push_back(L"ProductName");
        m_keyNames.push_back(L"ProductVendor");
        m_keyNames.push_back(L"ProductVersion");
        m_keyNames.push_back(L"SystemID");
        m_keyNames.push_back(L"CollectionID");
    }

    void tearDown(void)
    {
        // Delete the authentication file
        SCXCoreLib::SCXFile::Delete( s_authFilePath );

        // Unload the provider
        std::wstring errMsg;
        TestableContext context;
        TearDownAgent<mi::MySQL_Server_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

        // Clean up the testable factory
        g_pFactory = NULL;
    }

    void TestEnumerateInstancesKeysOnly()
    {
        // We'll fail if we don't have a valid authentication rule
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        CPPUNIT_ASSERT_NO_THROW( pAuth->AddCredentialSet(sqlPort, sqlHostname, sqlUsername, sqlPassword) );
        CPPUNIT_ASSERT_NO_THROW( pAuth->Save() );

        std::wstring errMsg;
        TestableContext context;
        StandardTestEnumerateKeysOnly<mi::MySQL_Server_Class_Provider>(
            m_keyNames, context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL(1u, context.Size());

        // Verify the ProductIdentifyingNumber
        SCXCoreLib::NameResolver nr;
        CPPUNIT_ASSERT_EQUAL(nr.GetHostname() + L":" + StrFromUTF8(sqlHostname) + L":" + StrFrom(sqlPort),
                             context[0].GetKey(L"ProductIdentifyingNumber", CALL_LOCATION(errMsg)));
    }

    void TestEnumerateInstances()
    {
        // We'll fail if we don't have a valid authentication rule
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        CPPUNIT_ASSERT_NO_THROW( pAuth->AddCredentialSet(sqlPort, sqlHostname, sqlUsername, sqlPassword) );
        CPPUNIT_ASSERT_NO_THROW( pAuth->Save() );

        std::wstring errMsg;
        TestableContext context;
        StandardTestEnumerateInstances<mi::MySQL_Server_Class_Provider>(
            m_keyNames, context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL(1u, context.Size());
        ValidateInstance(context, CALL_LOCATION(errMsg));
    }

    void TestVerifyKeyCompletePartial()
    {
        // We'll fail if we don't have a valid authentication rule
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        CPPUNIT_ASSERT_NO_THROW( pAuth->AddCredentialSet(sqlPort, sqlHostname, sqlUsername, sqlPassword) );
        CPPUNIT_ASSERT_NO_THROW( pAuth->Save() );

        std::wstring errMsg;
        StandardTestVerifyGetInstanceKeys<mi::MySQL_Server_Class_Provider,
                mi::MySQL_Server_Class>(m_keyNames, CALL_LOCATION(errMsg));
    }

    void TestGetInstance()
    {
        std::wstring errMsg;

        SCXCoreLib::NameResolver nr;
        std::vector<std::wstring> keyValues;
        keyValues.push_back( nr.GetHostname() + L":" + StrFromUTF8(sqlHostname) + L":" + StrFrom(sqlPort) );
        keyValues.push_back( L"MySQL" );
        keyValues.push_back( L"Oracle" );
        keyValues.push_back( s_sql_Version );
        keyValues.push_back( s_sql_Server_id );
        keyValues.push_back( s_sql_Version_compile_os );

        // We'll fail if we don't have a valid authentication rule
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        CPPUNIT_ASSERT_NO_THROW( pAuth->AddCredentialSet(sqlPort, sqlHostname, sqlUsername, sqlPassword) );
        CPPUNIT_ASSERT_NO_THROW( pAuth->Save() );

        TestableContext context;
        CPPUNIT_ASSERT_EQUAL(MI_RESULT_OK, (GetInstance<mi::MySQL_Server_Class_Provider,
            mi::MySQL_Server_Class>(m_keyNames, keyValues, context, CALL_LOCATION(errMsg))));
        ValidateInstance(context, CALL_LOCATION(errMsg));
    }

    void TestInvoke_UpdateCredentials_NoPort_Fails()
    {
        // Port is a required parameter - insure we fail if we don't pass it

        TestableContext context;
        mi::MySQL_Server_Class instanceName;
        mi::MySQL_Server_UpdateCredentials_Class param;
        mi::Module Module;
        mi::MySQL_Server_Class_Provider agent(&Module);
        agent.Invoke_UpdateCredentials(context, NULL, instanceName, param);

        std::wstring errMsg;
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, MI_RESULT_INVALID_PARAMETER, context.GetResult());
    }

    void TestInvoke_UpdateCredentials_AllParameters()
    {
        TestableContext context;
        mi::MySQL_Server_Class instanceName;
        mi::MySQL_Server_UpdateCredentials_Class param;
        mi::Module Module;
        mi::MySQL_Server_Class_Provider agent(&Module);

        param.Port_value( 3306 );
        param.BindAddress_value( "localhost" );
        param.Username_value( "root" );
        param.Password_value( "root" );
        agent.Invoke_UpdateCredentials(context, NULL, instanceName, param);

        std::wstring errMsg;
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, MI_RESULT_OK, context.GetResult());
        // We expect one instance to be returned with an MIReturn of success
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, 1u, context.Size());
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE,
             static_cast<bool>(true),
             context[0].GetProperty("MIReturn", CALL_LOCATION(errMsg)).GetValue_MIBoolean(CALL_LOCATION(errMsg)) );

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=localhost, root, cm9vdA=="), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[1] );
    }

    void TestInvoke_UpdateCredentials_OptionalParameters()
    {
        TestableContext context;
        mi::MySQL_Server_Class instanceName;
        mi::Module Module;
        mi::MySQL_Server_Class_Provider agent(&Module);

        {
            // Add default port
            mi::MySQL_Server_UpdateCredentials_Class param;
            param.Port_value( 0 );
            param.BindAddress_value( "localhost" );
            param.Username_value( "root" );
            param.Password_value( "root" );
            agent.Invoke_UpdateCredentials(context, NULL, instanceName, param);
        }

        std::wstring errMsg;
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, MI_RESULT_OK, context.GetResult());
        // We expect one instance to be returned with an MIReturn of success
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, 1u, context.Size());
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE,
             static_cast<bool>(true),
             context[0].GetProperty("MIReturn", CALL_LOCATION(errMsg)).GetValue_MIBoolean(CALL_LOCATION(errMsg)) );

        {
            // Add MySQL port (3306) with optional parameters
            mi::MySQL_Server_UpdateCredentials_Class param;
            param.Port_value( 3306 );
            context.Reset();
            agent.Invoke_UpdateCredentials(context, NULL, instanceName, param);
        }

        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, MI_RESULT_OK, context.GetResult());
        // We expect one instance to be returned with an MIReturn of success
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, 1u, context.Size());
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE,
             static_cast<bool>(true),
             context[0].GetProperty("MIReturn", CALL_LOCATION(errMsg)).GetValue_MIBoolean(CALL_LOCATION(errMsg)) );

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(3), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=localhost, root, cm9vdA=="), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=, ,"), lines[1] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[2] );
    }

    void TestInvoke_UpdateCredentials_WithEncodedPassword()
    {
        TestableContext context;
        mi::MySQL_Server_Class instanceName;
        mi::MySQL_Server_UpdateCredentials_Class param;
        mi::Module Module;
        mi::MySQL_Server_Class_Provider agent(&Module);

        std::string b64Password;
        util::Base64Helper::Encode( "root", b64Password );

        param.Port_value( 0 );
        param.Username_value( "root" );
        param.Password_value( b64Password.c_str() );
        param.B64Encoded_value( true );
        agent.Invoke_UpdateCredentials(context, NULL, instanceName, param);

        std::wstring errMsg;
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, MI_RESULT_OK, context.GetResult());
        // We expect one instance to be returned with an MIReturn of success
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, 1u, context.Size());
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE,
             static_cast<bool>(true),
             context[0].GetProperty("MIReturn", CALL_LOCATION(errMsg)).GetValue_MIBoolean(CALL_LOCATION(errMsg)) );

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=, root, cm9vdA=="), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[1] );
    }

    void TestInvoke_DeleteCredentials_NoPort_Fails()
    {
        // Port is a required parameter - insure we fail if we don't pass it

        TestableContext context;
        mi::MySQL_Server_Class instanceName;
        mi::MySQL_Server_DeleteCredentials_Class param;
        mi::Module Module;
        mi::MySQL_Server_Class_Provider agent(&Module);
        agent.Invoke_DeleteCredentials(context, NULL, instanceName, param);

        std::wstring errMsg;
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, MI_RESULT_INVALID_PARAMETER, context.GetResult());
    }

    void TestInvoke_DeleteCredentials_WithPort_Succeeds()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"0=127.0.0.1, ,");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        TestableContext context;
        mi::MySQL_Server_Class instanceName;
        mi::MySQL_Server_DeleteCredentials_Class param;
        mi::Module Module;
        mi::MySQL_Server_Class_Provider agent(&Module);

        param.Port_value( 0 );
        agent.Invoke_DeleteCredentials(context, NULL, instanceName, param);

        std::wstring errMsg;
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, MI_RESULT_OK, context.GetResult());
        // We expect one instance to be returned with an MIReturn of success
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, 1u, context.Size());
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE,
             static_cast<bool>(true),
             context[0].GetProperty("MIReturn", CALL_LOCATION(errMsg)).GetValue_MIBoolean(CALL_LOCATION(errMsg)) );

        // Verify authentication file contents
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[0] );
    }

    void ValidateInstance(const TestableContext& context, std::wstring errMsg)
    {
        CPPUNIT_ASSERT_EQUAL(1u, context.Size());// This provider has only one instance (at least for test purposes)
        const TestableInstance &instance = context[0];

        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, m_keyNames[0], instance.GetKeyName(0, CALL_LOCATION(errMsg)));

        // Verify each of the key properties returned by the primary MySQL instance
        SCXCoreLib::NameResolver nr;
        CPPUNIT_ASSERT_EQUAL_MESSAGE(
            ERROR_MESSAGE,
            nr.GetHostname() + L":" + StrFromUTF8(sqlHostname) + L":" + StrFrom(sqlPort),
            context[0].GetKey(L"ProductIdentifyingNumber", CALL_LOCATION(errMsg)));

        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, std::wstring(L"MySQL"),
            context[0].GetKey(L"ProductName", CALL_LOCATION(errMsg)));

        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, std::wstring(L"Oracle"),
            context[0].GetKey(L"ProductVendor", CALL_LOCATION(errMsg)));

        CPPUNIT_ASSERT_EQUAL_MESSAGE(StrToUTF8(context[0].GetKey(L"ProductVersion", CALL_LOCATION(errMsg))),
            static_cast<size_t>(0),
            context[0].GetKey(L"ProductVersion", CALL_LOCATION(errMsg)).find(L"5."));

        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, std::wstring(s_sql_Server_id),
            context[0].GetKey(L"SystemID", CALL_LOCATION(errMsg)));

        // CollectionID is kinda "nasty" to validate - something like "redhat-linux-gnu", but hard to predict
        // Just verify that we can fetch it, and that it's not empty

        CPPUNIT_ASSERT_MESSAGE(StrToUTF8(context[0].GetKey(L"SystemID", CALL_LOCATION(errMsg))),
            !context[0].GetKey(L"SystemID", CALL_LOCATION(errMsg)).empty());

        std::wstring tmpExpectedProperties[] = {L"ProductIdentifyingNumber",
                                                L"ProductName",
                                                L"ProductVendor",
                                                L"ProductVersion",
                                                L"SystemID",
                                                L"CollectionID",
                                                L"ConfigurationFile",
                                                L"ErrorLogFile",
                                                L"Hostname",
                                                L"BindAddress",
                                                L"Port",
                                                L"SocketFile",
                                                L"DataDirectory",
                                                L"OperatingStatus"};

        const size_t numprops = sizeof(tmpExpectedProperties) / sizeof(tmpExpectedProperties[0]);
        VerifyInstancePropertyNames(instance, tmpExpectedProperties, numprops, CALL_LOCATION(errMsg));

        // Verify each of the non-key properties returned by the primary MySQL instance
        CPPUNIT_ASSERT_EQUAL(std::wstring(L"/etc/my.cnf"),
            instance.GetProperty(L"ConfigurationFile", CALL_LOCATION(errMsg)).GetValue_MIString(CALL_LOCATION(errMsg)));
        CPPUNIT_ASSERT_EQUAL(std::wstring(s_sql_log_error),
            instance.GetProperty(L"ErrorLogFile", CALL_LOCATION(errMsg)).GetValue_MIString(CALL_LOCATION(errMsg)));
        CPPUNIT_ASSERT_EQUAL(nr.GetHostname(),
            instance.GetProperty(L"Hostname", CALL_LOCATION(errMsg)).GetValue_MIString(CALL_LOCATION(errMsg)));
        CPPUNIT_ASSERT_EQUAL(std::wstring(StrFromUTF8(sqlHostname)),
            instance.GetProperty(L"BindAddress", CALL_LOCATION(errMsg)).GetValue_MIString(CALL_LOCATION(errMsg)));
        CPPUNIT_ASSERT_EQUAL(static_cast<MI_Uint16>(sqlPort),
            instance.GetProperty(L"Port", CALL_LOCATION(errMsg)).GetValue_MIUint16(CALL_LOCATION(errMsg)));
        CPPUNIT_ASSERT_EQUAL(std::wstring(L"/var/lib/mysql/mysql.sock"),
            instance.GetProperty(L"SocketFile", CALL_LOCATION(errMsg)).GetValue_MIString(CALL_LOCATION(errMsg)));
        CPPUNIT_ASSERT_EQUAL(std::wstring(L"/var/lib/mysql/"),
            instance.GetProperty(L"DataDirectory", CALL_LOCATION(errMsg)).GetValue_MIString(CALL_LOCATION(errMsg)));
        CPPUNIT_ASSERT_EQUAL(std::wstring(L"OK"),
            instance.GetProperty(L"OperatingStatus", CALL_LOCATION(errMsg)).GetValue_MIString(CALL_LOCATION(errMsg)));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MySQL_Server_Test );
