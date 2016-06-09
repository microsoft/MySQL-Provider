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
 /**
        \file        omi-mysql.cpp

        \brief       Supplies dependencies for the MySQL provider (for OMI_PREEXEC)

        \date        10-28-14
*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/scxfile.h>
#include <scxcorelib/scxlog.h>
#include <scxcorelib/stringaid.h>

#include "mycnf-paths.h"
#include "mycnf-scanner.h"
#include "omi-preexec.h"
#include "sqlauth.h"

#include <iostream>
#include <string>


using namespace SCXCoreLib;

/*----------------------------------------------------------------------------*/
/**
   Parse a MySQL configuration file looking for 'port' and 'bind-address'
   options, and add an entry to the provider auth file for each 'port'/
   'bind-address' pair.

   Note: If automatic updates are disabled in authentication file, then just
   exit without doing any parsing.

   \param[in]  uid      User identifier for the user
   \param[in]  gid      Group identifier for the user
   \returns    Zero on success, non-zero on error

*/
static int MySQL_ConfigurationParser(uid_t uid, gid_t gid, const std::wstring& cnfFile)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.omi-preexec");
    int rc = 0;

    MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_AuthenticationDependencies()), uid, gid );
    SCX_LOGHYSTERICAL(hLog, L"Loading MySQL authentication file");
    auth.Load();
    if ( ! auth.GetAutomaticUpdates() )
    {
        SCX_LOGHYSTERICAL(hLog, L"MySQL authentication has disallowed automatic updates");
        return 0;
    }

    SCX_LOGHYSTERICAL(hLog, StrAppend(L"Loading MySQL configuration file: ", cnfFile));

    MySQL::MySQL_ConfigurationScanner configScanner;
    try
    {
        configScanner.Scan(cnfFile, auth);
    }
    catch (const SCXException& e)
    {
        SCX_LOGERROR(hLog, StrAppend(L"Error reading configuration file: ", e.What()));
        return -1;
    }

    SCX_LOGHYSTERICAL(hLog, L"Saving MySQL authentication");
    auth.Save();

    SCX_LOGHYSTERICAL(hLog, StrAppend(L"Successfully parsed file: ", cnfFile));
    return rc;
}

/*----------------------------------------------------------------------------*/
/**
   Find a MySQL configuraiton file. For first configuration file found,
   parse it to populate provider authentication file.

   \param[in]  uid      User identifier for the user
   \param[in]  gid      Group identifier for the user
   \returns    Zero on success, non-zero on error

*/
static int MySQL_ConfigurationFinder(uid_t uid, gid_t gid)
{
    SCXLogHandle hLog = SCXLogHandleFactory::GetLogHandle(L"mysql.omi-preexec");

    std::vector<std::string> paths;
    MySQL::GetConfigurationFilePaths( paths );

    int rc = 0;
    for (std::vector<std::string>::const_iterator it = paths.begin(); it != paths.end(); ++it)
    {
        const std::wstring configFile( StrFromUTF8(*it) );
        if ( ! SCXFile::Exists(SCXFilePath(configFile)) )
        {
            SCX_LOGHYSTERICAL(hLog, StrAppend(L"Skipping configuration file: ", StrFromUTF8(*it)));
            continue;
        }

        // We found a MySQL configuration file; parse it and build up our authentication

        if ( 0 != (rc = MySQL_ConfigurationParser(uid, gid, configFile)) )
        {
            SCX_LOGHYSTERICAL(hLog, L"Parser returned failure!");
            return rc;
        }

        break;
    }

    return rc;
}

//
// Hooks for OMI pre-execution calls
//

void PreExecution::GetDirectoryCreationList(std::vector<std::string>& dirList)
{
    dirList.clear();

    dirList.push_back( "/var/opt/microsoft/mysql-cimprov/auth/" );
    dirList.push_back( "/var/opt/microsoft/mysql-cimprov/log/" );
}

int PreExecution::NonPrived_Hook(uid_t uid, gid_t gid)
{
    return 0;
}

int PreExecution::Prived_Hook(uid_t uid, gid_t gid)
{
    return 0;
}

int PreExecution::Generic_Hook(uid_t uid, gid_t gid)
{
    return  MySQL_ConfigurationFinder(uid, gid);
}

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
