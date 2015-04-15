#include <stdio.h>
#include <mysql.h>
#include <string>

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

main()
{
    // --------------------------------------------------------------------
    // Connect to the database
    
    MYSQL      *MySQLConRet;
    MYSQL      *MySQLConnection = NULL;

    string hostName = "localhost";
    string userId   = "root";
    string password = "root";

    MySQLConnection = mysql_init( NULL );

    try
    {
        MySQLConRet = mysql_real_connect( MySQLConnection,
                                          hostName.c_str(), 
                                          userId.c_str(), 
                                          password.c_str(), 
                                          NULL, /* No database connection */
                                          0, 
                                          NULL,
                                          0 );

        if ( MySQLConRet == NULL )
            throw FFError( (char*) mysql_error(MySQLConnection) );
   
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

    int             mysqlStatus = 0;
    MYSQL_RES      *mysqlResult = NULL;

    MYSQL_ROW       mysqlRow;
    MYSQL_FIELD    *mysqlFields;
    my_ulonglong    numRows;
    unsigned int    numFields;
    
    try
    {
        string sqlSelStatement = "show variables like 'w%'";
        mysqlStatus = mysql_query( MySQLConnection, sqlSelStatement.c_str() );

        if (mysqlStatus)
            throw FFError( (char*)mysql_error(MySQLConnection) );
        else
            mysqlResult = mysql_store_result(MySQLConnection); // Get the Result Set

        if (mysqlResult)  // there are rows
        {
            // # of rows in the result set
            numRows = mysql_num_rows(mysqlResult);

            // # of Columns (mFields) in the latest results set
            numFields = mysql_field_count(MySQLConnection);

            // Returns the number of columns in a result set specified
            numFields = mysql_num_fields(mysqlResult);

            printf("Number of rows=%u  Number of fields=%u \n",numRows,numFields);
        }
        else
        {
           printf("Result set is empty\n");
           return 0;
        }
    
        // Print column headers
        printf("\n");

        mysqlFields = mysql_fetch_fields(mysqlResult);

        for(int jj=0; jj < numFields; jj++)
        {
            printf("%-38s\t",mysqlFields[jj].name);
        }
        printf("\n");
     
        // print query results

        bool fFoundWaitTimeout = false;
        while(mysqlRow = mysql_fetch_row(mysqlResult)) // row pointer in the result set
        {
            for(int ii=0; ii < numFields; ii++)
            {
                if ( mysqlRow[ii] && strcmp("wait_timeout", mysqlRow[ii]) == 0 )
                {
                    fFoundWaitTimeout = true;
                }
                printf("%-38s\t", mysqlRow[ii] ? mysqlRow[ii] : "NULL");  // Not NULL then print
            }
            printf("\n");
        }

        if(mysqlResult)
        {
            mysql_free_result(mysqlResult);
            mysqlResult = NULL;
        }
    }
    catch ( FFError e )
    {
        printf("%s\n",e.Label.c_str());
        mysql_close(MySQLConnection);
        return 1;
    }

    // --------------------------------------------------------------------
    // Close datbase connection

    mysql_close(MySQLConnection);

    return 0;
}
