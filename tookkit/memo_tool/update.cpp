#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <vector>

#include "m_sqlite3.h"
#include "m_sqlite3.cpp"
#include "read_file.cpp"

const int TIME_STRING_LENGTH = 20;

void err_print(const std::string &err_msg) {
    std::cout << "[ERROR] " << err_msg << std::endl;
}

int update_record_table(Sqlite3 &sqlite3, std::string &msg, const std::string &id,
                        const std::vector<std::string> &params) {
    std::string sql = "UPDATE record SET ";
    for (int i = 0; i < params.size(); i += 2) {
        if (i > 0)
            sql += " AND ";
        sql += params[i] + " = '" + params[i + 1] + "'";
    }
    sql += " WHERE id = " + id;
//    std::cout << "[SQL] " << sql << std::endl;
    return sqlite3.sql_execute(sql, msg);
}


int main(int argc, char *argv[]) {
    Data d;
    readfile(&d);
    Sqlite3 sqlite3(d.db_path);

    if (argc < 2) {
        printf("args is not enough, please use as: update {key} {value} ...\n");
        return -1;
    }

    int res;
    std::string msg;
    std::string id = argv[1];
    std::vector<std::string> params;
    for (int i = 2; i < argc; i++) {
        params.emplace_back(argv[i]);
    }

    res = update_record_table(sqlite3, msg, id, params);
    if (res != 0) {
        err_print("update failed: " + msg);
    }
}