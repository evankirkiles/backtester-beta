//
// Created by Evan Kirkiles on 6/30/18.
//

#include "DataRetriever.hpp"

// Retrieves bars from Yahoo Finance by creating CSVs and reading them
BarData DataRetriever::getBars(std::string symbol, std::string startdate, std::string enddate) {

    // Initializes Yahoo Finance Reader and creates csv's with the data
    YahooFinanceDownloader yfd;
    yfd.downloadCSV(symbol, get_epoch_time(startdate), get_epoch_time(enddate));


}

// Converts time from yyyy-MM-dd to seconds since 1970 epoch
unsigned long get_epoch_time(std::string date) {

    // Initialize variables
    struct tm t = {0};
    size_t pos = 0;

    // Parse through the string and get year, month, and date
    while (std::string::npos != (pos = date.find("-"))) {

        // Different lengths in the string correspond to different components: year = 4, month = 2
        switch(pos) {
            case 4:
                t.tm_year = std::stoi(date.substr(0, pos));
                break;
            case 2:
                t.tm_mon = std::stoi(date.substr(0, pos));
                break;
            default:
                break;
        }

        // Erase the interpreted date information from the string
        date.erase(0, pos + 1);
    }

    // Remaining two characters will be the day
    t.tm_mday = std::stoi(date);

    // Now complete the rest of the format and get time as epoch since 1970
    t.tm_year -= 1900;           // Subtract 1900 here because time_t uses years since 1900
    --t.tm_mon;                  // Subtract 1 here because time_t has January as month 0
    t.tm_hour = 0;
    t.tm_min = 0;
    t.tm_sec = 0;
    time_t timeSinceEpoch = mktime(&t);

    // Return it as an unsigned long
    return unsigned long(timeSinceEpoch);
}

// Converts time from seconds since 1970 epoch to yyyy-MM-dd
std::string get_std_time(unsigned long epochtime) {

    // Formats the date into yyyy-MM-dd
    char date[80];
    strftime(date, 80, "%Y-%m-%d", gmtime((time_t*)&epochtime));
    return date;
}
