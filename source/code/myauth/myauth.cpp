/*----------------------------------------------------------------------------
  Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
*/
/**
   \file       myauth.cpp

   \brief      MySQL CIM Provider Authentication File Management

   \date       12-10-2014
*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxfilesystem.h>
#include <util/Base64Helper.h>
#include <util/unique_ptr.h>

#include <iostream>
#include <string>
#include <vector>

#include "buildversion.h"
#include "sqlauth.h"
#include "sqlbinding.h"



using namespace SCXCoreLib;
using namespace std;

static void show_usage(const char * name, bool fBrief, int exitValue);
static void show_version();

// For the getopt() function:
extern char *optarg;
extern int optind, opterr, optopt;

enum commands_t
{
    op_unknown,
    op_autoUpdate,
    op_default,
    op_delete,
    op_exit,
    op_help,
    op_print,
    op_quit,
    op_save,
    op_update
};

enum returnValues_t
{
    retOkay = 0,
    retHelpOutput,
    retParsingError,
    retCommandError,
    retInvalidArguments,
    retInvalidAuth,
    retCannotSaveAuth
};

// Keep track if we updated the authentication database

static bool sf_updatePending = false;



/**
 * Parse/process commands and return non-zero upon error
 */

bool CommandMatch(const wstring& option, const wstring command, size_t minLength)
{
    return StrIsPrefix(command, option) && option.length() >= minLength;
}

int ParseCommand(commands_t &operation, vector<wstring>& options, const wstring& line)
{
    StrTokenize(line, options);

    // Convert any parameters of "" to the empty string in the vector
    for ( vector<wstring>::iterator it = options.begin(); it != options.end(); ++it )
    {
        if ( L"\"\"" == *it )
        {
            (*it).erase();
        }
    }

    // Parse the command that we got (parse to allow minimum unique characters)
    struct
    {
        const wchar_t* command;
        int minLength;
        commands_t operation;
    } command_table[] =
      {
          { L"autoupdate",  1, op_autoUpdate },
          { L"default",     3, op_default },
          { L"delete",      3, op_delete },
          { L"exit",        1, op_exit },
          { L"help",        1, op_help },
          { L"print",       1, op_print },
          { L"quit",        4, op_quit },
          { L"save",        1, op_save },
          { L"update",      1, op_update },
          { L"",            0, op_unknown }
      };

    operation = op_unknown;
    if ( !options.empty() )
    {
        for ( int i = 0; ; ++i )
        {
            // Exit out if we didn't find our command
            if ( 0 == command_table[i].minLength )
            {
                break;
            }

            if ( CommandMatch(options[0], command_table[i].command, command_table[i].minLength) )
            {
                operation = command_table[i].operation;
                break;
            }
        }

        if ( op_unknown == operation )
        {
            wcerr << L"Error - Invalid command specified: " << options[0] << endl;
            return retCommandError;
        }
    }
    else
    {
        wcerr << L"Error - No command specified or command keyword empty" << endl;
        return retCommandError;
    }

    return retOkay;
}

bool CommandHelper_SaveAuthenticationFile(MySQL_Authentication& auth)
{
    try
    {
        auth.Save();
    }
    catch (const SCXFilePathNotFoundException& e)
    {
        wcerr << L"Error 10002: Path not found when trying to save authentication file "
              << auth.GetDefaultAuthFileName().Get() 
              << L" - refer to documentation for more details"
              << endl;
        return false;
    }
    catch (SCXException& e)
    {
        wcerr << L"Error: Unexcpected exception when trying to save authentication file: " << e.What() << endl;
        return false;
    }

    return true;
}

int CommandHandler_AutoUpdate(MySQL_Authentication& auth, const vector<wstring> command)
{
    if ( command.size() != 2 )
    {
        wcerr << L"Error - Invalid number of arguments specified: " << command.size() << endl;
        return retInvalidArguments;
    }

    if ( CommandMatch(command[1], L"true", 1) || L"1" == command[1] )
    {
        auth.AllowAutomaticUpdates(true);
    }
    else if ( CommandMatch(command[1], L"false", 1) || L"0" == command[1] )
    {
        auth.AllowAutomaticUpdates(false);
    }
    else
    {
        wcerr << L"Error - Invalid argument specified for autoupdate: \"" << command[1] << "\""<< endl;
        return retInvalidArguments;
    }

    sf_updatePending = true;
    return retOkay;
}

