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
