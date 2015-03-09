/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.

    Created date    2014-11-11 13:47:00

    MySQL_StoredProcedureRow_AsXML_Class_Provider unit tests.

    Only tests the functionality of the provider class.

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/scxnameresolver.h>
#include <scxcorelib/stringaid.h>
#include <testutils/scxunit.h>
#include <testutils/providertestutils.h>

#include "MySQL_StoredProcedureRow_AsXML_Class_Provider.h"
#include "sqlbinding.h"
#include "sqlcredentials.h"
#include "testablefactory.h"

#include <iostream> // for cout


using namespace std;
using namespace SCXCoreLib;

// Definitions of methods in MySQL_StoredProcedureRow_AsXML_Class_Provider.cpp

bool GetValueForKey(string& value, const string& query, const string& key);
string QuoteXMLString(string text);


class MySQL_Stored_Procedure_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( MySQL_Stored_Procedure_Test );

    CPPUNIT_TEST( TestEnumerateWithNoQueryFails_KeysOnly );
    CPPUNIT_TEST( TestEnumerateWithNoQueryFails_AllProps );
    CPPUNIT_TEST( TestEnumerateInstancesKeysOnly );
    CPPUNIT_TEST( TestEnumerateInstances );
    CPPUNIT_TEST( TestVerifyKeyCompletePartialFails );
    CPPUNIT_TEST( TestGetInstanceFails );
    CPPUNIT_TEST( TestGetValueForKey_KeyExists );
    CPPUNIT_TEST( TestGetValueForKey_KeyNotFound );
    CPPUNIT_TEST( TestGetValueForKey_MultipleKeysFound );
    CPPUNIT_TEST( TestGetValueForKey_QuotedParameters );
    CPPUNIT_TEST( TestGetValueForKey_LongQuotedParameters );
    CPPUNIT_TEST( TestQuoteXML_EmptyString );
    CPPUNIT_TEST( TestQuoteXML_UnremarkableChars );
    CPPUNIT_TEST( TestQuoteXML_DoubleQuote );
    CPPUNIT_TEST( TestQuoteXML_Apostrophe );
    CPPUNIT_TEST( TestQuoteXML_LessThan );
    CPPUNIT_TEST( TestQuoteXML_GreaterThan );
    CPPUNIT_TEST( TestQuoteXML_EmbeddedQuotableBytes );
    CPPUNIT_TEST( TestCompleteParameterParsing );

    SCXUNIT_TEST_ATTRIBUTE(TestEnumerateInstancesKeysOnly, SLOW);
    SCXUNIT_TEST_ATTRIBUTE(TestEnumerateInstances, SLOW);
    SCXUNIT_TEST_ATTRIBUTE(TestVerifyKeyCompletePartialFails, SLOW);
    SCXUNIT_TEST_ATTRIBUTE(TestGetInstanceFails, SLOW);
    SCXUNIT_TEST_ATTRIBUTE(TestGetInstanceWithNonexistentDatabase, SLOW);
    CPPUNIT_TEST_SUITE_END();

private:
    std::vector<std::wstring> m_keyNames;