int CommandHandler_CommonUpdate(MySQL_Authentication& auth, const vector<wstring> command)
{
    // Validate the port
    if ( std::string::npos != command[1].find_first_not_of(L"0123456789") )
    {
        wcerr << L"Error - Invalid port specified: \"" << command[1] << L"\"" << endl;
        return retInvalidArguments;
    }

    // Save items so we have known values if not specified

    unsigned int port;
    string binding, username, password;

    port = StrToUInt( command[1] );
    binding = ( command.size() >= 3 ? StrToUTF8(command[2]) : "" );
    username = ( command.size() >= 4 ? StrToUTF8(command[3]) : "" );
    password = ( command.size() >= 5 ? StrToUTF8(command[4]) : "" );

    // Validate and act upon the b64-encoded flag
    if ( command.size() >= 6 )
    {
        if ( CommandMatch(command[5], L"true", 1) )
        {
            bool result = util::Base64Helper::Decode(password, password);
            if ( ! result )
            {
                // Base64 conversion error - return failure
                wcerr << L"Error - Invalid base64 password specified: \"" << command[4] << L"\"" << endl;
                return retInvalidArguments;
            }
        }
        else if ( CommandMatch(command[5], L"false", 1) )
        {
            // Password not Base64 encoded, but flag was specified - just ignore it
        }
        else
        {
            wcerr << L"Error - Invalid in-base64 field specified: \"" << command[5] << L"\"" << endl;
            return retInvalidArguments;
        }
    }

    // Make a copy of the Auth object, update with the change, and validate via MySQL

    util::unique_ptr<MySQL_Authentication> testAuth( new MySQL_Authentication(auth) );

    try
    {
        testAuth->AddCredentialSet(port, binding, username, password);
    }
    catch (const SCXException& e)
    {
        wcerr << L"Error - Invalid authentication: " << e.What() << endl;
        return retInvalidAuth;
    }

    if ( port )
    {
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        bool fSuccess = pBinding->AttachUsingStoredCredentials(port, testAuth);

        if ( !fSuccess )
        {
            wcerr << L"Error - Unable to log in to MySQL Server instance " << port << L": " << StrFromUTF8(pBinding->GetErrorText()) << endl;
            return retInvalidAuth;
        }
    }
    else
    {
        // Update is to the default record - loop through to validate what the default record applies to
        util::unique_ptr<MySQL_Binding> pBinding( g_pFactory->GetBinding() );
        std::vector<unsigned int> ports;
        testAuth->GetPortList(ports);

        for ( std::vector<unsigned int>::const_iterator it = ports.begin(); it != ports.end(); ++it )
        {
            MySQL_AuthenticationEntry entry;
            if ( !testAuth->GetEntry(*it, entry) )
            {
                wcerr << L"Error - entry for port " << *it << L" is incomplete and will not be validated" << endl;
                continue;
            }

            // Does anything here reference the default record?  If not, skip it.
            if ( 0 == entry.sourcedFromDefault )
            {
                continue;
            }

            // Verify this entry since it references the default record
            bool fSuccess = pBinding->AttachUsingStoredCredentials(*it, testAuth);

            if ( !fSuccess )
            {
                wcerr << L"Error - Unable to log in to MySQL Server instance " << *it << L": " << StrFromUTF8(pBinding->GetErrorText()) << endl;
                return retInvalidAuth;
            }
        }
    }

    // We passed all of our tests - update the real authentication object
    auth.AddCredentialSet(port, binding, username, password);

    sf_updatePending = true;
    return retOkay;
}

int CommandHandler_Default(MySQL_Authentication& auth, const vector<wstring> command)
{
    if ( command.size() < 2 || command.size() > 5 )
    {
        wcerr << L"Error - Invalid number of arguments specified: " << command.size() << endl;
        return retInvalidArguments;
    }

    // Insert a port # of zero (0) immediately after command to make compatible with CommonUpdate
    vector<wstring> myCommands(command);
    myCommands.insert(myCommands.begin() + 1, wstring(L"0"));

    return CommandHandler_CommonUpdate(auth, myCommands);
}

