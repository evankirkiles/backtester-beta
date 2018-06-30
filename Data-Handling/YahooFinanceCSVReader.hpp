//
// Created by Evan Kirkiles on 6/29/18.
//

#ifndef ALGOBACKTESTERV2_YAHOOFINANCECSVREADER_HPP
#define ALGOBACKTESTERV2_YAHOOFINANCECSVREADER_HPP

// System includes
#include <fstream>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <cstdio>
#include <cmath>

// Guarded string include
#ifndef string
#include <string>
#endif
// Guarded vector include
#ifndef vector
#include <vector>
#endif

// cURL include
#include <curl/curl.h>

// Packet of data sent by the CSV Reader
struct BarData {

    // Holds the symbol data for each date
    // Format: bars[symbol][date][open / high / low / close / volume / adj]
    std::unordered_map<std::string, std::unordered_map<long, std::unordered_map<std::string, double>>> bars;
    // Vector holding all the dates, SORTED earliest to latest from beginning to end
    std::vector<long> allDates;
    // Holds the current date index for iterating through the bardata
    unsigned int currentDatesIndex;

};

// Handles downloading Yahoo Finance data into .csv's
class YahooFinanceCSVReader {
public:
    // Basic default constructor
    YahooFinanceCSVReader() = default;
    // Function to pull data from Yahoo Finance
    BarData historicalData(std::string symbol, std::string startdate, std::string enddate);

private:
    // Write function for pulling data with cURL
    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
    // Gets the cookie and crumb data from Yahoo Finance
    const char* get_crumb_and_cookies();
};

// Global functions for converting epoch date to readable string and back
long get_epoch_time(std::string date);
std::string get_std_time(long epochtime);

#endif //ALGOBACKTESTERV2_YAHOOFINANCECSVREADER_HPP
