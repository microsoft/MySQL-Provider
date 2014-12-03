/*--------------------------------------------------------------------------------
 *        Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *     
 *        */
 /**
      \file        omi-preexec.h

      \brief       Provide list of project-specific callouts for OMI_PREEXEC program
                   (allows for common implementation to differ only by project)

      \date        11-06-14
*/
/*----------------------------------------------------------------------------*/

#ifndef OMI_PREXEC_H
#define OMI_PREXEC_H

#include <sys/types.h>

#include <string>
#include <vector>

class PreExecution
{
public:
    void GetDirectoryCreationList(std::vector<std::string>& dirList);
    int NonPrived_Hook(uid_t uid, gid_t gid);
    int Prived_Hook(uid_t uid, gid_t gid);
    int Generic_Hook(uid_t uid, gid_t gid);

    int _createDir(const std::string baseDir, uid_t uid, gid_t gid);
};

#endif /* OMI_PREEXEC_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
