/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.
    
*/
/**
    \file        mycnf-paths.cpp

    \brief       Declares fixed MySQL Configuraiton File Paths

    \date        2014-11-05 16:22:00

*/
/*----------------------------------------------------------------------------*/

#include "mycnf-paths.h"

namespace MySQL
{
    void GetConfigurationFilePaths( std::vector<std::string>& paths )
    {
        paths.clear();
        paths.push_back( "/etc/my.cnf" );
        paths.push_back( "/etc/mysql/my.cnf" );
        paths.push_back( "/var/lib/mysql/my.cnf" );
        paths.push_back( "/usr/local/mysql/data/my.cnf" );
        paths.push_back( "/usr/local/var/my.cnf" );

        return;
    }
}

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
