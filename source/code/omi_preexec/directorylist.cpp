/*--------------------------------------------------------------------------------
 *        Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *      
 *           */
 /**
        \file        directorylist.cpp

        \brief       Supplies list of directories to create for OMI_PREEXEC program

        \date        10-28-14
*/
/*----------------------------------------------------------------------------*/

#include "directorylist.h"

void  GetDirectoryCreationList(std::vector<std::string>& dirList)
{
    dirList.clear();

    dirList.push_back( "/var/opt/microsoft/mysql-cimprov/auth/" );
    dirList.push_back( "/var/opt/microsoft/mysql-cimprov/log/" );
}

int PreExec_NonPrived_Hook(uid_t uid, gid_t gid)
{
    return 0;
}

int PreExec_Prived_Hook()
{
    return 0;
}

int PreExec_Generic_Hook()
{
    return 0;
}

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
