/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.

    Created date    2014-11-11 13:47:00

    MySQL_Server_Database_Class_Provider unit tests.

    Only tests the functionality of the provider class.

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/scxnameresolver.h>
#include <scxcorelib/stringaid.h>
#include <testutils/scxunit.h>
#include <testutils/providertestutils.h>

#include "MySQL_Server_Database_Class_Provider.h"
#include "sqlbinding.h"
#include "sqlcredentials.h"
#include "testablefactory.h"

#include <iostream> // for cout


using namespace SCXCoreLib;

class MySQL_Server_Database_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( MySQL_Server_Database_Test );

    CPPUNIT_TEST( TestEnumerateInstancesKeysOnly );
    CPPUNIT_TEST( TestEnumerateInstances );
    CPPUNIT_TEST( TestVerifyKeyCompletePartial );
    CPPUNIT_TEST( TestGetInstance );
    CPPUNIT_TEST( TestGetInstanceWithNonexistentDatabase );

    SCXUNIT_TEST_ATTRIBUTE(TestEnumerateInstancesKeysOnly, SLOW);
    SCXUNIT_TEST_ATTRIBUTE(TestEnumerateInstances, SLOW);
    SCXUNIT_TEST_ATTRIBUTE(TestVerifyKeyCompletePartial, SLOW);
    SCXUNIT_TEST_ATTRIBUTE(TestGetInstance, SLOW);
    SCXUNIT_TEST_ATTRIBUTE( TestGetInstanceWithNonexistentDatabase, SLOW );
    CPPUNIT_TEST_SUITE_END();

private:
    std::vector<std::wstring> m_keyNames;

