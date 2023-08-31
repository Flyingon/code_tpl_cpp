#pragma once

# include <time.h>
# include <string>

time_t StringToTimeStamp(std::string str) {
    struct tm tm_;
    int year, month, day, hour, minute, second;
    sscanf(str.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    tm_.tm_year = year - 1900;
    tm_.tm_mon = month - 1;
    tm_.tm_mday = day;
    tm_.tm_hour = hour;
    tm_.tm_min = minute;
    tm_.tm_sec = second;
    tm_.tm_isdst = 0;

    time_t timeStamp = mktime(&tm_);
    return timeStamp;
}

time_t convertTimeStr2TimeStamp(std::string timeStr) {
    struct tm timeinfo;
    strptime(timeStr.c_str(), "%Y-%m-%d %H:%M:%S", &timeinfo);
    time_t timeStamp = mktime(&timeinfo);
    printf("timeStamp=%ld\n", timeStamp);
    return timeStamp;
}