int CommandHandler_Delete(MySQL_Authentication& auth, const vector<wstring> command)
{
    if ( command.size() != 2 )
    {
        wcerr << L"Error - Invalid number of arguments specified: " << command.size() << endl;
        return retInvalidArguments;
    }

    // Validate the port
    if ( L"default" != command[1] && std::string::npos != command[1].find_first_not_of(L"0123456789") )
    {
        wcerr << L"Error - Invalid port specified: \"" << command[1] << L"\"" << endl;
        return retInvalidArguments;
    }

    unsigned int port = 0;
    if ( L"default" != command[1] )
    {
        port = StrToUInt( command[1] );
    }

    // Try to delete the credential set to see if it works
    // (If it fails, then auth object will not be updated)

    try
    {
        auth.DeleteCredentialSet(port);
    }
    catch (const SCXException& e)
    {
        wcerr << L"Error - Invalid authentication: " << e.What() << endl;
        return retInvalidAuth;
    }

    sf_updatePending = true;
    return retOkay;
}

int CommandHandler_Exit(MySQL_Authentication& auth, const vector<wstring> command)
{
    if ( command.size() != 1 )
    {
        wcerr << L"Error - Invalid number of arguments specified: " << command.size() << endl;
        return retInvalidArguments;
    }

    return ( CommandHelper_SaveAuthenticationFile(auth) ? retOkay : retCannotSaveAuth );
}

int CommandHandler_Help(MySQL_Authentication& auth, const vector<wstring> command)
{
    if ( command.size() != 1 )
    {
        wcerr << L"Error - Invalid number of arguments specified: " << command.size() << L"; extra arguments ignored" << endl << endl;
    }

    wcout << L"Help for commands to maintain MySQL Provider Authentication File:" << endl << endl
          << L"  autoupdate [true|false]" << endl
          << L"      Allow/disallow automatic updates to authentication file." << endl << endl
          << L"  default [bind-address] [username] [password] [in-base64]:" << endl
          << L"      Add or update default record to provide default information for" << endl
          << L"      port records (set via update command)." << endl
          << L"        [bind-address] is default bind address for MySQL Server" << endl
          << L"        [username] is default username for login to MySQL Server" << endl
          << L"        [password] is default password for login to MySQL Server" << endl
          << L"        [in-base64] is \"true\" or \"false\" if record pw in Base64 format" << endl
          << L"      Default record is entirely optional, and need not exist.  Specify" << endl
          << L"      an empty field as \"\"." << endl << endl
          << L"  delete [default|port#]:" << endl
          << L"      Delete default record or a port record in authentication file." << endl << endl
          << L"  exit:" << endl
          << L"      Saves changes and exits (only useful for interactive mode)." << endl << endl
          << L"  help:" << endl
          << L"      Display this help text." << endl << endl
          << L"  print:" << endl
          << L"      Print the contents of the MySQL provider authenticaiton file." << endl << endl
          << L"  quit:" << endl
          << L"      Quits interactive mode without saving changes." << endl << endl
          << L"  save:" << endl
          << L"      Save changes to disk. This is automatic for non-interactive mode." << endl << endl
          << L"  update [port#] [bind-address] [username] [password] [in-base64]:" << endl
          << L"      Add or update a port record to identify a MySQL Server instance in the" << endl
          << L"      authentication file." << endl
          << L"        [port#] is the port number for the MySQL Server instance" << endl
          << L"        [bind-address] is default bind address for MySQL Server" << endl
          << L"        [username] is default username for login to MySQL Server" << endl
          << L"        [password] is default password for login to MySQL Server" << endl
          << L"        [in-base64] is \"true\" or \"false\" if record pw in Base64 format" << endl
          << L"      Note that all information is validated by connecting to MySQL Server." << endl
          << L"      Specify an empty field as \"\"." << endl;

    return retOkay;
}

