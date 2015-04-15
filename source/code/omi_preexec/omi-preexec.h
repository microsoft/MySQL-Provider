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
    /*----------------------------------------------------------------------------*/
    /**
       Return vector of directories where named directory (based on UID) should
       be created. If this capability is not desired, return empty vector.

       NOTE: Each directory returned should contain trailing '/' character.

       \param[out] dirList  List of directories to create named directory within

    */
    void GetDirectoryCreationList(std::vector<std::string>& dirList);

    /*----------------------------------------------------------------------------*/
    /**
       Hook to execute for non-privileged users (uid != 0).

       \param[in]  uid      User identifier for the user
       \param[in]  gid      Group identifier for the user
       \returns    Implementation-specific value

    */
    int NonPrived_Hook(uid_t uid, gid_t gid);

    /*----------------------------------------------------------------------------*/
    /**
       Hook to execute for privileged users (uid == 0).

       \param[in]  uid      User identifier for the user
       \param[in]  gid      Group identifier for the user
       \returns    Implementation-specific value

    */
    int Prived_Hook(uid_t uid, gid_t gid);

    /*----------------------------------------------------------------------------*/
    /**
       Hook to execute regardless of value of 'uid' parameter

       \param[in]  uid      User identifier for the user
       \param[in]  gid      Group identifier for the user
       \returns    Implementation-specific value

    */
    int Generic_Hook(uid_t uid, gid_t gid);

    int _createDir(const std::string baseDir, uid_t uid, gid_t gid);
};

#endif /* OMI_PREEXEC_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
