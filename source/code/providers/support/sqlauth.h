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

    virtual SCXCoreLib::SCXFilePath GetDefaultAuthFileName() const
    {
        SCXCoreLib::SCXUser user;
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
    MySQL_AuthenticationEntry() : port(0) {}
    void clear()
    {
        port = 0;
        binding.clear();
        username.clear();
        password.clear();
    }

    unsigned int port;
    std::string binding;
    std::string username;
    std::string password;
};

class MySQL_Authentication
{
public:
    explicit MySQL_Authentication(SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> deps = SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_AuthenticationDependencies()));
    virtual ~MySQL_Authentication() { m_deps = NULL; }

    virtual void Load();
    virtual void Save();

    virtual void AllowAutomaticUpdates(bool bAllowed);
    virtual void AddCredentialSet(unsigned int port, const std::string& binding,
                                  const std::string& user, const std::string& password);
    virtual void DeleteCredentialSet(unsigned int port);

    virtual bool GetAutomaticUpdates();
    virtual void GetPortList(std::vector<unsigned int>& portList);
    virtual void GetEntry(const unsigned int& port, MySQL_AuthenticationEntry& entry);

private:
    std::wstring FormatPortSpecification(const std::string& binding, const std::string& user, const std::string& password);
    void ValidateDefaultRecordUpdate(const std::string& binding, const std::string& username, const std::string& password);

    SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> m_deps;
    SCXCoreLib::SCXConfigFile m_config;
    SCXCoreLib::SCXLogHandle m_log;
    MySQL_AuthenticationEntry m_default;
};

#endif /* SQLAUTHENTICATION_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
