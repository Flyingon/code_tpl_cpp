#pragma once

#include <iostream>
#include <sstream>

template<typename Iterator>
std::string joinIterator(Iterator first,
                         Iterator last,
                         const std::string &separator = ", ",
                         const std::string &concluder = "") {
    if (first == last) {
        return concluder;
    }

    std::stringstream ss;
    ss << *first;
    ++first;

    while (first != last) {
        ss << separator;
        ss << *first;
        ++first;
    }

    ss << concluder;

    return ss.str();
}


std::string joinVector(const std::vector<std::string> &vec, const std::string &delimiter) {
    std::stringstream ss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0) {
            ss << delimiter;
        }
        ss << vec[i];
    }
    return ss.str();
}

std::string joinArray(std::string strList[], const std::string &delimiter) {
    std::stringstream ss;
    auto len = strList->capacity() / strList[0].length();
    for (int i = 0; i < len; i++) {
        if (i != 0) {
            ss << delimiter;
        }
        ss << strList[i];
    }
    return ss.str();
}

