// compile like this: 
// g++ db_connect.cpp -o test_db -L/usr/include/mariadb/mysql -lmariadbclient

#include <iostream>
#include <mariadb/mysql.h>

using namespace std;

struct connection_det {
	const char * server, *user, *pass, *db;
};

MYSQL* mysql_connection_setup( struct connection_det conn_det) {
	MYSQL * conn = mysql_init(NULL);
	if(!mysql_real_connect(conn, conn_det.server, conn_det.user, conn_det.pass, conn_det.db, 0, NULL, 0 )) {
		cout << "Connection ERROR: could not connect to " << conn_det.db << " " << mysql_error(conn) << endl;
		exit(1);
	}
	return conn;
}

MYSQL_RES* mysql_execute_query(MYSQL* conn, const char * sql_query) {
	if(mysql_query(conn, sql_query)) {
		cout << "MySQL ERROR: " << mysql_error(conn) << endl;
		exit(1);
	}
	return mysql_use_result(conn);
}

int main(int argv, char * argc[]) {
	MYSQL* con;
	MYSQL_RES * res;
	MYSQL_ROW row;
	struct connection_det mysqlD;
	mysqlD.server = "localhost";
	mysqlD.user = "root";
	mysqlD.pass = "2812Dontrelent";
	mysqlD.db = "mysql";

	con = mysql_connection_setup(mysqlD);
	res = mysql_execute_query(con, "select * from event");
	cout << "Displaying database output: \n" << endl;

	while((row = mysql_fetch_row(res) ) != NULL){
		cout << row[0];
	}
	mysql_free_result(res);
	mysql_close(con);

	return 0;

}