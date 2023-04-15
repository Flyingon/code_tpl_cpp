#include <iostream>

#include "m_sqlite3.h"
#include "m_sqlite3.cpp"
#include "read_file.cpp"


int insert_into() {
    return 0;
}


int main(int argc, char *argv[]) {
    Data d;
    readfile(&d);
    std::cout << "d: " << d.db_path << std::endl;

    Sqlite3 sqlite3(d.db_path);
}