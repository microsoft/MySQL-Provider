/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.

    Created date    2015-01-23 08:45:00

    MySQL Authentication Tool unit tests.

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxfile.h>
#include <scxcorelib/scxprocess.h>
#include <scxcorelib/stringaid.h>
#include <testutils/scxunit.h>
#include <testutils/providertestutils.h>

#include <iostream> // for cout

#include "sqlauth.h"
#include "sqlcredentials.h"

static const std::wstring s_authProgram = L"./mycimprovauth";
static const wchar_t* s_authFilePath = L"./mysql-auth";

static const int s_timeout = 0;


using namespace SCXCoreLib;

class MyCimprovAuth_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( MyCimprovAuth_Test );

    CPPUNIT_TEST( test_NoCommandOptions );
    CPPUNIT_TEST( test_BasicHelp );
    CPPUNIT_TEST( test_CommandHelp );
    CPPUNIT_TEST( test_OptionTest_Valid );
    CPPUNIT_TEST( test_CommandPrint_Empty );
    CPPUNIT_TEST( test_CommandQuit_DoesntUpdate );
    CPPUNIT_TEST( test_AutoUpdate_Interactive );
    CPPUNIT_TEST( test_AutoUpdate_CommandLine );
    CPPUNIT_TEST( test_Default_Interactive );
    CPPUNIT_TEST( test_Default_CommandLine );
    CPPUNIT_TEST( test_Update_Interactive );
    CPPUNIT_TEST( test_Update_CommandLine );
    CPPUNIT_TEST( test_Delete_Interactive );
    CPPUNIT_TEST( test_Delete_CommandLine );
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

    void test_NoCommandOptions()
    {
        std::istringstream processInput;
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram, processInput, processOutput, processErr, s_timeout);
        CPPUNIT_ASSERT_EQUAL( "", processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( "./mycimprovauth: Try './mycimprovauth -h' for more information.\n", processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 1, status );
    }

    void test_BasicHelp()
    {
        std::istringstream processInput;
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram + L" -h", processInput, processOutput, processErr, s_timeout);

        std::stringstream expectedOutput;
        expectedOutput << "Usage: ./mycimprovauth[options] [operations]" << std::endl
              << std::endl
              << "Options:" << std::endl
              << "  -h:\tDisplay detailed help information" << std::endl
              << "  -i:\tInteractive use" << std::endl
              << "  -v:\tDisplay version information" << std::endl << std::endl
              << "Operations:" << std::endl
              << "  autoupdate true|false" << std::endl
              << "  default [bind-address] [username] [password]" << std::endl
              << "  delete default|<port#>" << std::endl
              << "  help" << std::endl
              << "  print" << std::endl
              << "  update <port#> [bind-address] [username] [password]" << std::endl;

        CPPUNIT_ASSERT_EQUAL( expectedOutput.str(), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );
    }

    void test_CommandHelp()
    {
        std::istringstream processInput;
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram + L" help", processInput, processOutput, processErr, s_timeout);

        std::stringstream expectedOutput;
        expectedOutput << "Help for commands to maintain MySQL Provider Authentication File:" << std::endl << std::endl
                       << "  autoupdate [true|false]" << std::endl
                       << "      Allow/disallow automatic updates to authentication file." << std::endl << std::endl
                       << "  default [bind-address] [username] [password] [in-base64]:" << std::endl
                       << "      Add or update default record to provide default information for" << std::endl
                       << "      port records (set via update command)." << std::endl
                       << "        [bind-address] is default bind address for MySQL Server" << std::endl
                       << "        [username] is default username for login to MySQL Server" << std::endl
                       << "        [password] is default password for login to MySQL Server" << std::endl
                       << "        [in-base64] is \"true\" or \"false\" if record pw in Base64 format" << std::endl
                       << "      Default record is entirely optional, and need not exist.  Specify" << std::endl
                       << "      an empty field as \"\"." << std::endl << std::endl
                       << "  delete [default|port#]:" << std::endl
                       << "      Delete default record or a port record in authentication file." << std::endl << std::endl
                       << "  exit:" << std::endl
                       << "      Saves changes and exits (only useful for interactive mode)." << std::endl << std::endl
                       << "  help:" << std::endl
                       << "      Display this help text." << std::endl << std::endl
                       << "  print:" << std::endl
                       << "      Print the contents of the MySQL provider authenticaiton file." << std::endl << std::endl
                       << "  quit:" << std::endl
                       << "      Quits interactive mode without saving changes." << std::endl << std::endl
                       << "  save:" << std::endl
                       << "      Save changes to disk. This is automatic for non-interactive mode." << std::endl << std::endl
                       << "  update [port#] [bind-address] [username] [password] [in-base64]:" << std::endl
                       << "      Add or update a port record to identify a MySQL Server instance in the" << std::endl
                       << "      authentication file." << std::endl
                       << "        [port#] is the port number for the MySQL Server instance" << std::endl
                       << "        [bind-address] is default bind address for MySQL Server" << std::endl
                       << "        [username] is default username for login to MySQL Server" << std::endl
                       << "        [password] is default password for login to MySQL Server" << std::endl
                       << "        [in-base64] is \"true\" or \"false\" if record pw in Base64 format" << std::endl
                       << "      Note that all information is validated by connecting to MySQL Server." << std::endl
                       << "      Specify an empty field as \"\"." << std::endl;

        CPPUNIT_ASSERT_EQUAL( expectedOutput.str(), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );
    }

    void test_OptionTest_Valid()
    {
        std::istringstream processInput;
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram + L" -t", processInput, processOutput, processErr, s_timeout);

        CPPUNIT_ASSERT_EQUAL( std::string(""), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string("Error - No command specified or command keyword empty\n"), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 3, status );
    }

    void test_CommandPrint_Empty()
    {
        std::istringstream processInput;
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram + L" -t print", processInput, processOutput, processErr, s_timeout);

        std::stringstream expectedOutput;
        expectedOutput << "[Automatic Updates: Enabled]" << std::endl 
                       << "[No default entry defined]" << std::endl;

        CPPUNIT_ASSERT_EQUAL( expectedOutput.str(), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );
    }

    void test_CommandQuit_DoesntUpdate()
    {
        std::istringstream processInput( std::string("autoupdate false\nprint\nquit\n") );
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram + L" -t -i", processInput, processOutput, processErr, s_timeout);

        std::stringstream expectedOutput;
        expectedOutput << "auth> autoupdate false" << std::endl
                       << "auth> print" << std::endl
                       << "[Automatic Updates: DISABLED]" << std::endl 
                       << "[No default entry defined]" << std::endl
                       << "auth> quit" << std::endl;

        CPPUNIT_ASSERT_EQUAL( expectedOutput.str(), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[0] );
    }

    void test_AutoUpdate_Interactive()
    {
        std::istringstream processInput( std::string("autoupdate false\nprint\nexit\n") );
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram + L" -t -i", processInput, processOutput, processErr, s_timeout);

        std::stringstream expectedOutput;
        expectedOutput << "auth> autoupdate false" << std::endl
                       << "auth> print" << std::endl
                       << "[Automatic Updates: DISABLED]" << std::endl 
                       << "[No default entry defined]" << std::endl
                       << "auth> exit" << std::endl;

        CPPUNIT_ASSERT_EQUAL( expectedOutput.str(), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=false"), lines[0] );
    }

    void test_AutoUpdate_CommandLine()
    {
        std::istringstream processInput;
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram + L" -t autoupdate false", processInput, processOutput, processErr, s_timeout);

        CPPUNIT_ASSERT_EQUAL( std::string(""), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=false"), lines[0] );
    }

    void test_Default_Interactive()
    {
        std::istringstream processInput( std::string("default " + sqlHostname + " " + sqlUsername + " " + sqlPassword + "\nprint\nexit\n") );
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram + L" -t -i", processInput, processOutput, processErr, s_timeout);

        std::stringstream expectedOutput;
        expectedOutput << "auth> default "<< sqlHostname << " " << sqlUsername << " " << sqlPassword << std::endl
                       << "auth> print" << std::endl
                       << "[Automatic Updates: Enabled]" << std::endl 
                       << std::endl
                       << "Default Entry: " << std::endl
                       << "    Binding:  " << sqlHostname << std::endl
                       << "    Username: root" << std::endl
                       << "    Password: root" << std::endl
                       << "auth> exit" << std::endl;

        CPPUNIT_ASSERT_EQUAL( expectedOutput.str(), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, root, cm9vdA=="), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[1] );
    }

    void test_Default_CommandLine()
    {
        std::istringstream processInput;
        std::ostringstream processOutput;
        std::ostringstream processErr;

        std::wstring commandLine(s_authProgram);
        commandLine += L" -t default " + StrFromUTF8(sqlHostname) + L" " + StrFromUTF8(sqlUsername) + L" " + StrFromUTF8(sqlPassword);
        int status = SCXProcess::Run(commandLine, processInput, processOutput, processErr, s_timeout);

        CPPUNIT_ASSERT_EQUAL( std::string(""), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, root, cm9vdA=="), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[1] );
    }

    void test_Update_Interactive()
    {
        std::istringstream processInput( std::string(
            "default " + sqlHostname + " " + sqlUsername + " " + sqlPassword + "\n"
            "update 3306 \"\"\n"
            "print\n"
            "exit\n") );
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram + L" -t -i", processInput, processOutput, processErr, s_timeout);

        std::stringstream expectedOutput;
        expectedOutput << "auth> default " << sqlHostname << " " << sqlUsername << " " << sqlPassword << std::endl
                       << "auth> update 3306 \"\"" << std::endl
                       << "auth> print" << std::endl
                       << "[Automatic Updates: Enabled]" << std::endl 
                       << std::endl
                       << "Default Entry: " << std::endl
                       << "    Binding:  " << sqlHostname << std::endl
                       << "    Username: " << sqlUsername << std::endl
                       << "    Password: " << sqlPassword << std::endl
                       << std::endl
                       << "Port 3306:" << std::endl
                       << "    Binding:  <From Default>" << std::endl
                       << "    Username: <From Default>" << std::endl
                       << "    Password: <From Default>" << std::endl
                       << "auth> exit" << std::endl;

        CPPUNIT_ASSERT_EQUAL( expectedOutput.str(), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(3), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, root, cm9vdA=="), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=, ,"), lines[1] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[2] );
    }

    void test_Update_CommandLine()
    {
        std::istringstream processInput;
        std::ostringstream processOutput;
        std::ostringstream processErr;

        std::wstring commandLine(s_authProgram);
        commandLine += L" -t default " + StrFromUTF8(sqlHostname) + L" " + StrFromUTF8(sqlUsername) + L" " + StrFromUTF8(sqlPassword);
        int status = SCXProcess::Run(commandLine, processInput, processOutput, processErr, s_timeout);

        CPPUNIT_ASSERT_EQUAL( std::string(""), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        commandLine = s_authProgram + L" -t update 3306 " + StrFromUTF8(sqlHostname);
        status = SCXProcess::Run(commandLine, processInput, processOutput, processErr, s_timeout);

        CPPUNIT_ASSERT_EQUAL( std::string(""), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(3), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, root, cm9vdA=="), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=127.0.0.1, ,"), lines[1] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[2] );
    }

    void test_Delete_Interactive()
    {
        std::istringstream processInput( std::string(
            "default " + sqlHostname + " " + sqlUsername + " " + sqlPassword + "\n"
            "update 3306 \"\"\n"
            "delete 3306\n"
            "delete default\n"
            "print\n"
            "exit\n") );
        std::ostringstream processOutput;
        std::ostringstream processErr;

        int status = SCXProcess::Run(s_authProgram + L" -t -i", processInput, processOutput, processErr, s_timeout);

        std::stringstream expectedOutput;
        expectedOutput << "auth> default " << sqlHostname << " " << sqlUsername << " " << sqlPassword << std::endl
                       << "auth> update 3306 \"\"" << std::endl
                       << "auth> delete 3306" << std::endl
                       << "auth> delete default" << std::endl
                       << "auth> print" << std::endl
                       << "[Automatic Updates: Enabled]" << std::endl
                       << "[No default entry defined]" << std::endl
                       << "auth> exit" << std::endl;

        CPPUNIT_ASSERT_EQUAL( expectedOutput.str(), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[0] );
    }

    void test_Delete_CommandLine()
    {
        std::istringstream processInput;
        std::ostringstream processOutput;
        std::ostringstream processErr;

        // Create default record
        std::wstring commandLine(s_authProgram);
        commandLine += L" -t default " + StrFromUTF8(sqlHostname) + L" " + StrFromUTF8(sqlUsername) + L" " + StrFromUTF8(sqlPassword);
        int status = SCXProcess::Run(commandLine, processInput, processOutput, processErr, s_timeout);

        CPPUNIT_ASSERT_EQUAL( std::string(""), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        std::vector<std::wstring> lines;
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, root, cm9vdA=="), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[1] );

        // Create port 3306 record
        commandLine = s_authProgram + L" -t update 3306 " + StrFromUTF8(sqlHostname);
        status = SCXProcess::Run(commandLine, processInput, processOutput, processErr, s_timeout);

        CPPUNIT_ASSERT_EQUAL( std::string(""), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(3), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, root, cm9vdA=="), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"3306=127.0.0.1, ,"), lines[1] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[2] );

        // Delete port 3306 record
        commandLine = s_authProgram + L" -t delete 3306";
        status = SCXProcess::Run(commandLine, processInput, processOutput, processErr, s_timeout);

        CPPUNIT_ASSERT_EQUAL( std::string(""), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(2), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"0=127.0.0.1, root, cm9vdA=="), lines[0] );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[1] );

        // Delete default record
        commandLine = s_authProgram + L" -t delete default";
        status = SCXProcess::Run(commandLine, processInput, processOutput, processErr, s_timeout);

        CPPUNIT_ASSERT_EQUAL( std::string(""), processOutput.str() );
        CPPUNIT_ASSERT_EQUAL( std::string(""), processErr.str() );
        CPPUNIT_ASSERT_EQUAL( 0, status );

        // Validate that the authentication file was written properly

        CPPUNIT_ASSERT( SCXFile::Exists( s_authFilePath ) );

        SCXFile::ReadAllLines( s_authFilePath, lines, nlfs );
        CPPUNIT_ASSERT_EQUAL( static_cast<size_t>(1), lines.size() );
        CPPUNIT_ASSERT_EQUAL( std::wstring(L"AutoUpdate=true"), lines[0] );
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( MyCimprovAuth_Test );
