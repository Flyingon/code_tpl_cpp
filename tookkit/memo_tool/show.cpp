#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "m_sqlite3.h"
#include "m_sqlite3.cpp"
#include "read_file.cpp"
#include "boost/algorithm/string.hpp"

const int TIME_STRING_LENGTH = 20;

void err_print(const std::string &err_msg) {
    std::cout << "[ERROR] " << err_msg << std::endl;
}


int query_record_table(Sqlite3 &sqlite3, std::string &msg, const std::string &type,
                       std::vector<std::string> &status_list) {

    std::string sql = "SELECT * FROM record";
    bool has_where = false;
    if (!type.empty()) {
        sql += " WHERE type LIKE '" + type + "%'";
        has_where = true;
    }

    if (!status_list.empty()) {
        std::string status_str;
        for (uint32_t i = 0; i < status_list.size(); i++) {
            if (status_list[i].empty())
                continue;
            if (i == 0)
                status_str += "'" + status_list[i] + "'";
            else
                status_str += ",'" + status_list[i] + "'";
        }

        if (has_where)
            sql = sql + " AND status in (" + status_str + ")";
        else
            sql += " WHERE status in (" + status_str + ")";
    }
//  std::cout << "[SQL] " << sql << std::endl;
    return sqlite3.sql_execute(sql, msg);
}


int main(int argc, char *argv[]) {
    Data d;
    readfile(&d);
    Sqlite3 sqlite3(d.db_path);

    int res;
    std::string msg;
    std::vector<std::string> status_list;

    switch (argc) {
        case 1:  // no param, query all
        {
            res = query_record_table(sqlite3, msg, "", status_list);
            break;
        }
        case 2:  // only type
        {
            std::string type = argv[1];
            res = query_record_table(sqlite3, msg, type, status_list);
            break;
        }
        case 3:  // two params
        {
            std::string type = argv[1];
            std::string in_status;

            if (argc > 2) {
                in_status = argv[2];
                boost::split(status_list, in_status, boost::is_any_of(","));
            }

            res = query_record_table(sqlite3, msg, type, status_list);
            break;
        }
        default: {
            res = 0;
            printf("args is not valid, please use as: show {type} {status} or show\n");
            break;
        }
    }
    if (res != 0) {
        err_print("query failed: " + msg);
    }

}