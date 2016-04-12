# MySQL_CIMPROV
MySQL OMI Provider for OMI Server

##Prequisites
1. At least one modern Linux system with:
  1. root login capability
  2. These build tools:
    1. GNU Make
    2. g++
    3. openssl-devel
2. Open Management Infrastructure (OMI) 1.0.8.(Download from: http://theopengroup.org/software/omi). Note that you need BOTH the binary packages, omi-1.0.8.1.packages.tar.gz,as well as the source distribution file (omi-1.0.8-1.tar.gz).
3. MySQL development package for your distribution. As an example, this contains (on Redhat):
  4. mysql
  5. mysql-server
  6. mysql-devel
  7. mysql-libs
 
##Building the MySQL OMI Provider
###1. Extract oss-mysql.tar.gz into a directory that you will build it from.
   This will create a "mysql" directory like this:
```
mysql/mysql     (directory with contents)
mysql/pal       (directory with contents)
mysql/omi       (no contents under this directory)
README          (this file)
```
###2. Change directory (cd) into directory mysql/omi and extract the OMI source
   file downloaded above. After extraction, you should have a single directory
   named "omi-1.0.8". Rename this directory to "Unix" (capital U is important).

   From the base mysql directory, things should now look like:
```
mysql/mysql/...
mysql/pal/...
mysql/omi/Unix/...
README          (this file)
```
###3. Building the MySQL Provider
  4. `cd mysql/mysql/build`
  5. `./configure`
  6. `make`
  7. `make test (if you wish to run the unit tests*)`
    * *To run the unit tests, edit file:
           `mysql/mysql/test/code/providers/support/sqlcredentials.h`
         This file must contain the binding port, the binding hostname, the
         username, and the password for MySQL. Note that one of the unit tests
         will create/delete a stored procedure in the mysql database, so you
         will likely need to specify the root credentials. The unit test will
         not change anything else in the mysql database, and the stored proc
         will be deleted after the unit tests complete.

###4. Installing
1. Install the appropriate kit for your system from the binary file,
      omi-1.0.8.1.packages.tar.gz (downloaded earlier).
2.  Install mysql provider:
  1. `cd mysql/mysql/build`
  2. `sudo bash`
  3. `make install`

3. Configure OMI
  4. Locate OMI registration directory. Depending on what version of OMI you installed, the registry directory could be in one of two places
    * `/opt/omi/etc/omiregister`
    * `/etc/opt/omi/conf/omiregister`
  5. Create directory root-mysql in this OMI registration directory
  6. Copy MySQL's OMI registration file, from MySQL base directory, file
           `installer/conf/omi/mysqlProvider.reg`, to the directory that you
           just created above.
  7. Restart OMI (see OMI documentation on how to do this)
  
###5. Test the provider
1. To test the provider, run a command like: `/opt/omi/bin/omicli ei root/mysql MySQL_Server` If the command succeeds, then the MySQL provider is running properly. The complete list of classes that the MySQL provider can enumerate are as follows:
 - MySQL_Server*
 - MySQL_ServerStatistics
 - MySQL_Server_Database
 - MySQL_StoredProcedureRow_AsXML**

 * If, when enumerating MySQL_Server, the "OperatingStatus" property contains a value of "Authentication File in Error", then you need to set up your MySQL authentication file. Refer to the MySQL Provider docuemntation for additional details on how to do this.
 
 ** Note that MySQL_StoredProcedureRow_AsXML can only be executed as a WQL query since parameters are required to run a stored procedure. Sample WQL query:
 
          select * from MySQL_StoredProcedureRow_AsXML
            where DatabaseName='test'
               or StoredProcedureName='GetUserData'
               or parameters='param1, param2'

Run a WQL query with a command like: `/opt/omi/bin/omicli wql root/mysql "WQLQUERY"`(where "WQLQUERY" is quoted query from above)




