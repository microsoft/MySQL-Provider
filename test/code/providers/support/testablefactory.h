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
