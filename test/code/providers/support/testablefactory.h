/*--------------------------------------------------------------------------------
 *        Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *     
 *        */
 /**
      \file        testablefactory.h

      \brief       Testable factory (with different dependencies) for unit test purposes

      \date        11-21-14
*/
/*----------------------------------------------------------------------------*/

#ifndef TESTABLEFACTORY_H
#define TESTABLEFACTORY_H

#include <scxcorelib/scxcmn.h>
#include <scxcorelib/scxfile.h>

#include "sqlbinding.h"

static const wchar_t* s_authFilePath = L"./mysql-auth";

class MySQL_TestableAuthenticationDependencies : public MySQL_AuthenticationDependencies
{
public:
    virtual SCXCoreLib::SCXFilePath GetDefaultAuthFileName(uid_t /*uid*/) const
    {
        return s_authFilePath;
    }
};

class MySQL_TestableFactory : public MySQL_Factory
{
    virtual SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies> GetAuthDependencies()
    {
        if (NULL == m_authDeps)
        {
            m_authDeps = SCXCoreLib::SCXHandle<MySQL_AuthenticationDependencies>(new MySQL_TestableAuthenticationDependencies());
        }

        return m_authDeps;
    }
};

#endif /* TESTABLEFACTORY_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
