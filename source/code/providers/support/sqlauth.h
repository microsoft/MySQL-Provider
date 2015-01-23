/*--------------------------------------------------------------------------------
 *        Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *     
 *        */
 /**
      \file        sqlbinding.h

      \brief       MySQL authentication handling for MySQL provider

      \date        11-13-14
*/
/*----------------------------------------------------------------------------*/

#ifndef SQLAUTHENTICATION_H
#define SQLAUTHENTICATION_H

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxconfigfile.h>
#include <scxcorelib/scxexception.h>
#include <scxcorelib/scxfilepath.h>
#include <scxcorelib/scxhandle.h>
#include <scxcorelib/scxlog.h>
#include <scxcorelib/scxuser.h>

#include <map>
#include <pwd.h>
#include <stdint.h>



namespace MySQL_Auth
{
    /** Exception for an invalid item */
    class InvalidAuthentication : public SCXCoreLib::SCXException
    {
    public:
        //! Ctor
        InvalidAuthentication(std::wstring reason, 
                              const SCXCoreLib::SCXCodeLocation& l)
        : SCXException(l), m_Reason(reason)
        {}

        std::wstring What() const { return m_Reason;};
    protected:
        //! Description of internal error
        std::wstring m_Reason;
    };

    /** Exception that one of the arguments is not valid (can't use SCXInvalidArgumentException beacause it asserts) */
    class InvalidArgumentException : public SCXCoreLib::SCXException
    {
    public:
        //! Ctor
        InvalidArgumentException(std::wstring formalArgument,
                                 std::wstring reason,
                                 const SCXCoreLib::SCXCodeLocation& l)
            : SCXException(l), m_Reason(L"Argument '" + formalArgument + L"' is not valid - " + reason)
        {}

        std::wstring What() const { return m_Reason;};
    protected:
        //! Description of internal error
        std::wstring m_Reason;
    };

    /** Exception for a port that doesn't exist in the configuration */
    class PortNotFound : public SCXCoreLib::SCXException
    {
    public:
        //! Ctor
        PortNotFound(unsigned int port,
                     const SCXCoreLib::SCXCodeLocation& l)
            : SCXException(l), m_Reason(L"Port not found: " + SCXCoreLib::StrFrom(port))
        {}

        std::wstring What() const { return m_Reason;};
    protected:
        //! Description of internal error
        std::wstring m_Reason;
    };
}

//
// MySQL Authentication Storage Management
//
// Allows updates for stored credentials to access MySQL database
//

class MySQL_AuthenticationDependencies
{
public:
    MySQL_AuthenticationDependencies() { }
    virtual ~MySQL_AuthenticationDependencies() { }

    virtual SCXCoreLib::SCXFilePath GetDefaultAuthFileName(uid_t uid = geteuid()) const
    {
        SCXCoreLib::SCXUser user(uid);
        SCXCoreLib::SCXFilePath filepath(L"/var/opt/microsoft/mysql-cimprov/auth/mysql-auth");

        if (!user.IsRoot())
        {
            filepath.AppendDirectory(user.GetName());
        }

        return filepath;
    }

    virtual bool Force_AutoUpdate_Flag()
    {
        return true;
    }

private:
};

struct MySQL_AuthenticationEntry
{
public:
    enum sourceFlags
    {
        BindingFromDefault = 0x1,
        UsernameFromDefault = 0x2,
        PasswordFromDefault = 0x4
    };

    MySQL_AuthenticationEntry() : port(0), sourcedFromDefault(0) {}
    void clear()
    {
        port = 0;
        binding.clear();
        username.clear();
        password.clear();
        sourcedFromDefault = 0;
    }

    unsigned int port;
    std::string binding;
    std::string username;
    std::string password;

    int sourcedFromDefault;
};

class MySQL_Authentication
{
public:
    explicit MySQL_Authentication(SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> deps = SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_AuthenticationDependencies()), uid_t uid = geteuid(), gid_t gid = getegid());
    virtual ~MySQL_Authentication() { m_deps = NULL; }

    virtual void Load();
    virtual void Save();

    virtual void AllowAutomaticUpdates(bool bAllowed);
    virtual void AddCredentialSet(unsigned int port, const std::string& binding,
                                  const std::string& user, const std::string& password);
    virtual bool AddCredentialSet(unsigned int port, const std::string& binding);
    virtual void DeleteCredentialSet(unsigned int port);

    virtual bool GetAutomaticUpdates();
    virtual void GetPortList(std::vector<unsigned int>& portList);
    virtual bool GetEntry(const unsigned int& port, MySQL_AuthenticationEntry& entry);

    virtual SCXCoreLib::SCXFilePath GetDefaultAuthFileName(uid_t uid = geteuid()) const
        { return m_deps->GetDefaultAuthFileName(uid); }

private:
    std::wstring FormatPortSpecification(const std::string& binding, const std::string& user, const std::string& password);
    void ValidateDefaultRecordUpdate(const std::string& binding, const std::string& username, const std::string& password);

    SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> m_deps;
    SCXCoreLib::SCXConfigFile m_config;
    SCXCoreLib::SCXLogHandle m_log;

    uid_t m_uid;
    gid_t m_gid;

    MySQL_AuthenticationEntry m_default;
};

#endif /* SQLAUTHENTICATION_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
