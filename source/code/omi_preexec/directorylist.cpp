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

    dirList.push_back( "/var/opt/microsoft/mysql-cimprov/lib/state/" );
    dirList.push_back( "/var/opt/microsoft/mysql-cimprov/log/" );
}

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
