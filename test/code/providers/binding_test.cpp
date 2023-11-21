/*
 * --------------------------------- START OF LICENSE ----------------------------
 *
 * MySQL cimprov ver. 1.0
 *
 * Copyright (c) Microsoft Corporation
 *
 * All rights reserved. 
 *
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the ""Software""), to deal
 * in the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED *AS IS*, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * ---------------------------------- END OF LICENSE -----------------------------
*/
/*--------------------------------------------------------------------------------

    Created date    2014-05-23 08:31:00

    MySQL binding unit tests.

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/stringaid.h>
#include <testutils/scxunit.h>
#include <testutils/providertestutils.h>

#include "errmsg.h"
#include "mysqld_error.h"

#include <iostream> // for cout

#include "sqlauth.h"
#include "sqlbinding.h"
#include "sqlcredentials.h"

class Binding_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( Binding_Test );

    CPPUNIT_TEST( testAddValues );
    CPPUNIT_TEST( testSQL_Binding_Construction );
    CPPUNIT_TEST( testSQL_Connect_No_Credentials );
    CPPUNIT_TEST( testSQL_Connect_With_Credentials );
    CPPUNIT_TEST( testSQL_Connect_With_Bad_Credentials );
    CPPUNIT_TEST( testSQL_Connect_Will_Reuse_Connection );
    CPPUNIT_TEST( testSQL_Connect_With_Stored_Credentials );
    CPPUNIT_TEST( testSQL_Binding_Destruction_When_Disconnected );
    CPPUNIT_TEST( testSQL_Stored_Credentials_Fails_With_Bad_Port );
    CPPUNIT_TEST( testSQL_Connect_With_ExistingDatabase_Succeeds );
    CPPUNIT_TEST( testSQL_Connect_With_BadDatabase_Fails );
    CPPUNIT_TEST( testSQL_GetConfigurationFilePaths );
    CPPUNIT_TEST( testSQLQuery_With_No_Attach );
    CPPUNIT_TEST( testSQLQuery_With_Bad_Credentials );
    CPPUNIT_TEST( testSQLQuery_With_Bad_Query );
    CPPUNIT_TEST( testSQLQuery_ShowGlobal_Status );
    CPPUNIT_TEST( testSQLQuery_ShowGlobal_Status_Handler_read );
    CPPUNIT_TEST( testSQLQuery_ShowGlobal_Status_With_Credentials );
    CPPUNIT_TEST( testSQLQuery_With_Multiple_Columns );
    CPPUNIT_TEST( testSQLQuery_With_Multiple_SQL_Statements_Fails );
    CPPUNIT_TEST( testSQLQuery_Fetching_Column_Names );
    CPPUNIT_TEST( testSQLAuthentication_Construction );

    CPPUNIT_TEST_SUITE_END();

private:

public:
    void setUp(void)
    {
        g_pFactory = NULL;
        g_pFactory = new MySQL_Factory();
    }

    void tearDown(void)
    {
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

    void testSQL_Binding_Construction()
    {
        // Test testSQL_Binding_Destructed_When_Explicitly_Disconnected() will
        // verify proper handling after using the binding object. This verifies
        // proper destruction if we don't do anything at all with it.

        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
    }

    void testSQL_Connect_No_Credentials()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        bool fSuccess = pBinding->Attach();
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
    }

    void testSQL_Connect_With_Credentials()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        bool fSuccess = pBinding->Attach(sqlPort, sqlHostname, sqlUsername, sqlPassword);
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
    }

    void testSQL_Connect_With_Bad_Credentials()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        bool fSuccess = pBinding->Attach(sqlPort, sqlHostname, sqlUsername, "BadPassword");
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), !fSuccess );

        // Verify error functions
        CPPUNIT_ASSERT_MESSAGE(std::string("Actual SQL Error message: \"") + pBinding->GetErrorText() + "\"",
                               0 == pBinding->GetErrorText().find("Access denied for user"));
        CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(ER_ACCESS_DENIED_ERROR), pBinding->GetErrorNum());
        CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(1045), pBinding->GetErrorNum());
        CPPUNIT_ASSERT_EQUAL(std::string("28000"), pBinding->GetErrorState());
    }

    void testSQL_Connect_Will_Reuse_Connection()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        bool fSuccess = pBinding->Attach(sqlPort, sqlHostname, sqlUsername, sqlPassword);
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
        fSuccess = pBinding->Detach();
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );

        fSuccess = pBinding->Attach(sqlPort, sqlHostname, sqlUsername, sqlPassword);
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
    }

    void testSQL_Connect_With_Stored_Credentials()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        CPPUNIT_ASSERT_NO_THROW( pAuth->AddCredentialSet(sqlPort, sqlHostname, sqlUsername, sqlPassword) );

        bool fSuccess = pBinding->AttachUsingStoredCredentials(sqlPort, pAuth);
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
    }

    void testSQL_Binding_Destruction_When_Disconnected()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        bool fSuccess = pBinding->Attach(sqlPort, sqlHostname, sqlUsername, sqlPassword);
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
        fSuccess = pBinding->Detach();
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
    }

    void testSQL_Stored_Credentials_Fails_With_Bad_Port()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        CPPUNIT_ASSERT_NO_THROW( pAuth->AddCredentialSet(8306, sqlHostname, sqlUsername, sqlPassword) );

        bool fSuccess = pBinding->AttachUsingStoredCredentials(8306, pAuth);
        CPPUNIT_ASSERT_MESSAGE( "Database connection succeeded when failure was expected", !fSuccess );
        CPPUNIT_ASSERT_EQUAL_MESSAGE( pBinding->GetErrorText(), static_cast<size_t>(0),
                                      pBinding->GetErrorText().find("Can't connect to MySQL server on") );
        CPPUNIT_ASSERT_EQUAL( static_cast<unsigned int>(2003), pBinding->GetErrorNum() );
    }

    void testSQL_Connect_With_ExistingDatabase_Succeeds()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        CPPUNIT_ASSERT_NO_THROW( pAuth->AddCredentialSet(sqlPort, sqlHostname, sqlUsername, sqlPassword) );

        // The "mysql" database should always be installed (part of base MySQL installation)
        CPPUNIT_ASSERT( pBinding->AttachUsingStoredCredentials(sqlPort, pAuth, "mysql") );
        CPPUNIT_ASSERT_EQUAL_MESSAGE( pBinding->GetErrorText(), static_cast<size_t>(0),  pBinding->GetErrorText().size() );
        CPPUNIT_ASSERT_EQUAL( static_cast<unsigned int>(0), pBinding->GetErrorNum() );
    }

    void testSQL_Connect_With_BadDatabase_Fails()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        CPPUNIT_ASSERT_NO_THROW( pAuth->AddCredentialSet(sqlPort, sqlHostname, sqlUsername, sqlPassword) );

        bool fSuccess = pBinding->AttachUsingStoredCredentials(sqlPort, pAuth, "NoSuchDatabase");
        CPPUNIT_ASSERT_MESSAGE( "Database connection succeeded when failure was expected", !fSuccess );
        CPPUNIT_ASSERT_EQUAL_MESSAGE( pBinding->GetErrorText(), static_cast<size_t>(0),
                                      pBinding->GetErrorText().find("Unknown database") );
        CPPUNIT_ASSERT_EQUAL( static_cast<unsigned int>(ER_BAD_DB_ERROR), pBinding->GetErrorNum() );
    }

    void testSQL_GetConfigurationFilePaths()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        std::vector<std::string> paths;
        pBinding->GetConfigurationFilePaths( paths );

        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(6), paths.size() );
        CPPUNIT_ASSERT_EQUAL( std::string("/etc/my.cnf"), paths[0] );
        CPPUNIT_ASSERT_EQUAL( std::string("/etc/mysql/my.cnf"), paths[1] );
        CPPUNIT_ASSERT_EQUAL( std::string("/var/lib/mysql/my.cnf"), paths[2] );
        CPPUNIT_ASSERT_EQUAL( std::string("/usr/local/mysql/data/my.cnf"), paths[3] );
        CPPUNIT_ASSERT_EQUAL( std::string("/usr/local/var/my.cnf"), paths[4] );
        CPPUNIT_ASSERT_EQUAL( std::string("/usr/my.cnf"), paths[5] );
    }

    void testSQLQuery_With_No_Attach()
    {
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        CPPUNIT_ASSERT( !pQuery->ExecuteQuery("show global status") );
        CPPUNIT_ASSERT_EQUAL(std::string("Attach() not called; not connected to a server"), pQuery->GetErrorText());
    }

    void testSQLQuery_With_Bad_Credentials()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        bool fSuccess = pBinding->Attach(sqlPort, sqlHostname, sqlUsername, "BadPassword");
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), !fSuccess );

        // Verify error functions
        CPPUNIT_ASSERT_MESSAGE(std::string("Actual SQL Error message: \"") + pBinding->GetErrorText() + "\"",
                               0 == pBinding->GetErrorText().find("Access denied for user"));
        CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(ER_ACCESS_DENIED_ERROR), pBinding->GetErrorNum());
        CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(1045), pBinding->GetErrorNum());
        CPPUNIT_ASSERT_EQUAL(std::string("28000"), pBinding->GetErrorState());

        // We didn't attach, but do the query anyway and make sure we get what we anticipated
        CPPUNIT_ASSERT( !pQuery->ExecuteQuery("show global status") );
        CPPUNIT_ASSERT_EQUAL(std::string("MySQL server has gone away"), pQuery->GetErrorText());
        CPPUNIT_ASSERT_EQUAL(static_cast<unsigned int>(CR_SERVER_GONE_ERROR), pQuery->GetErrorNum());
        CPPUNIT_ASSERT_EQUAL(std::string("HY000"), pQuery->GetErrorState());
    }

    void testSQLQuery_With_Bad_Query()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        bool fSuccess = pBinding->Attach();
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
        CPPUNIT_ASSERT( !pQuery->ExecuteQuery("this is a bogus MySQL query") );
        CPPUNIT_ASSERT_MESSAGE(std::string("Actual SQL Error message: \"") + pQuery->GetErrorText() + "\"",
                               std::string::npos != pQuery->GetErrorText().find("error in your SQL syntax"));
    }

    void testSQLQuery_ShowGlobal_Status()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        std::map<std::string, std::string> status;
        bool fSuccess = pBinding->Attach();
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
        CPPUNIT_ASSERT( pQuery->ExecuteQuery("show global status") && pQuery->GetResults(status) );
        CPPUNIT_ASSERT( !status.empty() );

        // Determine how many entries we expect on the various platforms
        // If we run on an unknown platform, update the code below ...
        size_t expectedSize = 0;
        if ( 0 == pBinding->GetServerInfo().find("5.0.") )
            expectedSize = 224;  // build node MySQL 5.0.33 returns 224 entries from query "show global status"
        else if ( 0 == pBinding->GetServerInfo().find("5.1.") )
            expectedSize = 291;  // MySQL 5.1 returns 291 entries from query "show global status"

        CPPUNIT_ASSERT_EQUAL_MESSAGE("Didn't receive expected number of entries from query \"show global status\"",
                                     expectedSize, status.size());
    }

    void testSQLQuery_ShowGlobal_Status_Handler_read()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        std::map<std::string, std::string> status;
        bool fSuccess = pBinding->Attach();
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
        CPPUNIT_ASSERT( pQuery->ExecuteQuery("show global status") && pQuery->GetResults(status) );
        CPPUNIT_ASSERT( !status.empty() );

        // Verify that exactly 2 keys exist with handler_read_rnd_*; spec calls for that
        int value;
        CPPUNIT_ASSERT_EQUAL( 2, AddValues(status, "handler_read_rnd", value) );

        // Verify that exactly 6 keys exist with handler_read_*; spec calls for that
        CPPUNIT_ASSERT_EQUAL( 6, AddValues(status, "handler_read_", value) );
    }

    void testSQLQuery_ShowGlobal_Status_With_Credentials()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        std::map<std::string, std::string> status;
        bool fSuccess = pBinding->Attach(sqlPort, sqlHostname, sqlUsername, sqlPassword);
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
        CPPUNIT_ASSERT( pQuery->ExecuteQuery("show global status") && pQuery->GetResults(status) );
        CPPUNIT_ASSERT( !status.empty() );
    }

    void testSQLQuery_With_Multiple_Columns()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        MySQL_QueryResults resultSet;
        bool fSuccess = pBinding->Attach(sqlPort, sqlHostname, sqlUsername, sqlPassword);
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
        fSuccess = pQuery->ExecuteQuery("select \"c1\" as \"Column 1\", \"c2\" as \"Column 2\", \"c3\" as \"Column 3\"");
        CPPUNIT_ASSERT_MESSAGE( pQuery->GetErrorText(), fSuccess );
        fSuccess = pQuery->GetMultiColumnResults(resultSet);
        CPPUNIT_ASSERT_MESSAGE( pQuery->GetErrorText(), fSuccess );

        // Verify the result set
        CPPUNIT_ASSERT( resultSet.size() == 1 );
        CPPUNIT_ASSERT( resultSet.count("c1") > 0 );

        std::vector<std::string> contents = resultSet["c1"];
        CPPUNIT_ASSERT( contents.size() == 2);
        CPPUNIT_ASSERT_EQUAL( std::string("c2"), contents[0] );
        CPPUNIT_ASSERT_EQUAL( std::string("c3"), contents[1] );
    }

    void testSQLQuery_With_Multiple_SQL_Statements_Fails()
    {
        // SQL injection bugs can result if multiple SQL statements are allowed
        // to be executed as part of a single query.
        //
        // The query code was reworked to use MySQL Prepared Statements, which
        // eliminates the possibility of SQL injection bugs. Verify that multiple
        // SQL statements aren't allowed.

        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        MySQL_QueryResults resultSet;
        bool fSuccess = pBinding->Attach(sqlPort, sqlHostname, sqlUsername, sqlPassword);
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );

        const char *sqlQuery = "select 1 as 'Result 1, Column 1', 2 as 'Result 1, Column 2'; "
                               "select 3 as 'Result 2, Column 1', 4 as 'Result 2, Column 2';";

        fSuccess = pQuery->ExecuteQuery(sqlQuery);
        std::string sqlError = pQuery->GetErrorText();
        CPPUNIT_ASSERT_MESSAGE( sqlError, ! fSuccess );
        CPPUNIT_ASSERT_MESSAGE( sqlError, sqlError.find("You have an error in your SQL syntax") != std::string::npos ); 
    }

    void testSQLQuery_Fetching_Column_Names()
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Query> pQuery(g_pFactory->GetQuery());

        MySQL_QueryResults resultSet;
        bool fSuccess = pBinding->Attach(sqlPort, sqlHostname, sqlUsername, sqlPassword);
        CPPUNIT_ASSERT_MESSAGE( pBinding->GetErrorText(), fSuccess );
        fSuccess = pQuery->ExecuteQuery("select \"c1\" as \"Column 1\", \"c2\" as \"Column 2\", \"c3\" as \"Column 3\"");
        CPPUNIT_ASSERT_MESSAGE( pQuery->GetErrorText(), fSuccess );
        fSuccess = pQuery->GetMultiColumnResults(resultSet);
        CPPUNIT_ASSERT_MESSAGE( pQuery->GetErrorText(), fSuccess );

        // Verify the result set
        CPPUNIT_ASSERT( resultSet.size() == 1 );
        CPPUNIT_ASSERT( resultSet.count("c1") > 0 );

        std::vector<std::string> contents = resultSet["c1"];
        CPPUNIT_ASSERT( contents.size() == 2);
        CPPUNIT_ASSERT_EQUAL( std::string("c2"), contents[0] );
        CPPUNIT_ASSERT_EQUAL( std::string("c3"), contents[1] );

        std::vector<std::string> columnNames = pQuery->GetColumnNames();
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(3), columnNames.size() );
        CPPUNIT_ASSERT_EQUAL( std::string("Column 1"), columnNames[0] );
        CPPUNIT_ASSERT_EQUAL( std::string("Column 2"), columnNames[1] );
        CPPUNIT_ASSERT_EQUAL( std::string("Column 3"), columnNames[2] );
    }

    void testSQLAuthentication_Construction()
    {
        // The MySQL_Authentication has a very rich set of unit tests
        // But make sure we can construct/use from binding (for test purposes)

        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
    }

};

CPPUNIT_TEST_SUITE_REGISTRATION( Binding_Test );
