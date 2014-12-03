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
    void GetConfigurationFilePaths( std::vector<std::string>& paths );
}

#endif /* MYCNF_PATHS_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