int CommandHandler_Print(MySQL_Authentication& auth, const vector<wstring> command)
{
    if ( command.size() != 1 )
    {
        wcerr << L"Error - Invalid number of arguments specified: " << command.size() << endl;
        return retInvalidArguments;
    }

    if ( auth.GetAutomaticUpdates() )
    {
        wcout << L"[Automatic Updates: Enabled]" << endl;
    }
    else
    {
        wcout << L"[Automatic Updates: DISABLED]" << endl;
    }

    MySQL_AuthenticationEntry entry;
    try {
        auth.GetEntry(0, entry);
        wcout << endl
              << L"Default Entry: " << endl
              << L"    Binding:  " << (entry.binding.size() ? StrFromUTF8(entry.binding) : L"<None>") << endl
              << L"    Username: " << (entry.username.size() ? StrFromUTF8(entry.username) : L"<None>") << endl
              << L"    Password: " << (entry.password.size() ? StrFromUTF8(entry.password) : L"<None>") << endl;
    }
    catch (MySQL_Auth::PortNotFound &e)
    {
        wcout << "[No default entry defined]" << endl;
    }

    vector<unsigned int> ports;
    auth.GetPortList(ports);

    for (vector<unsigned int>::const_iterator it = ports.begin(); it != ports.end(); ++it)
    {
        auth.GetEntry(*it, entry);
        wcout << endl
              << L"Port " << entry.port << L":" << endl
              << L"    Binding:  "
              <<   (entry.sourcedFromDefault & MySQL_AuthenticationEntry::BindingFromDefault
                    ? L"<From Default>"
                    : (entry.binding.size() ? StrFromUTF8(entry.binding) : L"<None>") ) << endl
              << L"    Username: "
              <<   (entry.sourcedFromDefault & MySQL_AuthenticationEntry::UsernameFromDefault
                    ? L"<From Default>"
                    : (entry.username.size() ? StrFromUTF8(entry.username) : L"<None>") ) << endl
              << L"    Password: "
              <<   (entry.sourcedFromDefault & MySQL_AuthenticationEntry::PasswordFromDefault
                    ? L"<From Default>"
                    : (entry.password.size() ? StrFromUTF8(entry.password) : L"<None>") ) << endl;
    }

    return retOkay;
}

int CommandHandler_Quit(MySQL_Authentication& auth, const vector<wstring> command)
{
    if ( command.size() != 1 )
    {
        wcerr << L"Error - Invalid number of arguments specified: " << command.size() << endl;
        return retInvalidArguments;
    }

    return retOkay;
}

int CommandHandler_Save(MySQL_Authentication& auth, const vector<wstring> command)
{
    if ( command.size() != 1 )
    {
        wcerr << L"Error - Invalid number of arguments specified: " << command.size() << endl;
        return retInvalidArguments;
    }

    if ( CommandHelper_SaveAuthenticationFile(auth) )
    {
        sf_updatePending = false;
        return retOkay;
    }
    else
    {
        return retCannotSaveAuth;
    }
}

int CommandHandler_Update(MySQL_Authentication& auth, const vector<wstring> command)
{
    if ( command.size() < 3 || command.size() > 6 )
    {
        wcerr << L"Error - Invalid number of arguments specified: " << command.size() << endl;
        return retInvalidArguments;
    }

    return CommandHandler_CommonUpdate(auth, command);
}

int ProcessCommand(commands_t& op, MySQL_Authentication& auth, const wstring& command)
{
    vector<wstring> options;
    int returnStatus;

    if ( 0 != (returnStatus = ParseCommand(op, options, command)) )
    {
        return returnStatus;
    }

    switch (op)
    {
        case op_autoUpdate:
            returnStatus = CommandHandler_AutoUpdate(auth, options);
            break;

        case op_default:
            returnStatus = CommandHandler_Default(auth, options);
            break;

        case op_delete:
            returnStatus = CommandHandler_Delete(auth, options);
            break;

        case op_exit:
            returnStatus = CommandHandler_Exit(auth, options);
            break;

        case op_help:
            returnStatus = CommandHandler_Help(auth, options);
            break;

        case op_print:
            returnStatus = CommandHandler_Print(auth, options);
            break;

        case op_quit:
            returnStatus = CommandHandler_Quit(auth, options);
            break;

        case op_save:
            returnStatus = CommandHandler_Save(auth, options);
            break;

        case op_update:
            returnStatus = CommandHandler_Update(auth, options);
            break;

        case op_unknown:
        default:
            wcerr << L"Internal Error - Invalid command operations code: " << op << endl;
            returnStatus = retCommandError;
    }

    return returnStatus;
}


