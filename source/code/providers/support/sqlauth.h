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
      \file        sqlauth.h

      \brief       MySQL authentication handling for MySQL provider
      \date        11-13-14

      Allows updates for stored credentials to access MySQL database
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

#include <unistd.h>
#include <sys/types.h>

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

/**
   MySQL dependencies class

   Allows for overrides for unit test purposes
*/
class MySQL_AuthenticationDependencies
{
public:
    //! Ctor
    MySQL_AuthenticationDependencies() { }
    //! Dtor
    virtual ~MySQL_AuthenticationDependencies() { }

    /**
       Get the default filename for storage of the provider authentication database

       \param[in]  uid       User ID for purposes of building the filename
       \returns    SCXFilePath for resulting constructed filename
     */
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

    /**
       Return state of Forced AutoUpdate (default state for AutoUpdate flag)

       \returns    'true' if AutoUpdate, by default, is enabled
     */
    virtual bool Force_AutoUpdate_Flag()
    {
        return true;
    }

private:
};

/**
   MySQL Authentication Entry

   Reflects a single authentication entry from the provider authentication database.
*/
struct MySQL_AuthenticationEntry
{
public:
    //! Flags to indicate if fields came from default record
    enum sourceFlags
    {
        BindingFromDefault = 0x1,
        UsernameFromDefault = 0x2,
        PasswordFromDefault = 0x4
    };

    //! Ctor
    MySQL_AuthenticationEntry() : port(0), sourcedFromDefault(0) {}

    //! Reset complete contents of class
    void clear()
    {
        port = 0;
        binding.clear();
        username.clear();
        password.clear();
        sourcedFromDefault = 0;
    }

    unsigned int port;          //!< Port number (MySQL instance) for connection
    std::string binding;        //!< Bind-address for the MySQL instance
    std::string username;       //!< Username for the MySQL instance
    std::string password;       //!< Password for the MySQL instance

    int sourcedFromDefault;     //!< Flags to indicate which fields, if any, came from default record
};

