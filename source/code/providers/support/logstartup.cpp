/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.
    
*/
/**
    \file        

    \brief       Initializes logging for the MySQL provider

    \date        2014-11-05 16:22:00

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxlog.h>

namespace MySQL
{
    /*----------------------------------------------------------------------------*/
    /**
       Log the startup message once regardless of how many times called
       
       This function will be called from all provider ctors except RunAs to 
       provide one initial log, regardless of how many times called.
       
    */

    void LogStartup(void) 
    {
        static bool bLoggedInitMessage = false;
        if (!bLoggedInitMessage) 
        {
            SCXCoreLib::SCXLogHandle log = SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.provider");
            SCX_LOGINFO(log, L"MySQL Provider Module loaded");
            
            bLoggedInitMessage = true;
        }
    }
}

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
