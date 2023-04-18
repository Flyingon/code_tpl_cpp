#include <iostream>
#include <vector>
#include <string>
#include <ctime>

#include "m_sqlite3.h"
#include "m_sqlite3.cpp"
#include "read_file.cpp"

const std::string cmd_init = "-init";
const int TIME_STRING_LENGTH = 20;

void err_print(std::string err_msg) {
    std::cout << "[ERROR] " << err_msg << std::endl;
}


int create_record_table(Sqlite3 &sqlite3, std::string &msg) {
    std::string sql = "CREATE TABLE IF NOT EXISTS record("  \
      "id INTEGER PRIMARY KEY AUTOINCREMENT    NOT NULL," \
      "type           TEXT    NOT NULL," \
      "desc           TEXT    NOT NULL," \
      "content        TEXT ," \
      "status         TEXT     NOT NULL," \
      "created_at     DATETIME," \
      "due_to         DATETIME );";
    return sqlite3.sql_execute(sql, msg);
}


int insert_record_table(Sqlite3 &sqlite3, std::string &msg, const std::string &type,
                        const std::string &desc, const std::string &content, const std::string &status,
                        float due_to_days) {
    time_t now = time(nullptr);
    struct tm *now_time = localtime(&now);

    char now_str[TIME_STRING_LENGTH];
    char due_str[TIME_STRING_LENGTH];
    strftime(now_str, TIME_STRING_LENGTH, "%Y-%m-%d %H:%M:%S", now_time);

    time_t due_to = now + (int) (due_to_days * 24 * 3600);
    struct tm *due_time = localtime(&due_to);
    strftime(due_str, TIME_STRING_LENGTH, "%Y-%m-%d %H:%M:%S", due_time);
    std::string sql_tpl = "INSERT INTO record (type, desc, content, status, created_at, due_to) " \
                      "VALUES ('%s','%s','%s','%s','%s','%s')";

    int str_len = sql_tpl.size() + desc.size() + type.size() + content.size() + status.size() + TIME_STRING_LENGTH * 2;
    char sql[str_len];
    std::snprintf(sql, sizeof(sql) - 1, sql_tpl.c_str(),
                  type.c_str(), desc.c_str(), content.c_str(), status.c_str(), now_str, due_str);
//    std::cout << "[SQL]: " << sql << std::endl;
    return sqlite3.sql_execute(sql, msg);
}


int main(int argc, char *argv[]) {
    Data d;
    readfile(&d);
    Sqlite3 sqlite3(d.db_path);

    if (argc < 2) {
        printf("args is not enough, please use as: record {type} {desc} {content} {status} {due_days}\n");
        return -1;
    }

    int res;
    std::string msg;
    if (std::string(argv[1]) == cmd_init) {
        res = create_record_table(sqlite3, msg);
        if (res != 0) {
            err_print("record init failed: " + msg);
        }
    } else {
        std::string type = argv[1];
        std::string desc = argv[2];
        std::string content = argv[3];
        std::string status = argv[4];
        float due_day = std::stof(argv[5]);;

        res = insert_record_table(sqlite3, msg, type, desc, content, status, due_day);
        if (res != 0) {
            err_print("insert failed: " + msg);
        }
    }
}