
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

    int sql_execute(const std::string &sql, std::string& msg);
};


#endif //CODE_TPL_CPP_SQLITE3_H
