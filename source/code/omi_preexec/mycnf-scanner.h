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
        \file        mycnf-scanner.h

        \brief       Parses MySQL configuration files to extract authentication info.

        \date        06-09-16
*/
/*----------------------------------------------------------------------------*/

#ifndef MYCNF_SCANNER_H
#define MYCNF_SCANNER_H
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

#include <scxcorelib/scxdirectoryinfo.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/scxfile.h>
#include <scxcorelib/scxlog.h>
#include <scxcorelib/stringaid.h>

#include "sqlauth.h"

namespace MySQL  {

    /**
       This exception class is used to indicate that a given MySQL config
       file could not be scanned
     */
    class MySQL_ConfigScannerException: public SCXCoreLib::SCXException
    {
    public:
        /**
           Ctor
           \param[in] reason Description of scanner error
           \param[in] l      Source code location object

        */
         MySQL_ConfigScannerException(const std::wstring& reason, const SCXCoreLib::SCXCodeLocation& l)
            : SCXCoreLib::SCXException(l), m_Reason(reason)
        { }
        
        std::wstring What() const {
            return m_Reason;
        }

    protected:
        //! Description of internal error
        std::wstring   m_Reason;

    };

   /**
      MySQL Configuration Scanner dependencies class

      Allows overriding for unit test purposes
   */
    class MySQL_CnfScannerDependency
    {
    public:
        //! Ctor
        MySQL_CnfScannerDependency() { }
        //! Dtor
        virtual ~MySQL_CnfScannerDependency() {}
        
        /**
       Finds the paths of file system objects in a specified directory.
       
       \param[in] path	   Path to directory.
       
       \returns vector containing the files in this directory
       
       \throws SCXFilePathNotFoundException if path is not found.
        */
        virtual std::vector< SCXCoreLib::SCXFilePath >  GetFiles(const SCXCoreLib::SCXFilePath& path)
        {
            return SCXCoreLib::SCXDirectory::GetFileSystemEntries(path, SCXCoreLib::eDirSearchOptionFile) ;
        }

        /**
           Reads as many lines of the UT8 encoded file at the specified position
           in the file system as possible.
           
           Handles newline symbols in a platform independent way, that is, may
           be used to read a stream originating on one platform on another platform.
           If the lines is to be written back to the originating system
           the same nlf should in general be used, if we do not have other information.

           \param[in]  source  Position of the file in the filesystem
           \param[in]  lines   Lines that was read
           \param[out] nlfs	  Newline symbols found used in the file
           \throws SCXUnauthorizedFileSystemAccessException
           \throws SCXLineStreamPartialReadException	 Line too long to be stored in a wstring
           \throws SCXLineStreamContentException	 Invalid byte sequence according to UTF8
           \throws SCXFilePathNotFoundException if source is not found
        */
        virtual void ReadAllLinesAsUTF8(
            const SCXCoreLib::SCXFilePath & source,
            std::vector< std::wstring >   & lines,
            SCXCoreLib::SCXStream::NLFs   & nlfs)
        {
            if (!SCXCoreLib::SCXFile::Exists(source))
            {
                throw SCXCoreLib::SCXFilePathNotFoundException(source.Get(), SCXSRCLOCATION);
            }

            SCXCoreLib::SCXFile::ReadAllLinesAsUTF8(source, lines, nlfs);
        }

    private:
    };

   /**
   MySQL Configuration Scanner Class

   Scans the given config file and updates the auth with port and corresponding binding address
   */
   class MySQL_ConfigurationScanner
   {
   public:

       MySQL_ConfigurationScanner()
           : m_extDepends(new MySQL_CnfScannerDependency()),
             m_log(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.configurationscanner"))
       {
       }

       MySQL_ConfigurationScanner(SCXCoreLib::SCXHandle< MySQL_CnfScannerDependency > extDepends)
           : m_extDepends(extDepends),
             m_log(SCXCoreLib::SCXLogHandleFactory::GetLogHandle(L"mysql.configurationscanner"))
       {
       }

       void Scan(const SCXCoreLib::SCXFilePath& cnfFile, MySQL_Authentication& auth);

   private:
       void LoadCnfFile (const SCXCoreLib::SCXFilePath& file, MySQL_Authentication& auth);
       void LoadCnfDirectory (const SCXCoreLib::SCXFilePath& directoryName,  MySQL_Authentication& auth);

       SCXCoreLib::SCXHandle< MySQL_CnfScannerDependency > m_extDepends;
       SCXCoreLib::SCXLogHandle m_log;
       std::set< std::wstring > m_visited; 
       std::map<unsigned int, std::wstring> m_ports;
   };
}
#endif
