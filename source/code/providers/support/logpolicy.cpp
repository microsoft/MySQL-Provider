/*--------------------------------------------------------------------------------
    Copyright (c) Microsoft Corporation.  All rights reserved.
    
*/
/**
    \file        

    \brief       Contains log policy for the MySQL agent.

    \date        2014-11-04 16:52:00

*/
/*----------------------------------------------------------------------------*/

#include <scxcorelib/scxlogpolicy.h>

/*----------------------------------------------------------------------------*/
/**
    Defines the MySQL log policy.
*/

class MySQL_LogPolicy : public SCXCoreLib::SCXLogPolicy
{
public:
    /**
        Virtual destructor.
    */
    virtual ~MySQL_LogPolicy() {}

    /**
        Get the path of the log config file.
        \returns the path of the log config file.
    */
    virtual SCXCoreLib::SCXFilePath GetConfigFileName() const
    {
        return SCXCoreLib::SCXFilePath(L"/etc/opt/microsoft/mysql-cimprov/conf/mysqllog.conf");
    }

    /**
        If no config is specified, then log output will be written
        to the file specified by this method.
        \returns Path to the default log file.
    */
    virtual SCXCoreLib::SCXFilePath GetDefaultLogFileName() const
    {
        return SCXCoreLib::SCXFilePath(L"/var/opt/microsoft/mysql-cimprov/log/mysqllog.log");
    }
};

/*----------------------------------------------------------------------------*/
/**
    This is the MySQL log policy factory. It will return the MySQL
    log policy.

    \returns The default log policy object.
*/
SCXCoreLib::SCXHandle<SCXCoreLib::SCXLogPolicy> CustomLogPolicyFactory()
{
    return SCXCoreLib::SCXHandle<SCXCoreLib::SCXLogPolicy>( new MySQL_LogPolicy() );
}

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
