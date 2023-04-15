//
// Created by zy.yuan on 2023/4/14.
//

#include "m_sqlite3.h"
#include <stdio.h>

Sqlite3::Sqlite3(std::string db_path) : db_path{db_path} {
    int rc;
    rc = sqlite3_open(this->db_path.c_str(), &this->db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(this->db));

    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
}

Sqlite3::~Sqlite3() {
    int rc;
    rc = sqlite3_open("test.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));

    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
}