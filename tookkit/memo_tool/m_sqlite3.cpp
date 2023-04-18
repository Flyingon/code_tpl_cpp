#include <iostream>
#include "m_sqlite3.h"

Sqlite3::Sqlite3(std::string db_path) : db_path(db_path) {
    int rc;
    rc = sqlite3_open(this->db_path.c_str(), &this->db);

    if (rc) {
        fprintf(stderr, "can't open database: %s\n", sqlite3_errmsg(this->db));

    }
//    else {
//        fprintf(stderr, "Opened database successfully\n");
//    }
//    std::cout << "sqlite[" << this->db_path << "] init" << std::endl;
}

Sqlite3::~Sqlite3() {
    sqlite3_close(this->db);
//    std::cout << "sqlite[" << this->db_path << "] closed" << std::endl;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    std::string row;
    for (i = 0; i < argc; i++) {
        if (i != 0) {
            row += "\t";
        }
        row += argv[i] ? argv[i] : "NULL";
//        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    std::cout << row << std::endl;
//    printf("\n");
    return 0;
}

int Sqlite3::sql_execute(const std::string &sql, std::string &msg) {
    int res;
    char *err_msg;
    res = sqlite3_exec(this->db, sql.c_str(), callback, nullptr, &err_msg);

    if (res != SQLITE_OK) {
        msg = std::string(err_msg);
        sqlite3_free(err_msg);
    }
    return res;
}