/**
   MySQL Authentication Class

   Allows for creation and management of the provider authentication file
*/
class MySQL_Authentication
{
public:
    /*----------------------------------------------------------------------------*/
    /**
       Constructor

       \param[in]  deps     Dependency class to use for dependency injection
       \param[in]  uid      User ID for the owner of the authentication file
       \param[in]  gid      Group ID for the owner of the authentication file

    */
    explicit MySQL_Authentication(SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> deps = SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_AuthenticationDependencies()), uid_t uid = geteuid(), gid_t gid = getegid());
    //! Dtor
    virtual ~MySQL_Authentication() { m_deps = NULL; }

    /**
       Load MySQL instance and authentication data into memory

       Note: If the MySQL configuration file does not exist, then an empty MySQL
       configuration is constructed. In this way, the class can be used to create
       a new configuration.

    */
    virtual void Load();

    /**
       Save MySQL instance and authentication data to disk

       Note that, for ease in editing the file, we always persist the AutoUpdate
       setting, even if the user didn't explicitly set that. This makes it easier
       for administrators to edit the file by hand and change this setting.

       Note: This method may be called from omi-preexec, which means that we may
       be running with root privileges. Take care to insure that anything we write
       to disk has correct user/group ownership and permissions so that that user
       can come along, non-privileged, and modify the data again (via the command
       line authentication utility, for example).

    */
    virtual void Save();

    /**
       Allow or disallow automatic updates to the authentication file

       Automatic updates is the notion that omi-preexec can automatically populate
       the provider authentication file based on the MySQL system configuration
       file. This works well if there is a MySQL configuration file, and if the file
       is accurate and actually used by MySQL. But it's possible that MySQL is set
       up via the command line, and never reads a configuration file at all.

       Disabling automatic updates allows the administrator to explicitly set up
       the provider authentication file without any automatic changes down the road.

       \param[in]  bAllowed  True to enable automatic updates, false otherwise

    */
    virtual void AllowAutomaticUpdates(bool bAllowed);

    /**
       Add a new instance (credential set) to the provider authentication file

       \param[in]  port      Port number for the MySQL server instance
       \param[in]  binding   Binding address for the MySQL server instance
       \param[in]  username  Username for the MySQL server instance
       \param[in]  password  Password for the MySQL server instance
       \throws     InvalidArgumentException if username supplied without password, or if password supplied without username
       \throws     InvalidAuthentication if new credential set is invalid given the current default record stored

    */
    virtual void AddCredentialSet(unsigned int port, const std::string& binding,
                                  const std::string& user, const std::string& password);

    /**
       Add partial instance (credential set) to the provider authentication file

       This entry point is intended for the OMI PreExec program, and doesn't
       validate additions that are being made. Only port/binding can be set
       (since that's all that's generally in the MySQL configuration file).

       \param[in]  port      Port number for the MySQL server instance
       \param[in]  binding   Binding address for the MySQL server instance
       \returns    True if entry was added, false otherwise

    */
    virtual bool AddCredentialSet(unsigned int port, const std::string& binding);

    /**
       Remove an instance (credential set) to the provider authentication file

       \param[in]  port      Port number for the MySQL server instance
       \throws     InvalidArgumentException if port doesn't exist in the configuraiton file
       \throws     InvalidAuthentication if deleting default entry and default entry is required

    */
    virtual void DeleteCredentialSet(unsigned int port);

    /**
       Read 'AutoUpdate' entry from the configuration file

       Since users may edit this, be flexible on value. Allow 'true' or 'false'
       to allow/disallow as well as '1' or '0' to allow/disallow.

       If setting is not valid, log warning and assume automatic updates are
       allowed.

       \returns    True if automatic updates are allowed, false otherwise

    */
    virtual bool GetAutomaticUpdates();

    /**
       Get list of MySQL Server instances (ports) that are in authentication file

       \param[out] portList  Vector of ports that are defined in authentication file

    */
    virtual void GetPortList(std::vector<unsigned int>& portList);

    /**
       Get an entry from the provider authentication file

       \param[in]  port      Port number for the MySQL server instance
       \param[out] entry     Structure representing the port definition from the instance file
       \throws     PortNotFound if port not defined in authentication file
       \returns    True if valid entry was returned, false otherwise

    */
    virtual bool GetEntry(const unsigned int& port, MySQL_AuthenticationEntry& entry);

    /**
       Get the authentication filename for the provider authentication file

       \param[in]  uid       User ID for the current user
       \returns    File path for the authentication file

    */
    virtual SCXCoreLib::SCXFilePath GetDefaultAuthFileName(uid_t uid = geteuid()) const
        { return m_deps->GetDefaultAuthFileName(uid); }

private:
    /**
       Format a port specification consistently for use in authentication file

       \param[in]  binding   Binding specification for connection to MySQL server instance
       \param[in]  user      Username for authentication to MySQL server instance
       \param[in]  password  password for authentication to MySQL server instance
       \returns    Formatted string of port specification (bind-address + username + password)

    */
    std::wstring FormatPortSpecification(const std::string& binding, const std::string& user, const std::string& password);

    /**
       Validate default record is valid after updates are applied

       If a default record is updated, we need to be careful that the new default
       record is valid relative to all other entries that refer to it. For example,
       if a new default record has no bind address, but some entry in the provider
       authentication file relies on it, that is a problem since it will invalidate
       the reliant record.

       This method will insure that the new default record is valid for all of the
       records defined in the provider authentication file

       \param[in]  binding   Binding specification for connection to MySQL server instance
       \param[in]  user      Username for authentication to MySQL server instance
       \param[in]  password  password for authentication to MySQL server instance
       \throws     InvalidAuthentication if new default record definition is NOT valid

    */
    void ValidateDefaultRecordUpdate(const std::string& binding, const std::string& username, const std::string& password);

    SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> m_deps; //!< Dependency object
    SCXCoreLib::SCXConfigFile m_config; //!< Configuraiton class (for storage of authentication file)
    SCXCoreLib::SCXLogHandle m_log;     //!< Log handle

    uid_t m_uid;                        //!< User ID for the current authentication file
    gid_t m_gid;                        //!< Group ID for the current authentication file

    MySQL_AuthenticationEntry m_default; //!< Default authentication entry (if any)
};

#endif /* SQLAUTHENTICATION_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
