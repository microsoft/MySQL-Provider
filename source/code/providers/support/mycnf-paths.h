/*------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
*/
/**
    \file      mycnf-paths.h

    \brief     Declaration for fetching the MySQL Configuration File Paths

    \date      12-02-2014 11:31:00
*/
/*----------------------------------------------------------------------------*/

#include <string>
#include <vector>

#ifndef MYCNF_PATHS_H
#define MYCNF_PATHS_H

namespace MySQL
{
    /**
        Return a list of potential locations for MySQL configuration file.

        Note: This list should be returned in "priority" order (i.e. in order
        of what to check first, what to check next, etc). When looking at the
        various MySQL configuration files, the first path we find "wins".

        \param[out] paths List of MySQL server configuration paths (absolute paths)

    */
    void GetConfigurationFilePaths( std::vector<std::string>& paths );
}

#endif /* MYCNF_PATHS_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
