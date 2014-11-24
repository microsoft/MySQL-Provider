/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.

    Created date    2014-05-23 08:31:00

    MySQL binding unit tests.

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/scxfile.h>
#include <scxcorelib/stringaid.h>
#include <testutils/scxunit.h>
#include <testutils/providertestutils.h>

#include <iostream> // for cout

#include "sqlauth.h"

static const wchar_t* s_authFilePath = L"./mysql-auth";


using namespace SCXCoreLib;

// Avoid collision with definitions in other test files
namespace
{
    class MySQL_TestableAuthenticationDependencies : public MySQL_AuthenticationDependencies
    {
    public:
        virtual SCXCoreLib::SCXFilePath GetDefaultAuthFileName() const
        {
            return s_authFilePath;
        }

        virtual bool Force_AutoUpdate_Flag() { return false; }
    };
}


class Authentication_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( Authentication_Test );

    CPPUNIT_TEST( testAuth_VerifyConstruction );
    CPPUNIT_TEST( testAuth_VerifyLoadWithNoFile );
    CPPUNIT_TEST( testAuth_PersistEmptyFile );
    CPPUNIT_TEST( testAuth_PersistAutoUpdate_False );
    CPPUNIT_TEST( testAuth_PersistAutoUpdate_True );
    CPPUNIT_TEST( testAuth_VerifyNoAutoUpdateKeyReturnsTrue );
    CPPUNIT_TEST( testAuth_AutoUpdate_VerifyCaseInsensitivity_False );
    CPPUNIT_TEST( testAuth_AutoUpdate_VerifyCaseInsensitivity_True );
    CPPUNIT_TEST( testAuth_GetEntry_Default_Invalid_Value_Fails );
    CPPUNIT_TEST( testAuth_GetEntry_Default_Binding_Only );
    CPPUNIT_TEST( testAuth_GetEntry_Default_InvalidPassword_Fails );
    CPPUNIT_TEST( testAuth_GetEntry_Default_UserPassword_Only );
    CPPUNIT_TEST( testAuth_GetEntry_Default_BindingUserPassword );
    CPPUNIT_TEST( testAuth_GetEntry_Binding_Only );
    CPPUNIT_TEST( testAuth_GetEntry_UserPassword_Only );
    CPPUNIT_TEST( testAuth_GetEntry_BindingUserPassword );
    CPPUNIT_TEST( testAuth_AddCred_Default_BindingOnly );
    CPPUNIT_TEST( testAuth_AddCred_Default_UsernameOnly_Fails );
    CPPUNIT_TEST( testAuth_AddCred_Default_PasswordOnly_Fails );
    CPPUNIT_TEST( testAuth_AddCred_Default_UserPass_Only );
    CPPUNIT_TEST( testAuth_AddCred_Default_With_All );
    CPPUNIT_TEST( testAuth_AddCred_NoBinding_No_Default );
    CPPUNIT_TEST( testAuth_AddCred_NoUsernamePassword_No_Default );
    CPPUNIT_TEST( testAuth_AddCred_NoValues_With_Default );
    CPPUNIT_TEST( testAuth_AddCred_NoBinding_With_Default );
    CPPUNIT_TEST( testAuth_AddCred_NoUsernamePassword_With_Default );
    CPPUNIT_TEST( testAuth_AddCred_All_With_Default );
    CPPUNIT_TEST( testAuth_AddCred_Allows_Updates );
    CPPUNIT_TEST( testAuth_AddCred_UpdateToDefaultSucceedsIfNotNeeded );
    CPPUNIT_TEST( testAuth_AddCred_UpdateToDefaultFailsIfNeeded );
    CPPUNIT_TEST( testAuth_DelCred_Default_Binding_Fails );
    CPPUNIT_TEST( testAuth_DelCred_Default_UsernamePassword_Fails );
    CPPUNIT_TEST( testAuth_DelCred_Default_Only );
    CPPUNIT_TEST( testAuth_DelCred_MySQL_Port_Only );
    CPPUNIT_TEST( testAuth_DelCred_Default_With_Others );
    CPPUNIT_TEST( testAuth_DelCred_MySQL_Port_With_Others );
    CPPUNIT_TEST( testAuth_GetPortList );

    CPPUNIT_TEST_SUITE_END();

private:

