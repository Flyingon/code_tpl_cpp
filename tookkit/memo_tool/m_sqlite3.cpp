//
// Created by zy.yuan on 2023/4/14.
//

#include <iostream>
#include "m_sqlite3.h"

Sqlite3::Sqlite3(std::string db_path) : db_path(db_path) {
    int rc;
    rc = sqlite3_open(this->db_path.c_str(), &this->db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(this->db));

    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
    std::cout << "sqlite[" << this->db_path << "] init" << std::endl;
}

Sqlite3::~Sqlite3() {
    sqlite3_close(this->db);
    std::cout << "sqlite[" << this->db_path << "] closed" << std::endl;
}