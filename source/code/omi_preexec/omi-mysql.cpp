/*--------------------------------------------------------------------------------
 *        Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *      
 *           */
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
#include "omi-preexec.h"
#include "sqlauth.h"

#include <iostream>
#include <string>


using namespace SCXCoreLib;

static int MySQL_ConfigurationParser(uid_t uid, gid_t gid, const std::wstring cnfFile)
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

    SCX_LOGHYSTERICAL(hLog, StrAppend(L"Parsing MySQL configuration file: ", cnfFile));

    std::vector<std::wstring> lines;
    try
    {
        SCXStream::NLFs nlfs;
        SCXFile::ReadAllLines(cnfFile, lines, nlfs );
    }
    catch (const SCXException& e)
    {
        SCX_LOGERROR(hLog, StrAppend(L"Error reading configuration file: ", e.What()));
        return -1;
    }

    std::map<unsigned int,std::wstring> ports;
    unsigned int portNum = 0;
    std::wstring bindAddress;

    for (std::vector<std::wstring>::const_iterator it = lines.begin(); it != lines.end(); ++it)
    {
        std::wstring line( StrTrim(*it) );
        SCX_LOGHYSTERICAL(hLog, StrAppend(L" Line: ", line));
        if ( line.size() == 0 || line[0] == L'#')
        {
            continue;
        }

        // Does this line start with "[" (new section in file)?  If so, flush and reset.
        if ( line[0] == L'[' )
        {
            // If we currently have a port number (and maybe a binding address), save it
            if ( portNum )
            {
                SCX_LOGHYSTERICAL(hLog, StrAppend(StrAppend(L"   Flushing port ", portNum).append(L", Bind Address: "), bindAddress));

                auth.AddCredentialSet(portNum, StrToUTF8(bindAddress));
                ports[portNum] = bindAddress;
            }

            portNum = 0;
            bindAddress = L"";

            // Is the line of the form "[mysql]" or "[mysqlDD]" (where DD is one or more digits)?  If so, scan section.
            if ( line == L"[mysqld]"
                 || ( StrIsPrefix(line, L"[mysqld") && line.substr(line.size()-1) == L"]" && line.size() > 8
                      && std::string::npos == line.substr(7,line.size()-8).find_first_not_of(L"0123456789") ) )
            {
                SCX_LOGHYSTERICAL(hLog, L"   New Section, scanning ...");

                // Starting new section - set defaults
                portNum = 3306;
                bindAddress = L"127.0.0.1";
            }

            continue;
        }

        std::vector<std::wstring> elements;
        StrTokenize(line, elements, L"=");
        if ( elements.size() != 2 )
        {
            // Not a line that we care about
            continue;
        }

        // Check for a port declaration (port = xxx)
        if ( 0 == StrCompare(L"port", elements[0], true) )
        {
            SCX_LOGHYSTERICAL(hLog, StrAppend(L"   Found Port: ", elements[1]));
            portNum = StrToUInt( elements[1] );
        }

        // Check for a bind-address declaration (bind-address = 172.0.0.1)
        if ( 0 == StrCompare(L"bind-address", elements[0], true) )
        {
            SCX_LOGHYSTERICAL(hLog, StrAppend(L"   Found bind-address: ", elements[1]));
            bindAddress = elements[1];
        }
    }

    if ( portNum )
    {
        SCX_LOGHYSTERICAL(hLog, StrAppend(StrAppend(L"   Flushing port ", portNum).append(L", Bind Address: "), bindAddress));

        auth.AddCredentialSet(portNum, StrToUTF8(bindAddress));
        ports[portNum] = bindAddress;
    }

    // We've added what must be added, but we need to delete unreferenced ports
    // (Loop through authentication ports and remove anything we didn't read from configuration

    std::vector<unsigned int> authPorts;
    auth.GetPortList( authPorts );
    for (std::vector<unsigned int>::const_iterator it = authPorts.begin(); it != authPorts.end(); ++it)
    {
        if ( ports.count(*it) == 0 )
        {
            SCX_LOGHYSTERICAL(hLog, StrAppend(L"Deleting port: ", *it));
            auth.DeleteCredentialSet(*it);
        }
    }

    SCX_LOGHYSTERICAL(hLog, L"Saving MySQL authentication");
    auth.Save();

    SCX_LOGHYSTERICAL(hLog, StrAppend(L"Successfully parsed file: ", cnfFile));

    return rc;
}

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
