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
    \file        mycnf-scanner.cpp

    \brief       Scans mysql configuration to extract authentication information.

    \date        2016-06-09

*/
/*----------------------------------------------------------------------------*/

#include "mycnf-scanner.h"

namespace MySQL
{
    const std::wstring cIncludeDirKeyword = L"!includedir";
    const std::wstring cIncludeKeyword = L"!include";

    /**
     Given a line from My SQL configuration file containing an include* directive,
     this function extracts the path used in the directive.
     
     MySQL extracts the path with the following algorithm:
     Path begins at the first non-space character after the keyword. It continues till 
     the end of the line, while ignoring the trailing whitespacelast non-space character.
     (Reference: get_argument function in my_default.cc in mysql-server source)

         !include(dir)?[\s]+path[\s]*

     \param[in] file  containing the directive(used only for reporting errors).
     \param[in] line  from the config file that has already been trimmed.
     \param[in] keywordlen length of the directive.
     \returns   SCXFilePath representing the path
     \throws     MySQL_ConfigScannerException  if the line contains does not follow the syntax
     */
    static inline SCXCoreLib::SCXFilePath GetPathFromDirective(const SCXCoreLib::SCXFilePath& file, const std::wstring& line, size_t keywordLen)
    {
        if (line.size() > keywordLen)
        {
            std::wstring path = SCXCoreLib::StrTrim(line.substr(keywordLen, line.size()- keywordLen));
            if ( path.size() > 0 )
            {
                return SCXCoreLib::SCXFilePath(path);
            }
        }

        std::wstringstream ss;
        ss << L"invalid directive in file, " << file.Get() << L" : " << line;
        throw MySQL_ConfigScannerException(ss.str(), SCXSRCLOCATION);
    }

    /**
       Scan a MySQL configuration file looking for 'port' and 'bind-address'
       options, and add an entry to the given auth file for each 'port'/
       'bind-address' pair. For '!include' directive, calls itself. 
       and '!includedir' directive, LoadCnfDirectory is called.

       \param[in]  cnfFile                       path of the MySQL configuration file
       \param[in]  auth                          authentication object that has been 'Load'ed.
       \throws     SCXFilePathNotFoundException  if cnfFile (or any of the paths pointed by "!include" directives) is not found
       \throws     MySQL_ConfigScannerException  if the include directives form a cycle
    */

    void MySQL_ConfigurationScanner::LoadCnfFile(
        const SCXCoreLib::SCXFilePath& file, 
        MySQL_Authentication& auth)
    {
        SCX_LOGHYSTERICAL(m_log, SCXCoreLib::StrAppend(L"LoadCnfFile loading: ", file.Get()));
        std::pair<std::set< std::wstring >::iterator, bool> ins = m_visited.insert(file.Get());
        if (!ins.second)
        {
            std::wstringstream ss;
            ss << file.Get() << L" is used in !include more than once.";
            throw MySQL_ConfigScannerException(ss.str(), SCXSRCLOCATION);
        }

        std::vector< std::wstring > lines;
        SCXCoreLib::SCXStream::NLFs nlfs;

        m_extDepends->ReadAllLinesAsUTF8(file, lines, nlfs);

        unsigned int portNum = 0;
        std::wstring bindAddress;
        for(std::vector< std::wstring >::const_iterator iter = lines.begin(); iter != lines.end(); ++iter)
        {
            std::wstring line( SCXCoreLib::StrTrim(*iter) );
            SCX_LOGHYSTERICAL(m_log, SCXCoreLib::StrAppend(L" Line: ", line));
            if (SCXCoreLib::StrIsPrefix(line, cIncludeDirKeyword))
            {
                SCXCoreLib::SCXFilePath directory = GetPathFromDirective(file, line, cIncludeDirKeyword.length());
                LoadCnfDirectory(directory, auth);
            }
            else if(SCXCoreLib::StrIsPrefix(line, cIncludeKeyword))
            {
                SCXCoreLib::SCXFilePath incFile = GetPathFromDirective(file, line, cIncludeKeyword.length());
                LoadCnfFile(incFile, auth);
            }
            else
            {
                if ( line.size() == 0 || line[0] == L'#')
                {
                    continue;
                }

                if ( line[0] == L'[' )
                {
                    // If we currently have a port number (and maybe a binding address), save it
                    if ( portNum )
                    {
                        SCX_LOGHYSTERICAL(m_log, SCXCoreLib::StrAppend(SCXCoreLib::StrAppend(L"   Flushing port ", portNum).append(L", Bind Address: "), bindAddress));
                        auth.AddCredentialSet(portNum, SCXCoreLib::StrToUTF8(bindAddress));
                        m_ports[portNum] = bindAddress;
                    }

                    portNum = 0;
                    bindAddress = L"";

                    // Is the line of the form "[mysql]" or "[mysqlDD]" (where DD is one or more digits)?  If so, scan section.
                    if ( line == L"[mysqld]"
                         || ( SCXCoreLib::StrIsPrefix(line, L"[mysqld") && line.substr(line.size()-1) == L"]" && line.size() > 8
                              && std::string::npos == line.substr(7,line.size()-8).find_first_not_of(L"0123456789") ) )
                    {
                        SCX_LOGHYSTERICAL(m_log, L"   New Section, scanning ...");

                        // Starting new section - set defaults
                        portNum = 3306;
                        bindAddress = L"127.0.0.1";
                    }
                    continue;
                }

                std::vector<std::wstring> elements;
                SCXCoreLib::StrTokenize(line, elements, L"=");
                if ( elements.size() != 2 )
                {
                    // Not a line that we care about
                    continue;
                }

                // Check for a port declaration (port = xxx)
                if ( 0 == SCXCoreLib::StrCompare(L"port", elements[0], true) )
                {
                    SCX_LOGHYSTERICAL(m_log, SCXCoreLib::StrAppend(L"   Found Port: ", elements[1]));
                    portNum = SCXCoreLib::StrToUInt( elements[1] );
                }

                // Check for a bind-address declaration (bind-address = 172.0.0.1)
                if ( 0 == SCXCoreLib::StrCompare(L"bind-address", elements[0], true) )
                {
                    SCX_LOGHYSTERICAL(m_log, SCXCoreLib::StrAppend(L"   Found bind-address: ", elements[1]));
                    bindAddress = elements[1];
                }
            }

            if ( portNum )
            {
                SCX_LOGHYSTERICAL(m_log, SCXCoreLib::StrAppend(SCXCoreLib::StrAppend(L"   Flushing port ", portNum).append(L", Bind Address: "), bindAddress));

                auth.AddCredentialSet(portNum, SCXCoreLib::StrToUTF8(bindAddress));
                m_ports[portNum] = bindAddress;
            }
        }
    }

