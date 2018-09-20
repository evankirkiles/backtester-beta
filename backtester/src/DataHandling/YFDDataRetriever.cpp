//
// Created by Evan Kirkiles on 6/30/18.
//

#include "backtester/include/YFDDataRetriever.hpp"

// Retrieves bars from Yahoo Finance by creating .csv's and reading them into BarData format.
//
// @param symbol         the symbol for which to get the data
// @param startdate      the date in yyyy-MM-dd format of the start of the backtest
// @param enddate        the date in yyyy-MM-dd format of the end of the backtest
// @param interval       "1d" for daily, "1wk" for weekly, "1mo" for monthly (Yahoo Finance specific)
// @param which          "open", "low", 'high", "close", "adj", "volume"
// @return               a BarData containing the data of the specified type in "which"
//
BarData YFDDataRetriever::getBars(const std::string &symbol, const unsigned long &startdate, const unsigned long &enddate,
                               const std::string &interval,  const std::vector<std::string> &which) {

    // Initializes Yahoo Finance Reader on the stack and creates a .csv with the data
    YahooFinanceDownloader yfd;
    yfd.downloadCSV(symbol, startdate, enddate, interval);

    // Cycle through the .csv and append each bar to the information
    // To improve performance, cap the size of the vector as the number of days between start and end
    BarData bd;
    bd.dates.reserve(static_cast<unsigned long>(ceil(enddate - startdate) / 86400));

    // File line iterator variables
    std::ifstream csv(std::string(filepaths::CSV_DIR + symbol + ".csv").c_str());
    std::string line;
    // Skip first line which contains column headers
    std::getline(csv, line);

    // Begin iteration through the csv file
    while (getline(csv, line)) {

        // Get the string stream
        replace(line.begin(), line.end(), ',', ' ');
        std::stringstream ss(line);

        // First column will be the date
        std::string placeholder;
        unsigned long epochtime;
        ss >> placeholder;
        epochtime = get_epoch_time(placeholder);
        bd.dates.emplace_back(epochtime);

        // Next columns follow the format O H L C A V
        ss >> placeholder;
        if (std::find(which.begin(), which.end(), "open") != which.end())
            bd.bars[symbol]["open"][epochtime] = std::stod(placeholder);
        ss >> placeholder;
        if (std::find(which.begin(), which.end(), "high") != which.end())
            bd.bars[symbol]["high"][epochtime] = std::stod(placeholder);
        ss >> placeholder;
        if (std::find(which.begin(), which.end(), "low") != which.end())
            bd.bars[symbol]["low"][epochtime] = std::stod(placeholder);
        ss >> placeholder;
        if (std::find(which.begin(), which.end(), "close") != which.end())
            bd.bars[symbol]["close"][epochtime] = std::stod(placeholder);
        ss >> placeholder;
        if (std::find(which.begin(), which.end(), "adj") != which.end())
            bd.bars[symbol]["adj"][epochtime] = std::stod(placeholder);
        ss >> placeholder;
        if (std::find(which.begin(), which.end(), "volume") != which.end())
            bd.bars[symbol]["volume"][epochtime] = std::stod(placeholder);
    }

    // Return the bardata after all lines have been iterated through
    return bd;
}

// Converts time from yyyy-MM-dd to seconds since 1970 epoch
//
// @param date           a string containing the date in yyyy-MM-dd
// @return               an unsigned long of the date (at 12:00:00.0 A.M EST)
//
unsigned long get_epoch_time(const std::string &date) {

    // Initialize variables
    struct tm t = {0};

    // First four characters will be the year
    t.tm_year = std::stoi(date.substr(0, 4));
    // Next two characters will be the month (after dash)
    t.tm_mon = std::stoi(date.substr(5, 7));
    // Remaining two characters will be the day (after dash)
    t.tm_mday = std::stoi(date.substr(8, 9));

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
//
// @param epochtime      the time in seconds since 1970 EST
// @return               a string containing the date in yyyy-MM-dd
//
std::string get_std_time(unsigned long epochtime) {

    // Formats the date into yyyy-MM-dd
    char date[80];
    strftime(date, 80, "%Y-%m-%d", gmtime((time_t*)&epochtime));
    return std::string(date);
}
