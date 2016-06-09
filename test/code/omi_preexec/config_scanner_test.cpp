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
/*--------------------------------------------------------------------------------

    Created date    2016-06-09 08:31:00

    MySQL Config file loading unit tests.

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/scxfile.h>
#include <scxcorelib/stringaid.h>
#include <testutils/scxunit.h>
#include <testutils/providertestutils.h>

#include <iostream> // for cout
#include <vector>
#include <map>

#include "mycnf-scanner.h"

using namespace SCXCoreLib;

class MySQL_ConfigScannerDependencies : public MySQL::MySQL_CnfScannerDependency
{
public:

    MySQL_ConfigScannerDependencies(const std::wstring& prefix) : m_prefix(prefix) {}
    /**
       Finds the paths of file system objects in a specified directory.

       \param[in] path	   Path to directory.

       \returns vector containing the files in the directory identified by prefix/path/

       \throws SCXFilePathNotFoundException if path is not found.
    */
    virtual std::vector< SCXCoreLib::SCXFilePath >  GetFiles(const SCXCoreLib::SCXFilePath& path)
    {
        SCXCoreLib::SCXFilePath fullPath = GetFullPath(path);
        return SCXCoreLib::SCXDirectory::GetFileSystemEntries(fullPath, SCXCoreLib::eDirSearchOptionFile) ;
    }

    /**
       Reads as many lines of the UT8 encoded file at the specified position
       in the file system as possible.

       Handles newline symbols in a platform independent way, that is, may
       be used to read a stream originating on one platform on another platform.
       If the lines is to be written back to the originating system
       the same nlf should in general be used, if we do not have other information.

       \param[in]  source  Position of the file in the filesystem
       \param[inout]  lines   Lines that were read from the file identified by the path, prefix/source
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
        SCXCoreLib::SCXFilePath fullPath;
        if (SCXCoreLib::StrIsPrefix(source.Get(), L"cnfs/"))
        {
            fullPath = source.Get();
        }
        else
        {
            fullPath = GetFullPath(source);
        }

        if (!SCXCoreLib::SCXFile::Exists(fullPath))
        {
            throw SCXCoreLib::SCXFilePathNotFoundException(fullPath.Get(), SCXSRCLOCATION);
        }

        SCXCoreLib::SCXFile::ReadAllLinesAsUTF8(fullPath, lines, nlfs);
    }


private:
    SCXCoreLib::SCXFilePath GetFullPath(const SCXCoreLib::SCXFilePath &path)
    {
        std::wstringstream os;
        os << m_prefix << path.Get();
        SCXCoreLib::SCXFilePath fullPath = os.str();
        return fullPath;
    }

    std::wstring m_prefix;
};

class MySQL_ScannerTestAuthenticationDependencies : public MySQL_AuthenticationDependencies
{
public:
    virtual SCXCoreLib::SCXFilePath GetDefaultAuthFileName(uid_t /* uid */) const
    {
        return L"./does-not-exist.cnf";
    }

    virtual bool Force_AutoUpdate_Flag() { return true; }
};

class ConfigScanner_Test : public CPPUNIT_NS::TestFixture
{
    CPPUNIT_TEST_SUITE( ConfigScanner_Test );

    CPPUNIT_TEST( testCnfScan_RHELCnf_Success );
    CPPUNIT_TEST( testCnfScan_SLESCnf_Success );
    CPPUNIT_TEST( testCnfScan_CnfWithIncludeFileDirective_Success );
    CPPUNIT_TEST( testCnfScan_UbuntuCnf_Success );
    CPPUNIT_TEST( testCnfScan_DirectivesFormHierarchy_Success );
    CPPUNIT_TEST( testCnfScan_CnfWithIncludeFileIncludesItself_Throws );
    CPPUNIT_TEST( testCnfScan_IncludeDirsFormLoop_Throws );
    CPPUNIT_TEST( testCnfScan_CnfFileMissingIncludeDir_Throws );
    CPPUNIT_TEST( testCnfScan_CnfFileMissingInclude_Throws );
    CPPUNIT_TEST( testCnfScan_InvalidIncludeDir_Throws );
    CPPUNIT_TEST( testCnfScan_InvalidInclude_Throws );

    CPPUNIT_TEST_SUITE_END();

private:

public:
    void setUp(void)
    {
    }

    void tearDown(void)
    {
    }

    void ValidateAuth(std::map< unsigned int, std::string >& expected, MySQL_Authentication& auth)
    {
        std::vector<unsigned int> authPorts;
        auth.GetPortList( authPorts );
        CPPUNIT_ASSERT_EQUAL(expected.size(), authPorts.size());
        for (std::vector<unsigned int>::const_iterator it = authPorts.begin(); it != authPorts.end(); ++it)
        {
            MySQL_AuthenticationEntry authEntry;
            auth.GetEntry(*it, authEntry);
            CPPUNIT_ASSERT_EQUAL(expected[authEntry.port], authEntry.binding);
        }
    }