public:
    void setUp(void)
    {
        if ( NULL != g_pFactory )
        {
            delete g_pFactory;
            g_pFactory = NULL;
        }
        g_pFactory = new MySQL_TestableFactory();

        std::wstring errMsg;
        TestableContext context;
        SetUpAgent<mi::MySQL_Server_Database_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

        // We'll fail if we don't have a valid authentication rule
        SCXHandle<MySQL_Binding> pBinding = g_pFactory->GetBinding();
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        CPPUNIT_ASSERT_NO_THROW( pAuth->AddCredentialSet(sqlPort, sqlHostname, sqlUsername, sqlPassword) );
        CPPUNIT_ASSERT_NO_THROW( pAuth->Save() );

        m_keyNames.push_back(L"InstanceID");
    }

    void tearDown(void)
    {
        // Delete the authentication file
        SCXFile::Delete( s_authFilePath );

        std::wstring errMsg;
        TestableContext context;
        TearDownAgent<mi::MySQL_Server_Database_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

        delete g_pFactory;
        g_pFactory = NULL;
    }

    void TestEnumerateInstancesKeysOnly()
    {
        std::wstring errMsg;
        TestableContext context;
        StandardTestEnumerateKeysOnly<mi::MySQL_Server_Database_Class_Provider>(
            m_keyNames, context, CALL_LOCATION(errMsg));

        CPPUNIT_ASSERT_MESSAGE(StrToUTF8(StrAppend(L"Number of databases returned: ", context.Size())), context.Size() >= 3);

        for (size_t i = 0; i < context.Size(); ++i)
        {
            const TestableInstance &instance = context[i];

            // Verify the InstanceID
            NameResolver nr;
            std::wstring instPrefix = nr.GetHostname() + L":" + StrFromUTF8(sqlHostname) + L":" + StrFrom(sqlPort) + L":";
            size_t instMinSize = instPrefix.size();
            CPPUNIT_ASSERT_EQUAL(instPrefix, instance.GetKey(L"InstanceID", CALL_LOCATION(errMsg)).substr(0,instMinSize));
        }
    }

    void TestEnumerateInstances()
    {
        std::wstring errMsg;
        TestableContext context;
        StandardTestEnumerateInstances<mi::MySQL_Server_Database_Class_Provider>(
            m_keyNames, context, CALL_LOCATION(errMsg));

        ValidateInstance(context, CALL_LOCATION(errMsg));
    }

    void TestVerifyKeyCompletePartial()
    {
        std::wstring errMsg;
        StandardTestVerifyGetInstanceKeys<mi::MySQL_Server_Database_Class_Provider,
                mi::MySQL_Server_Database_Class>(m_keyNames, CALL_LOCATION(errMsg));
    }

    void TestGetInstance()
    {
        std::wstring errMsg;

        NameResolver nr;
        std::vector<std::wstring> keyValues;
        // Pick a known database that must always exist in a MySQL Server installation (mysql)
        keyValues.push_back( nr.GetHostname() + L":" + StrFromUTF8(sqlHostname) + L":" + StrFrom(sqlPort) + L":mysql" );

        TestableContext context;
        CPPUNIT_ASSERT_EQUAL(MI_RESULT_OK, (GetInstance<mi::MySQL_Server_Database_Class_Provider,
            mi::MySQL_Server_Database_Class>(m_keyNames, keyValues, context, CALL_LOCATION(errMsg))));
        ValidateInstance(context, CALL_LOCATION(errMsg), true);
    }

    void TestGetInstanceWithNonexistentDatabase()
    {
        std::wstring errMsg;

        NameResolver nr;
        std::vector<std::wstring> keyValues;
        // Pick a database that does not exist ("invalid", in this case)
        keyValues.push_back( nr.GetHostname() + L":" + StrFromUTF8(sqlHostname) + L":" + StrFrom(sqlPort) + L":invalid" );

        TestableContext context;
        CPPUNIT_ASSERT_EQUAL(MI_RESULT_NOT_FOUND, (GetInstance<mi::MySQL_Server_Database_Class_Provider,
            mi::MySQL_Server_Database_Class>(m_keyNames, keyValues, context, CALL_LOCATION(errMsg))));
    }

    void ValidateInstance(const TestableContext& context, std::wstring errMsg, bool fGetInstance = false)
    {
        // GetInstance will always return a single reset set; otherwise we get
        // at least 3 from default installation (information_schema, mysql, test)
        CPPUNIT_ASSERT_MESSAGE(
            StrToUTF8(StrAppend(L"Number of databases returned: ", context.Size())),
            ( fGetInstance ? 1 : context.Size() >= 3));

        for (size_t i = 0; i < context.Size(); ++i)
        {
            const TestableInstance &instance = context[i];

            CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, m_keyNames[0], instance.GetKeyName(0, CALL_LOCATION(errMsg)));

            // Verify the InstanceID
            NameResolver nr;
            std::wstring instPrefix = nr.GetHostname() + L":" + StrFromUTF8(sqlHostname) + L":" + StrFrom(sqlPort) + L":";
            size_t instMinSize = instPrefix.size();
            CPPUNIT_ASSERT_EQUAL(instPrefix, instance.GetKey(L"InstanceID", CALL_LOCATION(errMsg)).substr(0,instMinSize));

            std::wstring tmpExpectedProperties[] = {L"InstanceID",
                                                    L"DatabaseName",
                                                    L"NumberOfTables",
                                                    L"DiskSpaceInBytes"};

            const size_t numprops = sizeof(tmpExpectedProperties) / sizeof(tmpExpectedProperties[0]);
            VerifyInstancePropertyNames(instance, tmpExpectedProperties, numprops, CALL_LOCATION(errMsg));

            // Verify DiskSpaceInBytes
            MI_Uint64 tables = instance.GetProperty(L"NumberOfTables", CALL_LOCATION(errMsg)).GetValue_MIUint64(CALL_LOCATION(errMsg));
            MI_Uint64 dbsize = instance.GetProperty(L"DiskSpaceInBytes", CALL_LOCATION(errMsg)).GetValue_MIUint64(CALL_LOCATION(errMsg));
            std::stringstream ss;
            ss << "Disk space (in bytes) " << dbsize << " for database " << StrToUTF8(instance.GetProperty(L"DatabaseName", CALL_LOCATION(errMsg)).GetValue_MIString(CALL_LOCATION(errMsg)));
            CPPUNIT_ASSERT_MESSAGE(ss.str(), (tables == 0 && dbsize == 0) || (tables >= 1 && dbsize >= 1024));
        }
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MySQL_Server_Database_Test );
