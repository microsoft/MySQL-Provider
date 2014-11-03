/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.

    Created date    2014-05-23 08:31:00

    MySQL_ServerStatistics_Class_Provider unit tests.

    Only tests the functionality of the provider class.

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/stringaid.h>
#include <testutils/scxunit.h>
#include <testutils/providertestutils.h>

#include "MySQL_ServerStatistics_Class_Provider.h"
#include "sqlbinding.h"

#include <iostream> // for cout


class MySQL_ServerStatistics_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( MySQL_ServerStatistics_Test );

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
        SetUpAgent<mi::MySQL_ServerStatistics_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

        m_keyNames.push_back(L"InstanceID");
    }

    void tearDown(void)
    {
        std::wstring errMsg;
        TestableContext context;
        TearDownAgent<mi::MySQL_ServerStatistics_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

        delete g_pFactory;
        g_pFactory = NULL;
    }

    void TestEnumerateInstancesKeysOnly()
    {
        std::wstring errMsg;
        TestableContext context;
        StandardTestEnumerateKeysOnly<mi::MySQL_ServerStatistics_Class_Provider>(
            m_keyNames, context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL(1u, context.Size());

        // Verify the InstanceID
        std::string instanceID;
        CPPUNIT_ASSERT_EQUAL(true, GetHostname(instanceID) );
        CPPUNIT_ASSERT_EQUAL(std::wstring(SCXCoreLib::StrFromUTF8(instanceID + ":3306")),
                             context[0].GetKey(L"InstanceID", CALL_LOCATION(errMsg)));
    }

    void TestEnumerateInstances()
    {
        std::wstring errMsg;
        TestableContext context;
        StandardTestEnumerateInstances<mi::MySQL_ServerStatistics_Class_Provider>(
            m_keyNames, context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL(1u, context.Size());
        ValidateInstance(context, CALL_LOCATION(errMsg));
    }

    void TestVerifyKeyCompletePartial()
    {
        std::wstring errMsg;
        StandardTestVerifyGetInstanceKeys<mi::MySQL_ServerStatistics_Class_Provider,
                mi::MySQL_ServerStatistics_Class>(m_keyNames, CALL_LOCATION(errMsg));
    }

    void TestGetInstance()
    {
        std::wstring errMsg;

        std::vector<std::wstring> keyValues;
        keyValues.push_back(L"Memory");
        TestableContext context;
        CPPUNIT_ASSERT_EQUAL(MI_RESULT_OK, (GetInstance<mi::MySQL_ServerStatistics_Class_Provider,
            mi::MySQL_ServerStatistics_Class>(m_keyNames, keyValues, context, CALL_LOCATION(errMsg))));
        ValidateInstance(context, CALL_LOCATION(errMsg));
    }

    void ValidateRatio(const TestableInstance& instance, const wchar_t *propertyName, std::wstring errMsg)
    {
        TestableInstance::PropertyInfo info;
        MI_Uint8 ratio;

        CPPUNIT_ASSERT_EQUAL(MI_RESULT_OK, instance.FindProperty(propertyName, info));
        ratio = info.GetValue_MIUint8(CALL_LOCATION(errMsg));
        SCXUNIT_ASSERT_BETWEEN(ratio, 0, 100);
    }

    void ValidateInstance(const TestableContext& context, std::wstring errMsg)
    {
        CPPUNIT_ASSERT_EQUAL(1u, context.Size());// This provider has only one instance.
        const TestableInstance &instance = context[0];

        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, m_keyNames[0], instance.GetKeyName(0, CALL_LOCATION(errMsg)));

        // Verify the InstanceID
        std::string instanceID;
        CPPUNIT_ASSERT_EQUAL(true, GetHostname(instanceID) );
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, std::wstring(SCXCoreLib::StrFromUTF8(instanceID + ":3306")),
                             instance.GetKeyValue(0, CALL_LOCATION(errMsg)));

        std::wstring tmpExpectedProperties[] = {L"InstanceID",
                                                L"NumConnections",
                                                L"MaxConnections",
                                                L"FailedConnections",
                                                L"Uptime",
                                                L"ServerDiskUseInBytes",
                                                L"SlowQueryPct",
                                                L"KeyCacheHitPct",
                                                L"KeyCacheWritePct",
                                                L"QCacheHitPct",
                                                L"QCachePrunesPct",
                                                L"TCacheHitPct",
                                                L"TableLockContentionPct",
                                                L"IDB_BP_HitPct",
                                                L"IDB_BP_UsePct",
                                                L"FullTableScanPct",
                                                L"SlaveStatus",
                                                L"SlaveLag"};

        const size_t numprops = sizeof(tmpExpectedProperties) / sizeof(tmpExpectedProperties[0]);
        VerifyInstancePropertyNames(instance, tmpExpectedProperties, numprops, CALL_LOCATION(errMsg));

        ValidateRatio(instance, L"SlowQueryPct", errMsg);
        ValidateRatio(instance, L"KeyCacheHitPct", errMsg);
        ValidateRatio(instance, L"KeyCacheWritePct", errMsg);
        ValidateRatio(instance, L"QCacheHitPct", errMsg);
        ValidateRatio(instance, L"QCachePrunesPct", errMsg);
        ValidateRatio(instance, L"TCacheHitPct", errMsg);
        ValidateRatio(instance, L"TableLockContentionPct", errMsg);
        ValidateRatio(instance, L"IDB_BP_HitPct", errMsg);
        ValidateRatio(instance, L"IDB_BP_UsePct", errMsg);
        ValidateRatio(instance, L"FullTableScanPct", errMsg);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MySQL_ServerStatistics_Test );
