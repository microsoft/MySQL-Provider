/*--------------------------------------------------------------------------------
 *        Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *     
 *        */
 /**
      \file        directorylist.h

      \brief       Provide list of project-specific callouts for OMI_PREEXEC program
                   (allows for common implementation to differ only by project)

      \date        11-06-14
*/
/*----------------------------------------------------------------------------*/

#ifndef DIRECTORYLIST_H
#define DIRECTORYLIST_H

#include <string>
#include <vector>

void  GetDirectoryCreationList(std::vector<std::string>& dirList);
int PreExec_NonPrived_Hook(uid_t uid, gid_t gid);
int PreExec_Prived_Hook();
int PreExec_Generic_Hook();

#endif /* DIRECTORY_LIST_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
