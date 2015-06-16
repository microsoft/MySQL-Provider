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
