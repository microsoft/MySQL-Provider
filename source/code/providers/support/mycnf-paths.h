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
    \file      mycnf-paths.h

    \brief     Declaration for fetching the MySQL Configuration File Paths

    \date      12-02-2014 11:31:00
*/
/*----------------------------------------------------------------------------*/

#include <string>
#include <vector>

#ifndef MYCNF_PATHS_H
#define MYCNF_PATHS_H

namespace MySQL
{
    /**
        Return a list of potential locations for MySQL configuration file.

        Note: This list should be returned in "priority" order (i.e. in order
        of what to check first, what to check next, etc). When looking at the
        various MySQL configuration files, the first path we find "wins".

        \param[out] paths List of MySQL server configuration paths (absolute paths)

    */
    void GetConfigurationFilePaths( std::vector<std::string>& paths );
}

#endif /* MYCNF_PATHS_H */

/*----------------------------E-N-D---O-F---F-I-L-E---------------------------*/