    /**
       call LoadCnfFile on each ".cnf" file present in the given directory.

       \param[in]  directory                     path of the MySQL configuration file
       \param[in]  auth                          authentication object that has been 'Load'ed.
       \throws     SCXFilePathNotFoundException  if directory is not found
    */
    void MySQL_ConfigurationScanner:: LoadCnfDirectory(
        const SCXCoreLib::SCXFilePath& directory, 
        MySQL_Authentication& auth)
    {
        SCX_LOGHYSTERICAL(m_log, SCXCoreLib::StrAppend(L"LoadCnfFilesFromDirectory loading:", directory.Get()));
        std::vector< SCXCoreLib::SCXFilePath > cnfFiles = m_extDepends->GetFiles(directory);

        for( std::vector< SCXCoreLib::SCXFilePath >::const_iterator iter = cnfFiles.begin(); iter != cnfFiles.end(); ++iter)
        {
            if (SCXCoreLib::SCXDirectory::Exists(*iter))
            {
                // ignore directories
                continue;
            }

            std::wstring fileSuffix = iter->GetFilesuffix();
            if (fileSuffix == L"cnf")
            {
                LoadCnfFile(*iter, auth);
            }
            else
            {
                SCX_LOGHYSTERICAL(m_log,SCXCoreLib::StrAppend(iter->Get(), L" is not a cnf file"));
            }
        }
    }

    /**
       Parse a MySQL configuration file looking for 'port' and 'bind-address'
       options, and add an entry to the given auth file for each 'port'/
       'bind-address' pair.
       '!include' and '!includedir' directives are honored.

       \param[in]  cnfFile                       path of the MySQL configuration file
       \param[in]  auth                          authentication object that has been 'Load'ed.
       \throws     SCXFilePathNotFoundException  if cnfFile (or any of the paths pointed by "!include" directives) is not found
       \throws     MySQL_ConfigScannerException  if the include directives form a cycle
    */
    void MySQL_ConfigurationScanner::Scan(const SCXCoreLib::SCXFilePath& cnfFile, MySQL_Authentication& auth)
    {
        m_visited.clear();
        m_ports.clear();
        LoadCnfFile(cnfFile, auth);

        std::vector<unsigned int> authPorts;
        auth.GetPortList( authPorts );

        // We've added what must be added, but we need to delete unreferenced ports
        // Loop through authentication ports and remove anything we didn't read from configuration
        for (std::vector<unsigned int>::const_iterator it = authPorts.begin(); it != authPorts.end(); ++it)
        {
            if ( m_ports.count(*it) == 0 )
            {
                SCX_LOGHYSTERICAL(m_log, SCXCoreLib::StrAppend(L"Deleting port: ", *it));
                auth.DeleteCredentialSet(*it);
            }
        }
    }
}
