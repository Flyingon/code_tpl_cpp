#pragma once

#include <iostream>
#include <fstream>
#include <sys/stat.h>

int readFromFile(const std::string &filePath, std::string &content) {
    std::ifstream ifs;
    ifs.open(filePath);
    if (!ifs.is_open()) {
        std::cerr << "open file: +" + filePath + "+ failed" << std::endl;
        return -1;
    }
    std::stringstream buffer;
    buffer << ifs.rdbuf();
    ifs.close();
    content = buffer.str();
    return 0;
}

int writeToFile(const std::string &filePath, std::string content) {
    std::ofstream ofs;
    ofs.open(filePath);
    if (!ofs.is_open()) {
        std::cerr << "open file: +" + filePath + "+ failed" << std::endl;
        return -1;
    }
    ofs << content;
    ofs.close();
    return 0;
}

bool getFileInfo(const std::string &strPath, long long &lCreateTime,
                 long long &lModifyTime, long long &lAccessTime,
                 long &lFileLen) {
    struct stat tmpInfo;
    if (stat(strPath.c_str(), &tmpInfo) != 0) {
        return false;
    }
    lCreateTime = tmpInfo.st_ctime;
    lModifyTime = tmpInfo.st_mtime;
    lAccessTime = tmpInfo.st_atime;
    lFileLen = tmpInfo.st_size;
    return true;
}