/*----------------------------------------------------------------------------*/
/**
   main function.
*/

int main(int argc, char *argv[])
{
    int exitStatus = 0;
    bool interactive = false;
    int c;

    // If no arguments, show brief usage help
    if (1 == argc)
    {
        show_usage(argv[0], true, retHelpOutput);
    }

    // Parse the arguments
    while ((c = getopt(argc, argv, "hiv")) != -1) {
        switch(c) {
            case 'h':                   /* Show extended help information */
                show_usage(argv[0], false, retHelpOutput);
                /*NOTREACHED*/
                break;

            case 'i':                   /* Interactive (prompted) use */
                interactive = true;
                break;

            case 'v':                   /* Show version info */
                show_version();
                exit(retOkay);
                break;

            case '?':                   /* Show basic help information */
                show_usage(argv[0], true, retParsingError);
                /*NOTREACHED*/

            default:
                show_usage(argv[0], true, retParsingError);
                /*NOTREACHED*/
                break;
        }
    }

    if ( !interactive )
    {
        MySQL_Authentication auth;
        auth.Load();

        // Handle any arguments on the command line
        string parseLine;
        while (optind < argc)
        {
            parseLine += ( strlen(argv[optind]) ? argv[optind] : "\"\"" );
            if (++optind < argc)
            {
                parseLine += " ";
            }
        }

        commands_t op;
        exitStatus = ProcessCommand(op, auth, StrFromUTF8(parseLine));

        // If no error, and we actually did something useful, then save resulting dataset
        // Command "save" isn't useful from command line, but not worth stopping it ...
        if ( 0 == exitStatus && op_exit != op && op_help != op && op_print != op && op_quit != op && op_save != op)
        {
            if ( !CommandHelper_SaveAuthenticationFile(auth) )
            {
                exitStatus = retCannotSaveAuth;
            }
        }
    }
    else
    {
        commands_t op = op_unknown;
        MySQL_Authentication auth;
        auth.Load();

        // Pre-check if we'll have an obvious problem saving the authentication file
        if ( !CommandHelper_SaveAuthenticationFile(auth) )
        {
            return retCannotSaveAuth;
        }

        do {
            wstring parseLine;

            wcout << L"auth> ";
            getline( wcin, parseLine );

            exitStatus = ProcessCommand(op, auth, parseLine);
        } while ( ! (op_exit == op || op_quit == op || exitStatus == retCannotSaveAuth ) );
    }

    return exitStatus;
}

void show_usage(const char * nname, bool fBrief, int exitValue)
{
    const wstring name = StrFromUTF8(nname);

    if (fBrief)
    {
        wcerr << name << L": Try '" << name << " -h' for more information." << endl;
    }
    else
    {
        wcout << L"Usage: " << name << L"[options] [operations]" << endl
              << endl
              << L"Options:" << endl
              << L"  -h:\tDisplay detailed help information" << endl
              << L"  -i:\tInteractive use" << endl
              << L"  -v:\tDisplay version information" << endl << endl
              << L"Operations:" << endl
              << L"  autoupdate true|false" << endl
              << L"  default [bind-address] [username] [password]" << endl
              << L"  delete default|<port#>" << endl
              << L"  help" << endl
              << L"  print" << endl
              << L"  update <port#> [bind-address] [username] [password]" << endl;
    }

    exit(exitValue);
}

void show_version()
{
    wcout << L"Version: " << CIMPROV_BUILDVERSION_MAJOR << L"." << CIMPROV_BUILDVERSION_MINOR
          << L"." << CIMPROV_BUILDVERSION_PATCH << L"-" << CIMPROV_BUILDVERSION_BUILDNR
          << L" (" << CIMPROV_BUILDVERSION_STATUS << L" - " << CIMPROV_BUILDVERSION_DATE << "L)\n";

    return;
}
