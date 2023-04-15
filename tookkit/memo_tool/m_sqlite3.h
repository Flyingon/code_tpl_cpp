//
// Created by zy.yuan on 2023/4/14.
//

#ifndef CODE_TPL_CPP_SQLITE3_H
#define CODE_TPL_CPP_SQLITE3_H

#include <string>
#include <sqlite3.h>


class Sqlite3 {
private:
    std::string db_path;
    sqlite3 *db;
public:
    Sqlite3(std::string db_path);

    ~Sqlite3();
};


#endif //CODE_TPL_CPP_SQLITE3_H
