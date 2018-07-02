//
// Created by Evan Kirkiles on 6/30/18.
//

#include "DataRetriever.hpp"

/*
// Retrieves bars from Yahoo Finance by creating CSVs and reading them
BarData DataRetriever::getBars(const std::string &symbol, const std::string &startdate, const std::string &enddate) {

    // Initializes Yahoo Finance Reader and creates csv's with the data
    YahooFinanceDownloader yfd;
    yfd.downloadCSV(symbol, get_epoch_time(startdate), get_epoch_time(enddate));


}
*/

// Converts time from yyyy-MM-dd to seconds since 1970 epoch
unsigned long get_epoch_time(const std::string &date) {

    // Initialize variables
    struct tm t = {0};

    // First four characters will be the year
    t.tm_year = std::stoi(date.substr(0, 4));
    // Next two characters will be the month
    t.tm_mon = std::stoi(date.substr(5, 7));
    // Remaining two characters will be the day
    t.tm_mday = std::stoi(date.substr(7, 9));

    // Now complete the rest of the format and get time as epoch since 1970
    t.tm_year -= 1900;           // Subtract 1900 here because time_t uses years since 1900
    --t.tm_mon;                  // Subtract 1 here because time_t has January as month 0
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    time_t timeSinceEpoch = mktime(&t);

    // Return it as an unsigned long
    return (unsigned long)timeSinceEpoch;
}

// Converts time from seconds since 1970 epoch to yyyy-MM-dd
std::string get_std_time(unsigned long epochtime) {

    // Formats the date into yyyy-MM-dd
    char date[80];
    strftime(date, 80, "%Y-%m-%d", gmtime((time_t*)&epochtime));
    return date;
}
