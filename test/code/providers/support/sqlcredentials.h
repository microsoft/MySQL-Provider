/*--------------------------------------------------------------------------------
 *        Copyright (c) Microsoft Corporation. All rights reserved. See license.txt for license information.
 *     
 *        */
 /**
      \file        sqlcredentials.h

      \brief       Define constants for MySQL login credentials (test only)

      \date        10-20-14
*/
/*----------------------------------------------------------------------------*/

#ifndef SQLCREDENTIALS_H
#define SQLCREDENTIALS_H

#include <string>

const unsigned int sqlPort(3306);
const std::string sqlHostname("127.0.0.1");
const std::string sqlUsername("root");
const std::string sqlPassword("root");

#endif /* SQLCREDENTIALS_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
