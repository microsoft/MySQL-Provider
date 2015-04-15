#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>

#define STRING_SIZE 256

#define TOTAL_QUERY 1
#define STORED_PROC 1

int main()
{
    MYSQL *mysql;
    MYSQL_STMT *stmt;
#if defined(STORED_PROC)
    //const char *sql = "call show_all_departments();";
    const char *sql = "show variables like '%version%';";
#else
#if !defined(TOTAL_QUERY)
    const char *sql = "SELECT * FROM `test_table` WHERE `first` like ?";
#else
    const char *sql = "select b.schema_name as 'Database', COUNT(a.table_name) as 'Tables', SUM(a.data_length) + SUM(a.index_length) as 'Size (Bytes)' from information_schema.schemata b left join information_schema.tables a on b.schema_name = a.table_schema where b.schema_name = ? group by b.schema_name;";
#endif // !defined(TOTAL_QUERY)
#endif // !defined(STORED_PROC)

    mysql = mysql_init(NULL);
  
    /* Here we make the connection to MySQL */
#if defined(STORED_PROC)
    if (mysql_real_connect(mysql, "localhost", "root", "root", "employees", 0, NULL, CLIENT_MULTI_RESULTS) == NULL)
#else
#if !defined(TOTAL_QUERY)
    if (mysql_real_connect(mysql, "localhost", "root", "root", "test", 0, NULL, 0) == NULL)
#else
    if (mysql_real_connect(mysql, "127.0.0.1", "root", "mysql", NULL, 3399, NULL, 0) == NULL)
#endif
#endif // defined(STORED_PROC)
    {
        fprintf(stderr, "No connection could be made to the database\n");
        exit(EXIT_FAILURE);
    }

    /* Initialize our statement */
    stmt = mysql_stmt_init(mysql);
    if (!stmt) {
        fprintf(stderr, " mysql_stmt_init(), out of memory\n");
        exit(EXIT_FAILURE);
    }

    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) {
        fprintf(stderr, " mysql_stmt_prepare(), SELECT failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

#if !defined(STORED_PROC)
    char          str_data[STRING_SIZE];
    unsigned long str_length;

    /* Zero out both the param and result data structures */
    MYSQL_BIND param[1];
    memset(param, 0, sizeof(param));

    /* STRING PARAM */
    param[0].buffer_type = MYSQL_TYPE_STRING;
    param[0].buffer = (char *)str_data;
    param[0].buffer_length = STRING_SIZE;
    param[0].is_null = 0;
    param[0].length = &str_length;

    /* Bind the parameters buffer */
    if (mysql_stmt_bind_param(stmt, param)) {
        fprintf(stderr, " mysql_stmt_bind_param() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    /* Specify the parameter that we send to the query */
#if !defined(TOTAL_QUERY)
    strncpy(str_data, "J%", STRING_SIZE);
#else
    strncpy(str_data, "test", STRING_SIZE);
#endif // !defined(TOTAL_QUERY)
    str_length = strlen(str_data);
#endif // !defined(STORED_PROC)


    /* Execute the statement */
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, " mysql_stmt_execute(), failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }


    unsigned int field_count = mysql_stmt_field_count(stmt);
    printf(" Field count: %d\n", field_count);

    MYSQL_RES *resultSet = mysql_stmt_result_metadata(stmt);
    if ( !resultSet ) {
        fprintf(stderr, " mysql_stmt_result_metadata() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    char column_names[field_count][STRING_SIZE];
    {
        MYSQL_FIELD *field;
        unsigned int counter = 0;
        while ((field = mysql_fetch_field(resultSet)))
        {
            strncpy( column_names[counter++], field->name, sizeof(column_names[0]) );
        }
        if (field_count != counter)
        {
            fprintf(stderr, " Field column count (%d) inconsistent with mysql_stmt_field_count (%d)\n",
                    counter, field_count);
            exit(EXIT_FAILURE);
        }

        /* Clean up the result set */
        mysql_free_result(resultSet);
    }

    MYSQL_BIND result[field_count];
    memset(result, 0, sizeof(result));

    char data_field[field_count][STRING_SIZE];
    unsigned long result_lengths[field_count];
    memset(result_lengths, 0, sizeof(result_lengths));

    for (int i = 0; i < field_count; ++i)
    {
        result[i].buffer_type = MYSQL_TYPE_VAR_STRING;
        result[i].buffer = data_field[i];
        result[i].buffer_length = STRING_SIZE;
        result[i].is_null = 0;
        result[i].length = &result_lengths[i];
    }

    /* Bind the results buffer */
    if (mysql_stmt_bind_result(stmt, result) != 0) {
        fprintf(stderr, " mysql_stmt_bind_result() failed\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    /* Print our results */
    int result_count = 0;
    while( true ) {
        int status = mysql_stmt_fetch (stmt);
        if (status == 1 || status == MYSQL_NO_DATA)
            break;

        result_count++;
        for( unsigned int i = 0; i < field_count; ++i)
        {
            if (! result[i].is_null)
                data_field[i][result_lengths[i]] = '\0';
            printf("%s: %s%s",
                   column_names[i],
                   (result[i].is_null ? "<NULL>" : data_field[i]),
                   (i < field_count-1 ? ", ": ""));
        }
        printf("\n");
    }

    if ( result_count == 0 ) {
        printf("No results found!\n");
    }
    else
        printf(" Rows returned: %d\n", result_count);

    if (mysql_stmt_free_result(stmt)) {
        fprintf(stderr, " failed while freeing results for the statement\n");
        fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        exit(EXIT_FAILURE);
    }

    if (mysql_more_results(mysql))
    {
        // Uh oh, more results are outstanding (this happens with prepared call statements
        // to get the final status of the call, or with multiple statements in a query).
        //
        // Note that MySQL versions < 5.5.3 don't support this properly, as the MySQL API
        // mysql_stmt_next_result() doesn't exist, which deals with this properly.
        //
        // The only recovery (ugly) is to abort the connection ...
        fprintf(stderr, " More statement results are signified; closing connection!\n");
        mysql_close(mysql);
    }
    else
    {
        /* Close the statement */
        if (mysql_stmt_close(stmt)) {
            fprintf(stderr, " failed while closing the statement\n");
            fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
        }
        mysql_close(mysql);
    }

    exit(EXIT_SUCCESS);
}
