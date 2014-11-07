/*--------------------------------------------------------------------------------
 *        Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *     
 *        */
 /**
      \file        directorylist.h

      \brief       Provide list of directories for OMI_PREEXEC program
                   (allows for common implementation to differ only by directory list)

      \date        11-06-14
*/
/*----------------------------------------------------------------------------*/

#ifndef DIRECTORYLIST_H
#define DIRECTORYLIST_H

#include <string>
#include <vector>

void  GetDirectoryCreationList(std::vector<std::string>& dirList);

#endif /* DIRECTORY_LIST_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
