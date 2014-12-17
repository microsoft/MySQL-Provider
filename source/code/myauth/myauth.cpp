/*----------------------------------------------------------------------------
  Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
*/
/**
   \file       myauth.cpp

   \brief      MySQL CIM Provider Authentication File Management

   \date       12-10-2014
*/

#include <scxcorelib/scxcmn.h>

#include <iostream>

#include "buildversion.h"
#include "sqlauth.h"



using namespace SCXCoreLib;
using namespace std;

static void show_usage(const char * name, bool fBrief, int exitValue);
static void show_version();

const int EXIT_LOGIC_ERROR = 64; /* Random exit code */

// For the getopt() function:
extern char *optarg;
extern int optind, opterr, optopt;



/*----------------------------------------------------------------------------*/
/**
   main function.
*/

int main(int argc, char *argv[])
{
    int exitStatus = 0;
    int c;

    // If no arguments, show brief usage help
    if (1 == argc)
    {
        show_usage(argv[0], true, 0);
    }

    // Parse the arguments
    while ((c = getopt(argc, argv, "hiv")) != -1) {
        switch(c) {
            case 'h':                   /* Show extended help information */
                show_usage(argv[0], false, 0);
                /*NOTREACHED*/
                break;

            case 'i':                   /* Interactive (prompted) use */
                break;

            case 'v':                   /* Show version info */
                show_version();
                exit(0);
                break;

            case '?':                   /* Show basic help information */
                show_usage(argv[0], true, EXIT_LOGIC_ERROR);
                /*NOTREACHED*/

            default:
                show_usage(argv[0], true, 0);
                /*NOTREACHED*/
                break;
        }
    }

    return exitStatus;
}

void show_usage(const char * name, bool fBrief, int exitValue)
{
    if (fBrief)
    {
        cout << name << ": Try '" << name << " -h' for more information." << endl;
    }
    else
    {
        cout << "Usage: " << name << endl
             << endl
             << "Options:" << endl
             << "  -h:\tDisplay detailed help information" << endl
             << "  -i:\tInteractive use" << endl
             << "  -v:\tDisplay version information" << endl << endl
             << "Operations:" << endl
             << "  autoupdate true|false" << endl
             << "  default [bind-address] [username] [password]" << endl
             << "  delete default|<port#>" << endl
             << "  print" << endl
             << "  update <port#> [bind-address] [username] [password]" << endl << endl
             << "Optional parameters that are not to be specified should be passed with \"\"" << endl;
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
