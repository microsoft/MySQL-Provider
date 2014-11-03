/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.

    Created date    2014-05-23 08:31:00

    MySQL binding unit tests.

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/stringaid.h>
#include <testutils/scxunit.h>
#include <testutils/providertestutils.h>

#include <iostream> // for cout

#include "sqlbinding.h"
#include "sqlcredentials.h"

class Binding_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( Binding_Test );

    CPPUNIT_TEST( testAddValues );
    CPPUNIT_TEST( testSQL_Connect_No_Credentials );
    CPPUNIT_TEST( testSQL_Connect_With_Credentials );
    CPPUNIT_TEST( testSQL_Connect_With_Bad_Credentials );
    CPPUNIT_TEST( testSQLQuery_With_No_Attach );
    CPPUNIT_TEST( testSQLQuery_With_Bad_Credentials );
    CPPUNIT_TEST( testSQLQuery_With_Bad_Query );
    CPPUNIT_TEST( testSQLQuery_ShowGlobal_Status );
    CPPUNIT_TEST( testSQLQuery_ShowGlobal_Status_Handler_read );
    CPPUNIT_TEST( testSQLQuery_ShowGlobal_Status_With_Credentials );

    CPPUNIT_TEST_SUITE_END();

private:

public:
    void setUp(void)
    {
        g_pFactory = new MySQL_Factory();
    }

    void tearDown(void)
    {
        delete g_pFactory;
        g_pFactory = NULL;
    }

    void testAddValues()
    {
        std::map<std::string, std::string> mymap;

        mymap["random_1_text1"] = "1";
        mymap["random_1_text2"] = "2";
        mymap["random_1_text3"] = "3";
        mymap["random_1_text4"] = "4";
        mymap["random_1_text5"] = "5";
        mymap["random_2_text1"] = "10";
        mymap["random_2_text2"] = "20";
        mymap["random_2_text3"] = "30";
        mymap["random_2_text4"] = "40";
        mymap["random_2_text5"] = "50";

        int value;
        CPPUNIT_ASSERT_EQUAL( 0, AddValues(mymap, "random_3", value) );
        CPPUNIT_ASSERT_EQUAL( 0, value );

        CPPUNIT_ASSERT_EQUAL( 5, AddValues(mymap, "random_1", value) );
        CPPUNIT_ASSERT_EQUAL( 15, value );

        CPPUNIT_ASSERT_EQUAL( 5, AddValues(mymap, "random_2", value) );
        CPPUNIT_ASSERT_EQUAL( 150, value );

        CPPUNIT_ASSERT_EQUAL( 10, AddValues(mymap, "random_", value) );
        CPPUNIT_ASSERT_EQUAL( 165, value );
    }

    void testSQL_Connect_No_Credentials()
    {
        MySQL_Binding* pBinding = g_pFactory->GetBinding();
        CPPUNIT_ASSERT( pBinding->Attach() );
    }

    void testSQL_Connect_With_Credentials()
    {
        MySQL_Binding* pBinding = g_pFactory->GetBinding();
        CPPUNIT_ASSERT( pBinding->Attach(sqlHostname, sqlUsername, sqlPassword) );
    }

    void testSQL_Connect_With_Bad_Credentials()
    {
        MySQL_Binding* pBinding = g_pFactory->GetBinding();
        CPPUNIT_ASSERT( !pBinding->Attach(sqlHostname, sqlUsername, "BadPassword") );
    }

    void testSQLQuery_With_No_Attach()
    {
        //MySQL_Binding* pBinding = g_pFactory->GetBinding();
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        CPPUNIT_ASSERT( !pQuery->ExecuteQuery("show global status") );
        CPPUNIT_ASSERT_EQUAL(std::string("Attach() not called; not connected to a server"), pQuery->GetErrorText());
    }

    void testSQLQuery_With_Bad_Credentials()
    {
        MySQL_Binding* pBinding = g_pFactory->GetBinding();
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        CPPUNIT_ASSERT( !pBinding->Attach(sqlHostname, sqlUsername, "BadPassword") );
        CPPUNIT_ASSERT( !pQuery->ExecuteQuery("show global status") );
        CPPUNIT_ASSERT_EQUAL(std::string("MySQL server has gone away"), pQuery->GetErrorText());
    }

    void testSQLQuery_With_Bad_Query()
    {
        MySQL_Binding* pBinding = g_pFactory->GetBinding();
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        CPPUNIT_ASSERT( pBinding->Attach() );
        CPPUNIT_ASSERT( !pQuery->ExecuteQuery("this is a bogus MySQL query") );
        CPPUNIT_ASSERT_MESSAGE(std::string("Actual SQL Error message: \"") + pQuery->GetErrorText() + "\"",
                               std::string::npos != pQuery->GetErrorText().find("error in your SQL syntax"));
    }

    void testSQLQuery_ShowGlobal_Status()
    {
        MySQL_Binding* pBinding = g_pFactory->GetBinding();
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        CPPUNIT_ASSERT( pBinding->Attach() );
        CPPUNIT_ASSERT( pQuery->ExecuteQuery("show global status") );

        std::map<std::string, std::string> status = pQuery->GetResults();
        CPPUNIT_ASSERT( !status.empty() );

        // Determine how many entries we expect on the various platforms
        // If we run on an unknown platform, update the code below ...
        size_t expectedSize = 0;
        if ( 0 == pBinding->GetServerInfo().find("5.0.") )
            expectedSize = 222;  // MySQL 5.0 returns 222 entries from query "show global status"
        else if ( 0 == pBinding->GetServerInfo().find("5.1.") )
            expectedSize = 291;  // MySQL 5.1 returns 291 entries from query "show global status"

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Didn't receive expected number of entries from query \"show global status\"",
                                     expectedSize, status.size());
    }

    void testSQLQuery_ShowGlobal_Status_Handler_read()
    {
        MySQL_Binding* pBinding = g_pFactory->GetBinding();
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        CPPUNIT_ASSERT( pBinding->Attach() );
        CPPUNIT_ASSERT( pQuery->ExecuteQuery("show global status") );

        std::map<std::string, std::string> status = pQuery->GetResults();
        CPPUNIT_ASSERT( !status.empty() );

        // Verify that exactly 2 keys exist with handler_read_rnd_*; spec calls for that
        int value;
        CPPUNIT_ASSERT_EQUAL( 2, AddValues(status, "handler_read_rnd", value) );

        // Verify that exactly 6 keys exist with handler_read_*; spec calls for that
        CPPUNIT_ASSERT_EQUAL( 6, AddValues(status, "handler_read_", value) );
    }

    void testSQLQuery_ShowGlobal_Status_With_Credentials()
    {
        MySQL_Binding* pBinding = g_pFactory->GetBinding();
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        CPPUNIT_ASSERT( pBinding->Attach(sqlHostname, sqlUsername, sqlPassword) );
        CPPUNIT_ASSERT( pQuery->ExecuteQuery("show global status") );

        std::map<std::string, std::string> status = pQuery->GetResults();
        CPPUNIT_ASSERT( !status.empty() );
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( Binding_Test );
