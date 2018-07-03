//
// Created by Evan Kirkiles on 6/29/18.
//

#ifndef ALGOBACKTESTERV2_YAHOOFINANCEDOWNLOADER_HPP
#define ALGOBACKTESTERV2_YAHOOFINANCEDOWNLOADER_HPP

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

// Program constants include
#include "constants.hpp"

// Handles downloading Yahoo Finance data into .csv's
class YahooFinanceDownloader {
public:
    // Basic default constructor
    explicit YahooFinanceDownloader() = default;
    // Function to pull data from Yahoo Finance and put it into a CSV
    void downloadCSV(std::string symbol, unsigned long startdate, unsigned long enddate);

private:

    // Gets the cookie and crumb data from Yahoo Finance
    const char* get_crumb_and_cookies(const std::string &symbol);


    // String replacing function for formatting the crumb
    static inline void ReplaceAll(std::string &str, const std::string& from, const std::string& to)
    {
        size_t start_pos = 0;
        while(std::string::npos != (start_pos = str.find(from, start_pos))) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
        }
    }
};

#endif /* ALGOBACKTESTERV2_YAHOOFINANCEDOWNLOADER_HPP */