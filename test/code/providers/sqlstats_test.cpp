/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.

    Created date    2014-05-23 08:31:00

    MySQL_ServerStatistics_Class_Provider unit tests.

    Only tests the functionality of the provider class.

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxfile.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/scxnameresolver.h>
#include <scxcorelib/stringaid.h>
#include <testutils/scxunit.h>
#include <testutils/providertestutils.h>

#include "MySQL_ServerStatistics_Class_Provider.h"
#include "sqlbinding.h"
#include "sqlcredentials.h"
#include "testablefactory.h"

#include <iostream> // for cout


using namespace SCXCoreLib;

class MySQL_ServerStatistics_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( MySQL_ServerStatistics_Test );

    CPPUNIT_TEST( TestEnumerateInstancesKeysOnly );
    CPPUNIT_TEST( TestEnumerateInstances );
    CPPUNIT_TEST( TestVerifyKeyCompletePartial );
    CPPUNIT_TEST( TestGetInstance );

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

        std::wstring errMsg;
        TestableContext context;
        SetUpAgent<mi::MySQL_ServerStatistics_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

        // We'll fail if we don't have a valid authentication rule
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
        TearDownAgent<mi::MySQL_ServerStatistics_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

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
        NameResolver nr;
        CPPUNIT_ASSERT_EQUAL(nr.GetHostname() + L":" + StrFromUTF8(sqlHostname) + L":" + StrFrom(sqlPort),
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

        NameResolver nr;
        std::vector<std::wstring> keyValues;
        keyValues.push_back( nr.GetHostname() + L":" + StrFromUTF8(sqlHostname) + L":" + StrFrom(sqlPort) );

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
        CPPUNIT_ASSERT( ratio <= 100 );
    }

    void ValidateInstance(const TestableContext& context, std::wstring errMsg)
    {
        CPPUNIT_ASSERT_EQUAL(1u, context.Size());// This provider has only one instance.
        const TestableInstance &instance = context[0];

        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, m_keyNames[0], instance.GetKeyName(0, CALL_LOCATION(errMsg)));

        // Verify the InstanceID
        NameResolver nr;
        CPPUNIT_ASSERT_EQUAL_MESSAGE(
            ERROR_MESSAGE,
            nr.GetHostname() + L":" + StrFromUTF8(sqlHostname) + L":" + StrFrom(sqlPort),
            instance.GetKeyValue(0, CALL_LOCATION(errMsg)));

        std::wstring tmpExpectedProperties[] = {L"InstanceID",
                                                L"CurrentNumConnections",
                                                L"MaxConnections",
                                                L"FailedConnections",
                                                L"Uptime",
                                                L"ServerDiskUseInBytes",
                                                L"ConnectionsUsePct",
                                                L"SlowQueryPct",
                                                L"KeyCacheHitPct",
                                                L"KeyCacheWritePct",
                                                L"QCacheHitPct",
                                                L"QCachePrunesPct",
                                                L"TCacheHitPct",
                                                L"TableLockContentionPct",
                                                L"IDB_BP_HitPct",
                                                L"IDB_BP_UsePct",
                                                L"FullTableScanPct"};

        const size_t numprops = sizeof(tmpExpectedProperties) / sizeof(tmpExpectedProperties[0]);
        VerifyInstancePropertyNames(instance, tmpExpectedProperties, numprops, CALL_LOCATION(errMsg));

        // Due to built in schema, minimim disk used appears to be 650155
        uint64_t diskUsed = instance.GetProperty(L"ServerDiskUseInBytes", CALL_LOCATION(errMsg)).GetValue_MIUint64(CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_MESSAGE(StrToUTF8(StrAppend(L"Disk space used: ", diskUsed)), diskUsed > 430000);

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
