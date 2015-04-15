#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <sys/stat.h>

#include <mysql.h>

// To call strmov(), must be after string.h
#include <mysql/my_global.h>
#include <mysql/m_string.h>

class FFError
{
public:
    std::string    Label;

    FFError( ) { Label = (char *)"Generic Error"; }
    FFError( char *message ) { Label = message; }
    ~FFError() { }
    inline const char*   GetMessage  ( void )   { return Label.c_str(); }
};

using namespace std;

bool ExecuteQuery(
    MYSQL *MySQLConnection,
    const char *query,
    unsigned int queryLen,
    my_ulonglong& numRows,
    unsigned int& numFields,
    bool checkKnown)
{
    int             mysqlStatus = 0;
    MYSQL_RES      *mysqlResult = NULL;

    MYSQL_ROW       mysqlRow;
    
    mysqlStatus = mysql_real_query( MySQLConnection, query, queryLen );

    if (mysqlStatus)
        throw FFError( (char*) mysql_error(MySQLConnection) );

    // print query results

    bool fFoundWaitTimeout = false;
    numRows = numFields = 0;
    do {
        // Did current statement return data?
        mysqlResult = mysql_store_result(MySQLConnection); // Get the Result Set

        if (mysqlResult)  // there are rows
        {
            // # of rows in the result set
            numRows = mysql_num_rows(mysqlResult);

            // Returns the number of columns in a result set specified
            numFields = mysql_num_fields(mysqlResult);

            printf("Number of rows=%lld  Number of fields=%u \n",numRows,numFields);

            // Print column headers
            printf("\n");

#if 0 // Core dumps on portability on 'call' statements, use mysql_fetch_field instead
            MYSQL_FIELD    *mysqlFields;
            mysqlFields = mysql_fetch_fields(mysqlResult);

            for(int jj=0; jj < numFields; jj++)
            {
                printf("%-15s\t",mysqlFields[jj].name);
            }
            printf("\n");
#else
            MYSQL_FIELD *mysqlField;

            while ((mysqlField = mysql_fetch_field(mysqlResult)) != NULL)
            {
                printf("%-15s\t", mysqlField->name);
            }
            printf("\n");
#endif

            while (mysqlRow = mysql_fetch_row(mysqlResult)) // row pointer in the result set
            {
                numRows++;
                for(int ii=0; ii < numFields; ii++)
                {
                    if ( mysqlRow[ii] && strcmp("wait_timeout", mysqlRow[ii]) == 0 )
                    {
                        fFoundWaitTimeout = true;
                    }
                    printf("%-15s\t", mysqlRow[ii] ? mysqlRow[ii] : "NULL");  // Not NULL then print
                }
                printf("\n");
            }

            mysql_free_result(mysqlResult);
            mysqlResult = NULL;
        }
        else
        {
            if (mysql_field_count(MySQLConnection) == 0)
            {
                // printf("%lld rows affected\n", mysql_affected_rows(MySQLConnection));
            }
            else
            {
                // Some error occured
                fprintf(stderr, "Could not retrieve result set!\n");
                return 1;
            }
        }

        /* more results? -1 = no, >0 = error, 0 = yes (keep looping) */
        if ((mysqlStatus = mysql_next_result(MySQLConnection)) > 0)
            printf("Could not execute statement\n");
    } while (mysqlStatus == 0);

    if ( checkKnown && ! fFoundWaitTimeout )
    {
        fprintf(stderr, "\n\nERROR: Did not find variable \"wait_timeout\"!\n");
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    // --------------------------------------------------------------------
    // Parse the parameters

    string configFile;
    string socketFile;

    string hostName = "localhost";
    string userId   = "root";
    string password = "root";

    int flags, opt;
    while ((opt = getopt(argc, argv, "b:c:u:p:s:")) != -1)
    {
        switch (opt)
        {
            case 'b':
                hostName = optarg;
                break;

            case 'c':
                configFile = optarg;
                break;

            case 'u':
                userId = optarg;
                break;

            case 'p':
                password = optarg;
                break;

            case 's':
                socketFile = optarg;
                break;

            default: /* '?' */
                fprintf(stderr, "Usage:  %s [-b bind-addr] [-c configFile] [-u username] [-p password] [-s socket]\n", argv[0]);
                return 1;
        }
    }

    if ( !configFile.size() && !socketFile.size() )
    {
        // --------------------------------------------------------------------
        // Determine the configuration file we're going to use
        vector<string> configPaths;

        configPaths.push_back( "/etc/my.cnf" );
        configPaths.push_back( "/etc/mysql/my.cnf" );
        configPaths.push_back( "/var/lib/mysql/my.cnf" );
        configPaths.push_back( "/usr/local/mysql/data/my.cnf" );
        configPaths.push_back( "/usr/local/var/my.cnf" );
        configPaths.push_back( "/usr/my.cnf" );

        for (vector<string>::const_iterator it = configPaths.begin(); it != configPaths.end(); ++it)
        {
            struct stat sb;

            if ( 0 == stat((*it).c_str(), &sb) )
            {
                configFile = *it;
                break;
            }
        }

        if ( ! configFile.size() )
        {
            fprintf(stderr, "Unable to determine MySQL configuraiton file path, use -c to specify it or use -s\n");
            return 1;
        }
    }

    // --------------------------------------------------------------------
    // Connect to the database
    
    MYSQL      *MySQLConRet;
    MYSQL      *MySQLConnection = NULL;

    MySQLConnection = mysql_init( NULL );

    try
    {
        mysql_options(MySQLConnection, MYSQL_READ_DEFAULT_FILE, configFile.c_str());

        MySQLConRet = mysql_real_connect( MySQLConnection,
                                          hostName.c_str(), 
                                          userId.c_str(), 
                                          password.c_str(), 
                                          "mysql", /* No database connection */
                                          0,
                                          socketFile.size() ? socketFile.c_str() : NULL,
                                          CLIENT_MULTI_RESULTS );

        if ( MySQLConRet == NULL )
        {
            fprintf(stderr, "  bind-address: %s\n", hostName.c_str());
            fprintf(stderr, "  config-file:  %s\n", configFile.c_str());
            fprintf(stderr, "  username:     %s\n", userId.c_str());
            fprintf(stderr, "  password:     %s\n", password.c_str());
            fprintf(stderr, "  socket-file:  %s\n", socketFile.c_str());

            throw FFError( (char*) mysql_error(MySQLConnection) );
        }

        printf("MySQL Connection Info: %s \n", mysql_get_host_info(MySQLConnection));
        printf("MySQL Client Info: %s \n", mysql_get_client_info());
        printf("MySQL Server Info: %s \n", mysql_get_server_info(MySQLConnection));

    }
    catch ( FFError e )
    {
        printf("%s\n",e.Label.c_str());
        return 1;
    }

    // --------------------------------------------------------------------
    // Perform a SQL SELECT and retrieve data

    try
    {
        my_ulonglong numRows;
        unsigned int numFields;

        char query[1000], *end;
        unsigned int queryLen;

        // Show variables ...
        end = strmov(query, "show variables like \"");
        end += mysql_real_escape_string(MySQLConnection, end, "w%", 2);
        *end++ = '\"';
        queryLen = (unsigned int) (end - query);

        if ( ExecuteQuery(MySQLConnection, query, queryLen, numRows, numFields, true) )
        {
            fprintf(stderr, "\n\nERROR OCCURRED, ABORTING!\n");
            mysql_close(MySQLConnection);
            return 1;
        }
        if ( numRows < 1 || numFields != 2 )
        {
            fprintf(stderr, "\n\nERROR OCCURRED, ABORTING!  numRows: %lld, numFields: %d\n", numRows, numFields);
            mysql_close(MySQLConnection);
            return 1;
        }

        printf("\n");

        // Create stored procedure ...
        end = strmov(query, "drop procedure if exists GetUserData");
        queryLen = (unsigned int) (end - query);

        if ( ExecuteQuery(MySQLConnection, query, queryLen, numRows, numFields, false) )
        {
            fprintf(stderr, "\n\nERROR OCCURRED, ABORTING!\n");
            mysql_close(MySQLConnection);
            return 1;
        }
        if ( numRows != 0 || numFields != 0 )
        {
            fprintf(stderr, "\n\nERROR OCCURRED, ABORTING!  numRows: %lld, numFields: %d\n", numRows, numFields);
            mysql_close(MySQLConnection);
            return 1;
        }

        end = strmov(query,
            "CREATE PROCEDURE GetUserData(in username char(255)) "
            "BEGIN "
            "  SELECT host, user, password FROM user WHERE user like username and password <> ''; "
            "END");
        queryLen = (unsigned int) (end - query);

        if ( ExecuteQuery(MySQLConnection, query, queryLen, numRows, numFields, false) )
        {
            fprintf(stderr, "\n\nERROR OCCURRED, ABORTING!\n");
            mysql_close(MySQLConnection);
            return 1;
        }
        if ( numRows != 0 || numFields != 0 )
        {
            fprintf(stderr, "\n\nERROR OCCURRED, ABORTING!  numRows: %lld, numFields: %d\n", numRows, numFields);
            mysql_close(MySQLConnection);
            return 1;
        }

        printf("\n");

        // Call stored procedure ...
        end = strmov(query, "call `GetUserData` (\"");
        end += mysql_real_escape_string(MySQLConnection, end, "ro%", 3);
        *end++ = '\"';
        *end++ = ')';
        queryLen = (unsigned int) (end - query);

        if ( ExecuteQuery(MySQLConnection, query, queryLen, numRows, numFields, false) )
        {
            fprintf(stderr, "\n\nERROR OCCURRED, ABORTING!\n");
            mysql_close(MySQLConnection);
            return 1;
        }
        if ( numRows < 1 || numFields != 3 )
        {
            fprintf(stderr, "\n\nERROR OCCURRED, ABORTING!  numRows: %lld, numFields: %d\n", numRows, numFields);
            mysql_close(MySQLConnection);
            return 1;
        }

        printf("\n");

        // Clean up stored procedure ...
        end = strmov(query, "drop procedure GetUserData");
        queryLen = (unsigned int) (end - query);

        if ( ExecuteQuery(MySQLConnection, query, queryLen, numRows, numFields, false) )
        {
            fprintf(stderr, "\n\nERROR OCCURRED, ABORTING!\n");
            mysql_close(MySQLConnection);
            return 1;
        }
        if ( numRows != 0 || numFields != 0 )
        {
            fprintf(stderr, "\n\nERROR OCCURRED, ABORTING!  numRows: %lld, numFields: %d\n", numRows, numFields);
            mysql_close(MySQLConnection);
            return 1;
        }

        printf("\n");
    }
    catch ( FFError e )
    {
        fprintf(stderr, "\n\nERROR: %s\n",e.Label.c_str());
        mysql_close(MySQLConnection);
        return 1;
    }

    // --------------------------------------------------------------------
    // Close datbase connection

    mysql_close(MySQLConnection);
    printf("Successful\n");
    return 0;
}