public:
    void setUp(void)
    {
        g_pFactory = NULL;
        g_pFactory = new MySQL_TestableFactory();

        std::wstring errMsg;
        TestableContext context;
        SetUpAgent<mi::MySQL_StoredProcedureRow_AsXML_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

        // We'll fail if we don't have a valid authentication rule
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();
        CPPUNIT_ASSERT_NO_THROW( pAuth->AddCredentialSet(sqlPort, sqlHostname, sqlUsername, sqlPassword) );
        CPPUNIT_ASSERT_NO_THROW( pAuth->Save() );

        //
        // Set up a stored procedure in the "mysql" database to work with
        //
        // Unfortunately, prepared statements (what our query engine is based on) do not
        // support creation/dropping of stored procedures. So we drop to raw SQL API code
        // to handle that after attaching to the database.
        //

        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );

        bool fStatus;
        vector<string> parameters;
        fStatus = pBinding->AttachUsingStoredCredentials(sqlPort, pAuth, "mysql");
        CPPUNIT_ASSERT_EQUAL_MESSAGE(pBinding->GetErrorText(), true, fStatus);

        MYSQL* mysql = g_pFactory->GetDependencies()->m_sqlConnection;
        CPPUNIT_ASSERT( mysql );

        fStatus = mysql_query(mysql, "drop procedure if exists GetUserData;");
        CPPUNIT_ASSERT_MESSAGE(mysql_error(mysql), ! fStatus);

        fStatus = mysql_query(mysql,
            "CREATE PROCEDURE GetUserData(in username char(255)) "
            "BEGIN "
            "  SELECT host, user, password FROM user WHERE user like username and password <> ''; "
            "END");
        CPPUNIT_ASSERT_MESSAGE(mysql_error(mysql), ! fStatus);

        // Key properties
        m_keyNames.push_back(L"InstanceID");
    }

    void tearDown(void)
    {
        // Drop the stored procedure that we needed for testing (see setUp() for restrictions)
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        util::unique_ptr<MySQL_Authentication> pAuth(g_pFactory->GetAuthentication());
        pAuth->Load();

        bool fStatus;
        vector<string> parameters;
        fStatus = pBinding->AttachUsingStoredCredentials(sqlPort, pAuth, "mysql");
        CPPUNIT_ASSERT_EQUAL_MESSAGE(pBinding->GetErrorText(), true, fStatus);

        MYSQL* mysql = g_pFactory->GetDependencies()->m_sqlConnection;
        CPPUNIT_ASSERT( mysql );

        fStatus = mysql_query(mysql, "drop procedure if exists GetUserData;");
        CPPUNIT_ASSERT_MESSAGE(mysql_error(mysql), ! fStatus);

        // Delete the authentication file
        SCXFile::Delete( s_authFilePath );

        std::wstring errMsg;
        TestableContext context;
        TearDownAgent<mi::MySQL_StoredProcedureRow_AsXML_Class_Provider>(context, CALL_LOCATION(errMsg));
        CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, false, context.WasRefuseUnloadCalled() );

        g_pFactory = NULL;
    }

    void TestEnumerateWithNoQueryFails_KeysOnly()
    {
        TestableContext context;
        mi::Module module;
        mi::MySQL_StoredProcedureRow_AsXML_Class_Provider agent(&module);

        agent.EnumerateInstances(context, NULL, context.GetPropertySet(), true, NULL);
        CPPUNIT_ASSERT_EQUAL( MI_RESULT_FAILED, context.GetResult() );
    }

    void TestEnumerateWithNoQueryFails_AllProps()
    {
        TestableContext context;
        mi::Module module;
        mi::MySQL_StoredProcedureRow_AsXML_Class_Provider agent(&module);

        agent.EnumerateInstances(context, NULL, context.GetPropertySet(), false, NULL);
        CPPUNIT_ASSERT_EQUAL( MI_RESULT_FAILED, context.GetResult() );
    }

    void TestEnumerateInstancesKeysOnly()
    {
        std::wstring errMsg;
        TestableContext context;
        MI_Filter filter( TestableFilter::SetUp(
                              "select * from MySQL_StoredProcedureRow_AsXML"
                              " where DatabaseName=\"mysql\""
                              "  or StoredProcedureName = \"GetUserData\""
                              "  or parameters=\"ro%\"") );
        StandardTestEnumerateKeysOnly<mi::MySQL_StoredProcedureRow_AsXML_Class_Provider>(
            m_keyNames, context, CALL_LOCATION(errMsg), &filter);

        CPPUNIT_ASSERT_MESSAGE(StrToUTF8(StrAppend(L"Number of records returned: ", context.Size())), context.Size() >= 1);

        for (size_t i = 0; i < context.Size(); ++i)
        {
            const TestableInstance &instance = context[i];

            // Verify the InstanceID
            NameResolver nr;
            wstringstream ss;
            ss << nr.GetHostname()
               << L":" + StrFromUTF8(sqlHostname)
               << L":" + StrFrom(sqlPort)
               << L":mysql:GetUserData:" << i + 1;
            CPPUNIT_ASSERT_EQUAL(ss.str(), instance.GetKey(L"InstanceID", CALL_LOCATION(errMsg)));
        }
    }

    void TestEnumerateInstances()
    {
        std::wstring errMsg;
        TestableContext context;
        MI_Filter filter( TestableFilter::SetUp(
                              "select * from MySQL_StoredProcedureRow_AsXML"
                              " where DatabaseName=\"mysql\""
                              "  or StoredProcedureName = \"GetUserData\""
                              "  or parameters=\"ro%\"") );
        StandardTestEnumerateInstances<mi::MySQL_StoredProcedureRow_AsXML_Class_Provider>(
            m_keyNames, context, CALL_LOCATION(errMsg), &filter);

        ValidateInstance(context, CALL_LOCATION(errMsg));
    }

    void TestVerifyKeyCompletePartialFails()
    {
        std::wstring errMsg;
        MI_Filter filter( TestableFilter::SetUp(
                              "select * from MySQL_StoredProcedureRow_AsXML"
                              " where DatabaseName=\"mysql\""
                              "  or StoredProcedureName = \"GetUserData\""
                              "  or parameters=\"ro%\"") );

        // GetInstance isn't implemented, verify it fails
        CPPUNIT_ASSERT_EQUAL_MESSAGE(
            ERROR_MESSAGE,
            MI_RESULT_NOT_SUPPORTED,
            (VerifyGetInstanceByCompleteKeySuccess<mi::MySQL_StoredProcedureRow_AsXML_Class_Provider,
                mi::MySQL_StoredProcedureRow_AsXML_Class>(
                    m_keyNames, static_cast<size_t>(-1), CALL_LOCATION(errMsg), &filter)));
    }

    void TestGetInstanceFails()
    {
        std::wstring errMsg;

        // Build an InstanceID
        NameResolver nr;
        wstringstream ss;
        ss << nr.GetHostname()
           << L":" + StrFromUTF8(sqlHostname)
           << L":" + StrFrom(sqlPort)
           << L":mysql:GetUserData:" << 1;

        std::vector<std::wstring> keyValues;
        keyValues.push_back( ss.str() );

        // GetInstance isn't implemented, verify it fails even with correct key
        TestableContext context;
        MI_Filter filter( TestableFilter::SetUp(
                              "select * from MySQL_StoredProcedureRow_AsXML"
                              " where DatabaseName=\"mysql\""
                              "  or StoredProcedureName = \"GetUserData\""
                              "  or parameters=\"ro%\"") );
        CPPUNIT_ASSERT_EQUAL(
            MI_RESULT_NOT_SUPPORTED,
            (GetInstance<mi::MySQL_StoredProcedureRow_AsXML_Class_Provider,
                 mi::MySQL_StoredProcedureRow_AsXML_Class>(m_keyNames, keyValues, context, CALL_LOCATION(errMsg))));
    }

    void ValidateInstance(const TestableContext& context, std::wstring errMsg)
    {
        // We should always get at least one result set back (root login)
        CPPUNIT_ASSERT_MESSAGE(
            StrToUTF8(StrAppend(L"Number of records returned: ", context.Size())),
            context.Size() >= 1);

        for (size_t i = 0; i < context.Size(); ++i)
        {
            const TestableInstance &instance = context[i];

            CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, m_keyNames[0], instance.GetKeyName(0, CALL_LOCATION(errMsg)));

            // Verify the InstanceID
            NameResolver nr;
            wstringstream ss;
            ss << nr.GetHostname()
               << L":" + StrFromUTF8(sqlHostname)
               << L":" + StrFrom(sqlPort)
               << L":mysql:GetUserData:" << i + 1;
            CPPUNIT_ASSERT_EQUAL(ss.str(), instance.GetKey(L"InstanceID", CALL_LOCATION(errMsg)));

            std::wstring tmpExpectedProperties[] = {L"InstanceID",
                                                    L"Port",
                                                    L"DatabaseName",
                                                    L"StoredProcedureName",
                                                    L"RowXMLValue",
                                                    L"IsTruncated"};

            const size_t numprops = sizeof(tmpExpectedProperties) / sizeof(tmpExpectedProperties[0]);
            VerifyInstancePropertyNames(instance, tmpExpectedProperties, numprops, CALL_LOCATION(errMsg));

            // Validate properties
            MI_Uint16 port = instance.GetProperty(L"Port", CALL_LOCATION(errMsg)).GetValue_MIUint16(CALL_LOCATION(errMsg));
            CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, sqlPort, port);

            CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, std::wstring(L"mysql"),
                instance.GetProperty(L"DatabaseName", CALL_LOCATION(errMsg)).GetValue_MIString(CALL_LOCATION(errMsg)));

            wstring xmlValue = instance.GetProperty(L"RowXMLValue", CALL_LOCATION(errMsg)).GetValue_MIString(CALL_LOCATION(errMsg));
            CPPUNIT_ASSERT_MESSAGE(ERROR_MESSAGE, xmlValue.size());
            // Starting prefix for all RowXMLValue properties
            CPPUNIT_ASSERT_EQUAL_MESSAGE(
                ERROR_MESSAGE,
                static_cast<size_t>(0),
                xmlValue.find(L"<row><field name=\"host\">") );
            // Ending suffix for all RowXMLValue properties
            CPPUNIT_ASSERT_EQUAL_MESSAGE(
                ERROR_MESSAGE,
                xmlValue.size() - 14,
                xmlValue.find(L"</field></row>") );

            CPPUNIT_ASSERT_EQUAL_MESSAGE(ERROR_MESSAGE, static_cast<bool>(false),
                instance.GetProperty(L"IsTruncated", CALL_LOCATION(errMsg)).GetValue_MIBoolean(CALL_LOCATION(errMsg)));
        }
    }

    void TestGetValueForKey_KeyExists()
    {
        string value;
        CPPUNIT_ASSERT( GetValueForKey(value, "select * from gold where Param=\"bar\"", "param") );
        CPPUNIT_ASSERT_EQUAL( string("bar"), value );
    }

    void TestGetValueForKey_KeyNotFound()
    {
        string value;
        CPPUNIT_ASSERT( ! GetValueForKey(value, "select * from gold where Param=\"bar\"", "notfound") );
    }

    void TestGetValueForKey_MultipleKeysFound()
    {
        string dbName, spName, params;
        string filter( "select * from MySQL_StoredProcedureRow_AsXML"
                       " where DatabaseName=\"mysql\""
                       "  or StoredProcedureName = \"GetUserData\""
                       "  or Parameters=\"ro%\"" );
        CPPUNIT_ASSERT( GetValueForKey(dbName, filter, "databasename") );
        CPPUNIT_ASSERT( GetValueForKey(spName, filter, "storedprocedurename") );
        CPPUNIT_ASSERT( GetValueForKey(params, filter, "parameters") );

        CPPUNIT_ASSERT_EQUAL( string("mysql"), dbName );
        CPPUNIT_ASSERT_EQUAL( string("GetUserData"), spName );
        CPPUNIT_ASSERT_EQUAL( string("ro%"), params );
    }
    
    void TestGetValueForKey_QuotedParameters()
    {
        string params;
        string filter( "select * from MySQL_StoredProcedureRow_AsXML"
                       " where DatabaseName=\"mysql\""
                       "  or StoredProcedureName = \"GetUserData\""
                       "  or Parameters=\" 'ro%,ot%', car\\\"rot\" " );
        CPPUNIT_ASSERT( GetValueForKey(params, filter, "parameters") );

        CPPUNIT_ASSERT_EQUAL( string(" 'ro%,ot%', car\\\"rot"), params );
    }

    void TestGetValueForKey_LongQuotedParameters()
    {
        string params;
        string filter( "select * from MySQL_StoredProcedureRow_AsXML"
                       " where DatabaseName=\"mysql\""
                       "  or StoredProcedureName = \"GetUserData\""
                       "  or Parameters=\" 'ro%,otUser%', car\\\"rot top, 'potato,bottoms'\" " );
        CPPUNIT_ASSERT( GetValueForKey(params, filter, "parameters") );

        CPPUNIT_ASSERT_EQUAL( string(" 'ro%,otUser%', car\\\"rot top, 'potato,bottoms'"), params );
    }

    void TestQuoteXML_EmptyString()
    {
        CPPUNIT_ASSERT_EQUAL( string(""), QuoteXMLString("") );
    }

    void TestQuoteXML_UnremarkableChars()
    {
        string xmlString = "Unremarkable data to validate";
        CPPUNIT_ASSERT_EQUAL( xmlString, QuoteXMLString(xmlString) );
    }

    void TestQuoteXML_DoubleQuote()
    {
        CPPUNIT_ASSERT_EQUAL( string("&quot;"), QuoteXMLString("\"") );
    }

    void TestQuoteXML_Apostrophe()
    {
        CPPUNIT_ASSERT_EQUAL( string("&apos;"), QuoteXMLString("'") );
    }

    void TestQuoteXML_LessThan()
    {
        CPPUNIT_ASSERT_EQUAL( string("&lt;"), QuoteXMLString("<") );
    }

    void TestQuoteXML_GreaterThan()
    {
        CPPUNIT_ASSERT_EQUAL( string("&gt;"), QuoteXMLString(">") );
    }

    void TestQuoteXML_Ampersand()
    {
        CPPUNIT_ASSERT_EQUAL( string("&amp;"), QuoteXMLString("&") );
    }

    void TestQuoteXML_EmbeddedQuotableBytes()
    {
        string inpText = "This is\"an'embedded<string>with>quoteable&bytes!@#$%^*()-_+=1234567890";
        string outText = "This is&quot;an&apos;embedded&lt;string&gt;with&gt;quoteable&amp;bytes!@#$%^*()-_+=1234567890";
        CPPUNIT_ASSERT_EQUAL( outText, QuoteXMLString(inpText) );
    }

    void TestCompleteParameterParsing()
    {
        string params;
        string filter( "select * from MySQL_StoredProcedureRow_AsXML"
                       " where DatabaseName=\"mysql\""
                       "  or StoredProcedureName = \"GetUserData\""
                       "  or Parameters=\" 'ro%,otUser%', car\\\"rot top, 'potato,bottoms'\" " );
        CPPUNIT_ASSERT( GetValueForKey(params, filter, "parameters") );

        CPPUNIT_ASSERT_EQUAL( string(" 'ro%,otUser%', car\\\"rot top, 'potato,bottoms'"), params );

        vector<wstring> parameterList;
        StrTokenizeQuoted( StrFromUTF8(params), parameterList, L"," );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(3), parameterList.size() );
        CPPUNIT_ASSERT_EQUAL( wstring(L"ro%,otUser%"), parameterList[0] );
        CPPUNIT_ASSERT_EQUAL( wstring(L"car\\\"rot top"), parameterList[1] );
        CPPUNIT_ASSERT_EQUAL( wstring(L"potato,bottoms"), parameterList[2] );
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MySQL_Stored_Procedure_Test );
