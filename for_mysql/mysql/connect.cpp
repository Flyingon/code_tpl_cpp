
#include <stdlib.h>
#include <stdio.h>
#include "mysql.h"

#pragma comment (lib, "libmysql.lib")

MYSQL mysql;

// https://dev.mysql.com/doc/c-api/5.7/en/mysql-real-connect.html
// https://downloads.mysql.com/archives/c-c/
void mysql_connect() {
	mysql.options.use_ssl = false;
	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "your_prog_name");
	mysql_options(&mysql, MYSQL_OPT_SSL_ENFORCE, false);
	if (!mysql_real_connect(&mysql, 
	 "1.13.5.232", "kbe", "pwd123456", "kbe", 3306, NULL, 0
	))
	{
		fprintf(stderr, "Failed to connect to database: Error: %s\n",
			mysql_error(&mysql));
	}

}

int main(void)
{
	mysql_connect();
}