public:
    void setUp(void)
    {
    }

    void tearDown(void)
    {
        // Delete the authentication file
        SCXCoreLib::SCXFile::Delete( s_authFilePath );
    }

    void ValidateAuth(MySQL_AuthenticationEntry& authEntry,
                      unsigned int port, std::string binding, std::string username, std::string password)
    {
        CPPUNIT_ASSERT_EQUAL( port, authEntry.port );
        CPPUNIT_ASSERT_EQUAL( binding, authEntry.binding );
        CPPUNIT_ASSERT_EQUAL( username, authEntry.username );
        CPPUNIT_ASSERT_EQUAL( password, authEntry.password );
    }

    void testAuth_VerifyConstruction()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
    }

    void testAuth_VerifyLoadWithNoFile()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
    }

    void testAuth_PersistEmptyFile()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.Save();

        // File must exist
        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        // File must be empty (no size() property on SCXFile)
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT( lines.empty() );
    }

    void testAuth_PersistAutoUpdate_False()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AllowAutomaticUpdates(false);
        auth.Save();

        // File must exist
        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=false"), lines[0] );

        CPPUNIT_ASSERT_EQUAL( static_cast<bool>(false), auth.GetAutomaticUpdates() );
    }

    void testAuth_PersistAutoUpdate_True()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AllowAutomaticUpdates(true);
        auth.Save();

        // File must exist
        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[0] );

        CPPUNIT_ASSERT_EQUAL( static_cast<bool>(true), auth.GetAutomaticUpdates() );
    }

    void testAuth_VerifyNoAutoUpdateKeyReturnsTrue()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        CPPUNIT_ASSERT_EQUAL( static_cast<bool>(true), auth.GetAutomaticUpdates() );
    }

    void testAuth_AutoUpdate_VerifyCaseInsensitivity_False()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"AutoUpdate=faLSe");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        CPPUNIT_ASSERT_EQUAL( static_cast<bool>(false), auth.GetAutomaticUpdates() );
    }

    void testAuth_AutoUpdate_VerifyCaseInsensitivity_True()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"AutoUpdate=tRUe");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        CPPUNIT_ASSERT_EQUAL( static_cast<bool>(true), auth.GetAutomaticUpdates() );
    }

    void testAuth_GetEntry_Default_Invalid_Value_Fails()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"0=, NoPasswordFollows");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        MySQL_AuthenticationEntry authEntry;
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        SCXUNIT_ASSERT_THROWN_EXCEPTION(auth.Load(), MySQL_Auth::InvalidAuthentication, L"invalid value");
    }

    void testAuth_GetEntry_Default_Binding_Only()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"0=127.0.0.1, ,");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        MySQL_AuthenticationEntry authEntry;
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.GetEntry(0, authEntry);
        ValidateAuth(authEntry, 0, "127.0.0.1", "", "");
    }

    void testAuth_GetEntry_Default_InvalidPassword_Fails()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"0=, username, x=");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        MySQL_AuthenticationEntry authEntry;
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        SCXUNIT_ASSERT_THROWN_EXCEPTION(auth.Load(), MySQL_Auth::InvalidAuthentication, L"decode password");
    }

    void testAuth_GetEntry_Default_UserPassword_Only()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"0=, username, cGFzc3dvcmQ=");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        MySQL_AuthenticationEntry authEntry;
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.GetEntry(0, authEntry);
        ValidateAuth(authEntry, 0, "", "username", "password");
    }

    void testAuth_GetEntry_Default_BindingUserPassword()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"0=jeffcof64-rhel6-01, username, cGFzc3dvcmQ=");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        MySQL_AuthenticationEntry authEntry;
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.GetEntry(0, authEntry);
        ValidateAuth(authEntry, 0, "jeffcof64-rhel6-01", "username", "password");
    }

    void testAuth_GetEntry_Binding_Only()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"0=jeffcof64-rhel6-01, username, cGFzc3dvcmQ=");
        lines.push_back(L"3306=127.0.0.1, ,");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        MySQL_AuthenticationEntry authEntry;
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.GetEntry(3306, authEntry);
        ValidateAuth(authEntry, 3306, "127.0.0.1", "username", "password");
    }

    void testAuth_GetEntry_UserPassword_Only()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"0=jeffcof64-rhel6-01, username, cGFzc3dvcmQ=");
        lines.push_back(L"3306=, anewworld, d2FzIGZvdW5kIGJ5IENocmlzdG9waGVy");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        MySQL_AuthenticationEntry authEntry;
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.GetEntry(3306, authEntry);
        ValidateAuth(authEntry, 3306, "jeffcof64-rhel6-01", "anewworld", "was found by Christopher");
    }

    void testAuth_GetEntry_BindingUserPassword()
    {
        std::vector<std::wstring> lines;
        lines.push_back(L"0=jeffcof64-rhel6-01, username, cGFzc3dvcmQ=");
        lines.push_back(L"3306=localhost, anewworld, d2FzIGZvdW5kIGJ5IENocmlzdG9waGVy");
        SCXFile::WriteAllLines( s_authFilePath, lines, std::ios_base::out );

        MySQL_AuthenticationEntry authEntry;
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.GetEntry(3306, authEntry);
        ValidateAuth(authEntry, 3306, "localhost", "anewworld", "was found by Christopher");
    }

    void testAuth_AddCred_Default_BindingOnly()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "", "" );
        auth.Save();

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, ,"), lines[0] );
    }

    void testAuth_AddCred_Default_UsernameOnly_Fails()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();

        SCXUNIT_ASSERT_THROWN_EXCEPTION(auth.AddCredentialSet(0, "", "MySQLUser", "" ),
                                        MySQL_Auth::InvalidArgumentException, L"no password");
    }

    void testAuth_AddCred_Default_PasswordOnly_Fails()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();

        SCXUNIT_ASSERT_THROWN_EXCEPTION(auth.AddCredentialSet(0, "", "", "AuthenticateMe" ),
                                        MySQL_Auth::InvalidArgumentException, L"no username");
    }

    void testAuth_AddCred_Default_UserPass_Only()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "", "randomUser", "AuthenticateMe!" );
        auth.Save();

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=, randomUser, QXV0aGVudGljYXRlTWUh"), lines[0] );
    }

    void testAuth_AddCred_Default_With_All()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.Save();

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, randomUser, QXV0aGVudGljYXRlTWUh"), lines[0] );
    }

    void testAuth_AddCred_NoBinding_No_Default()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();

        SCXUNIT_ASSERT_THROWN_EXCEPTION(auth.AddCredentialSet(3306, "", "randomUser", "AuthenticateMe!"),
                                        MySQL_Auth::InvalidAuthentication, L"no binding");
    }

    void testAuth_AddCred_NoUsernamePassword_No_Default()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();

        SCXUNIT_ASSERT_THROWN_EXCEPTION(auth.AddCredentialSet(3306, "172.0.0.1", "", ""),
                                        MySQL_Auth::InvalidAuthentication, L"no username");
    }

    void testAuth_AddCred_NoValues_With_Default()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!");
        auth.AddCredentialSet(3306, "", "", "");
        auth.Save();

        MySQL_AuthenticationEntry authEntry;
        auth.GetEntry(0, authEntry);
        ValidateAuth(authEntry, 0, "127.0.0.1", "randomUser", "AuthenticateMe!");

        auth.GetEntry(3306, authEntry);
        ValidateAuth(authEntry, 3306, "127.0.0.1", "randomUser", "AuthenticateMe!");

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, randomUser, QXV0aGVudGljYXRlTWUh"), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=, ,"), lines[1] );
    }

    void testAuth_AddCred_NoBinding_With_Default()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!");
        auth.AddCredentialSet(3306, "", "anewworld", "was found by Christopher");
        auth.Save();

        MySQL_AuthenticationEntry authEntry;
        auth.GetEntry(3306, authEntry);
        ValidateAuth(authEntry, 3306, "127.0.0.1", "anewworld", "was found by Christopher");

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, randomUser, QXV0aGVudGljYXRlTWUh"), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=, anewworld, d2FzIGZvdW5kIGJ5IENocmlzdG9waGVy"), lines[1] );
    }

    void testAuth_AddCred_NoUsernamePassword_With_Default()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!");
        auth.AddCredentialSet(3306, "localhost", "", "");
        auth.Save();

        MySQL_AuthenticationEntry authEntry;
        auth.GetEntry(3306, authEntry);
        ValidateAuth(authEntry, 3306, "localhost", "randomUser", "AuthenticateMe!");

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, randomUser, QXV0aGVudGljYXRlTWUh"), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=localhost, ,"), lines[1] );
    }

    void testAuth_AddCred_All_With_Default()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.AddCredentialSet(3306, "localhost", "anewworld", "was found by Christopher");
        auth.Save();

        MySQL_AuthenticationEntry authEntry;
        auth.GetEntry(3306, authEntry);
        ValidateAuth(authEntry, 3306, "localhost", "anewworld", "was found by Christopher");

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, randomUser, QXV0aGVudGljYXRlTWUh"), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=localhost, anewworld, d2FzIGZvdW5kIGJ5IENocmlzdG9waGVy"), lines[1] );
    }

    void testAuth_AddCred_Allows_Updates()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.AddCredentialSet(3306, "localhost", "anewworld", "was found by Christopher");

        // Now update existing entry and verify that we got the correct information
        auth.AddCredentialSet(3306, "localhost", "", "");

        MySQL_AuthenticationEntry authEntry;
        auth.GetEntry( 3306, authEntry );
        ValidateAuth(authEntry, 3306, "localhost", "randomUser", "AuthenticateMe!");
    }

    void testAuth_AddCred_UpdateToDefaultSucceedsIfNotNeeded()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.AddCredentialSet(3306, "localhost", "anewworld", "was found by Christopher");

        CPPUNIT_ASSERT_NO_THROW( auth.AddCredentialSet(0, "172.0.0.1", "", "") );
    }

    void testAuth_AddCred_UpdateToDefaultFailsIfNeeded()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.AddCredentialSet(3306, "", "anewworld", "was found by Christopher");

        SCXUNIT_ASSERT_THROWN_EXCEPTION(auth.AddCredentialSet(0, "", "randomUser", "AuthenticateMe!"),
                                        MySQL_Auth::InvalidAuthentication, L"is required");
    }

    void testAuth_DelCred_Default_Binding_Fails()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.AddCredentialSet(3306, "", "anewworld", "was found by Christopher");

        SCXUNIT_ASSERT_THROWN_EXCEPTION(auth.DeleteCredentialSet(0),
                                        MySQL_Auth::InvalidAuthentication, L"is required");
    }

    void testAuth_DelCred_Default_UsernamePassword_Fails()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.AddCredentialSet(3306, "localhost", "", "");

        SCXUNIT_ASSERT_THROWN_EXCEPTION(auth.DeleteCredentialSet(0),
                                        MySQL_Auth::InvalidAuthentication, L"is required");
    }

    void testAuth_DelCred_Default_Only()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.DeleteCredentialSet(0);
        auth.Save();

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(0), lines.size() );
    }

    void testAuth_DelCred_MySQL_Port_Only()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(3306, "localhost", "anewworld", "was found by Christopher");
        auth.DeleteCredentialSet(3306);
        auth.Save();

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(0), lines.size() );
    }

    void testAuth_DelCred_Default_With_Others()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.AddCredentialSet(3306, "localhost", "anewworld", "was found by Christopher");
        auth.DeleteCredentialSet(0);
        auth.Save();

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=localhost, anewworld, d2FzIGZvdW5kIGJ5IENocmlzdG9waGVy"), lines[0] );
    }

    void testAuth_DelCred_MySQL_Port_With_Others()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.AddCredentialSet(3306, "localhost", "anewworld", "was found by Christopher");
        auth.DeleteCredentialSet(3306);
        auth.Save();

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, randomUser, QXV0aGVudGljYXRlTWUh"), lines[0] );
    }

    void testAuth_GetPortList()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies()) );
        auth.Load();
        auth.AddCredentialSet(0, "127.0.0.1", "randomUser", "AuthenticateMe!" );
        auth.AddCredentialSet(3306, "localhost", "anewworld", "was found by Christopher");
        auth.AddCredentialSet(3399, "192.168.1.100", "yetanother", "test password");
        auth.AllowAutomaticUpdates(false);
        auth.Save();

        std::vector<unsigned int> ports;
        auth.GetPortList( ports );

        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), ports.size() );
        CPPUNIT_ASSERT_EQUAL( static_cast<unsigned int>(3306), ports[0] );
        CPPUNIT_ASSERT_EQUAL( static_cast<unsigned int>(3399), ports[1] );

        // Verify authentication file contents
        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(4), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, randomUser, QXV0aGVudGljYXRlTWUh"), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=localhost, anewworld, d2FzIGZvdW5kIGJ5IENocmlzdG9waGVy"), lines[1] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3399=192.168.1.100, yetanother, dGVzdCBwYXNzd29yZA=="), lines[2] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=false"), lines[3] );
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( Authentication_Test );
