#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "m_sqlite3.h"
#include "m_sqlite3.cpp"
#include "read_file.cpp"

const int TIME_STRING_LENGTH = 20;

void err_print(std::string err_msg) {
    std::cout << "[ERROR] " << err_msg << std::endl;
}

int query_record_table(Sqlite3 &sqlite3, std::string &msg, const std::string &type,
                       const std::string &status) {
    std::string sql = "SELECT * FROM record WHERE type LIKE '" + type + "%'";
    if (!status.empty()) {
        sql = sql + " AND status = '" + status + "'";
    }
    return sqlite3.sql_execute(sql, msg);
}


int main(int argc, char *argv[]) {
    Data d;
    readfile(&d);
    Sqlite3 sqlite3(d.db_path);

    if (argc < 2) {
        printf("args is not enough, please use as: show {type} {status}\n");
        return -1;
    }

    int res;
    std::string msg;
    std::string type = argv[1];
    std::string status;

    if (argc > 2) {
        status = argv[2];
    }

    res = query_record_table(sqlite3, msg, type, status);
    if (res != 0) {
        err_print("query failed: " + msg);
    }
}