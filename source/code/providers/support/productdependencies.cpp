/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
*/
/**
    \file        productdependencies.cpp

    \brief       Implements the product-specific dependencies for SCXCore

    \date        2013-02-26 13:38:00
*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/stringaid.h>
#include <scxcorelib/scxprocess.h>
#include <scxcorelib/scxproductdependencies.h>
#include <scxsystemlib/scxproductdependencies.h>

#if !defined(WIN32)
#include "buildversion.h"
#endif

namespace SCXCoreLib
{
    namespace SCXProductDependencies
    {
        void WriteLogFileHeader( SCXHandle<std::wfstream> &stream, int logFileRunningNumber, SCXCalendarTime& procStartTimestamp )
        {
            std::wstringstream continuationLogMsg;
            if ( logFileRunningNumber > 1 )
            {
                continuationLogMsg << L"* Log file number: " << StrFrom(logFileRunningNumber) << std::endl;
            }

            (*stream) << L"*" << std::endl
                      << L"* Microsoft System Center Cross Platform MySQL Extensions" << std::endl
#if !defined(WIN32)
                      << L"* Build number: " << CIMPROV_BUILDVERSION_MAJOR << L"." << CIMPROV_BUILDVERSION_MINOR << L"."
                      << CIMPROV_BUILDVERSION_PATCH << L"-" << CIMPROV_BUILDVERSION_BUILDNR << L" "
                      << CIMPROV_BUILDVERSION_STATUS << std::endl
#endif
                      << L"* Process id: " << StrFrom(SCXProcess::GetCurrentProcessID()) << std::endl
                      << L"* Process started: " << procStartTimestamp.ToExtendedISO8601() << std::endl
                      << continuationLogMsg.str() 
                      << L"*" << std::endl
                      << L"* Log format: <date> <severity>     [<code module>:<line number>:<process id>:<thread id>] <message>" << std::endl
                      << L"*" << std::endl;
        }

        void WrtieItemToLog( SCXHandle<std::wfstream> &stream, const SCXLogItem& item, const std::wstring& message )
        {
            (void) item;

            (*stream) << message << std::endl;
        }
    }
}

namespace SCXSystemLib
{
    namespace SCXProductDependencies
    {
        std::wstring GetLinuxOS_ScriptPath()
        {
            return std::wstring(L"");
        }

        std::wstring GetLinuxOS_ReleasePath()
        {
            return std::wstring(L"");
        }

        void Disk_IgnoredFileSystems( std::set<std::wstring> &igfs )
        {
            // To suppress compiler warnings about parameter not being used
            (void)igfs;
            return;
        }

        void Disk_IgnoredFileSystems_StartsWith( std::set<std::wstring> &igfs )
        {
            // To suppress compiler warnings about parameter not being used
            (void)igfs;
            return;
        }

        void Disk_IgnoredFileSystems_Contains( std::set<std::wstring> &igfs )
        {
            (void)igfs;
            return;
        }

        void Disk_IgnoredFileSystems_NoLinkToPhysical( std::set<std::wstring> &igfs )
        {
            (void)igfs;
            return;
        }
    }
}