    void testCnfScan_RHELCnf_Success()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();

        std::map< unsigned int, std::string > portBindingMap;
        portBindingMap[3306] = "127.0.0.1";

        const std::wstring prefix = L"cnfs/vendor/rhel_7.2";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        scanner.Scan(L"/etc/mysql/my.cnf", auth);
        ValidateAuth(portBindingMap, auth);
    }

    void testCnfScan_SLESCnf_Success()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();

        std::map< unsigned int, std::string > portBindingMap;
        portBindingMap[3306] = "127.0.0.1";

        const std::wstring prefix = L"cnfs/vendor/sles_11.04";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        scanner.Scan(L"/etc/mysql/my.cnf", auth);
        ValidateAuth(portBindingMap, auth);
    }

    void testCnfScan_UbuntuCnf_Success()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();

        std::map< unsigned int, std::string > portBindingMap;
        portBindingMap[3306] = "127.0.0.1";

        const std::wstring prefix = L"cnfs/vendor/ubuntu_16.04";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        scanner.Scan(L"/etc/mysql/my.cnf", auth);
        ValidateAuth(portBindingMap, auth);
    }

    void testCnfScan_CnfWithIncludeFileDirective_Success()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();

        std::map< unsigned int, std::string > portBindingMap;
        portBindingMap[3507] =  "172.127.217.712"; // from cnfs/include-file-test.cnf
        portBindingMap[4301] =  "198.199.210.201"; // from cnfs/include-file-test.cnf
        portBindingMap[3306] = "127.0.0.1"; // from included file

        const std::wstring prefix = L"cnfs/derived";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        scanner.Scan(L"/include-file-test.cnf", auth);
        ValidateAuth(portBindingMap, auth);
    }

    void testCnfScan_DirectivesFormHierarchy_Success ()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();
        std::map< unsigned int, std::string > portBindingMap;
        portBindingMap[4301] = "198.199.210.201"; // From cnfs/include-dir-test.cnf
        portBindingMap[5508] = "187.0.2.1"; // from cnfs/threelevels/mysql.conf.d/mysqld.cnf
        portBindingMap[3507] = "172.127.217.712"; // from cnfs/include-dir-test.cnf
        portBindingMap[3306] = "127.0.0.1"; // from cnfs/debian/mysql.conf.d/mysqld.cnf

        const std::wstring prefix = L"cnfs/derived";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        scanner.Scan(L"/include-dir-test.cnf", auth);
        ValidateAuth(portBindingMap, auth);
    }

    void testCnfScan_CnfWithIncludeFileIncludesItself_Throws()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();

        const std::wstring prefix = L"cnfs/derived";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        CPPUNIT_ASSERT_THROW(scanner.Scan(L"/include-file-recursive.cnf", auth), MySQL::MySQL_ConfigScannerException);
    }

    void testCnfScan_IncludeDirsFormLoop_Throws()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();

        const std::wstring prefix = L"cnfs/derived";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        CPPUNIT_ASSERT_THROW(scanner.Scan(L"/include-dir-recursive.cnf", auth), MySQL::MySQL_ConfigScannerException);
    }

    void testCnfScan_CnfFileMissingIncludeDir_Throws()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();
        const std::wstring prefix = L"cnfs/derived";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        CPPUNIT_ASSERT_THROW(scanner.Scan(L"/includedir-notexisting.cnf", auth), SCXCoreLib::SCXFilePathNotFoundException);
    }

    void testCnfScan_CnfFileMissingInclude_Throws()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();

        const std::wstring prefix = L"cnfs/derived";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        CPPUNIT_ASSERT_THROW(scanner.Scan(L"/include-notexisting.cnf", auth), SCXCoreLib::SCXFilePathNotFoundException);
    }

    void testCnfScan_InvalidIncludeDir_Throws ()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();

        const std::wstring prefix = L"cnfs/derived";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        CPPUNIT_ASSERT_THROW(scanner.Scan(L"/invalid-includedir.cnf", auth), MySQL::MySQL_ConfigScannerException);
    }

    void testCnfScan_InvalidInclude_Throws ()
    {
        MySQL_Authentication auth( SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_ScannerTestAuthenticationDependencies()));
        auth.Load();

        const std::wstring prefix = L"cnfs/derived";
        MySQL::MySQL_ConfigurationScanner scanner(SCXHandle<MySQL::MySQL_CnfScannerDependency>(new MySQL_ConfigScannerDependencies(prefix)));
        CPPUNIT_ASSERT_THROW(scanner.Scan(L"/invalid-includefile.cnf", auth), MySQL::MySQL_ConfigScannerException);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION( ConfigScanner_Test );
