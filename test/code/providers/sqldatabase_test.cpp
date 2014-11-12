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

#include <iostream> // for cout


class MySQL_Server_Database_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( MySQL_Server_Database_Test );

    CPPUNIT_TEST( TestEnumerateInstancesKeysOnly );
    CPPUNIT_TEST( TestEnumerateInstances );
    // *TODO* Implement GetInstance, then uncomment these tests
    //CPPUNIT_TEST( TestVerifyKeyCompletePartial );
    //CPPUNIT_TEST( TestGetInstance );

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
        if ( NULL != g_pFactory )
        {
            delete g_pFactory;
            g_pFactory = NULL;
        }
        g_pFactory = new MySQL_Factory();

        std::wstring errMsg;
        TestableContext context;
        SetUpAgent<mi::MySQL_Server_Database_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

        m_keyNames.push_back(L"InstanceID");
    }

    void tearDown(void)
    {
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
        CPPUNIT_ASSERT_MESSAGE(SCXCoreLib::StrToUTF8(SCXCoreLib::StrAppend(L"Number of databases returned: ", context.Size())), context.Size() > 1);

        // Verify the InstanceID
        SCXCoreLib::NameResolver nr;
        size_t instanceMinSize = nr.GetHostname().size() + 6; /* ":3306:" */
        CPPUNIT_ASSERT_EQUAL(nr.GetHostname() + L":3306:", context[0].GetKey(L"InstanceID", CALL_LOCATION(errMsg)).substr(0,instanceMinSize));
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

        std::vector<std::wstring> keyValues;
        keyValues.push_back(L"Memory");
        TestableContext context;
        CPPUNIT_ASSERT_EQUAL(MI_RESULT_OK, (GetInstance<mi::MySQL_Server_Database_Class_Provider,
            mi::MySQL_Server_Database_Class>(m_keyNames, keyValues, context, CALL_LOCATION(errMsg))));
        ValidateInstance(context, CALL_LOCATION(errMsg));
    }

    void ValidateInstance(const TestableContext& context, std::wstring errMsg)
    {
        CPPUNIT_ASSERT_MESSAGE(SCXCoreLib::StrToUTF8(SCXCoreLib::StrAppend(L"Number of databases returned: ", context.Size())), context.Size() > 1);

        for (size_t i = 0; i < context.Size(); ++i)
        {
            const TestableInstance &instance = context[i];

            CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, m_keyNames[0], instance.GetKeyName(0, CALL_LOCATION(errMsg)));

            // Verify the InstanceID
            SCXCoreLib::NameResolver nr;
            size_t instanceMinSize = nr.GetHostname().size() + 6; /* ":3306:" */
            CPPUNIT_ASSERT_EQUAL(nr.GetHostname() + L":3306:", context[0].GetKey(L"InstanceID", CALL_LOCATION(errMsg)).substr(0,instanceMinSize));

            std::wstring tmpExpectedProperties[] = {L"InstanceID",
                                                    L"DatabaseName",
                                                    L"NumberOfTables",
                                                    L"DiskSpaceInBytes"};

            const size_t numprops = sizeof(tmpExpectedProperties) / sizeof(tmpExpectedProperties[0]);
            VerifyInstancePropertyNames(instance, tmpExpectedProperties, numprops, CALL_LOCATION(errMsg));

            // Verify DiskSpaceInBytes
            TestableInstance::PropertyInfo info;
            MI_Uint64 dbsize;

            CPPUNIT_ASSERT_EQUAL(MI_RESULT_OK, instance.FindProperty("DiskSpaceInBytes", info));
            dbsize = info.GetValue_MIUint64(CALL_LOCATION(errMsg));
            CPPUNIT_ASSERT_MESSAGE(SCXCoreLib::StrToUTF8(SCXCoreLib::StrAppend(L"DiskSpaceInBytes: ", dbsize)), dbsize == 0);
        }
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MySQL_Server_Database_Test );
