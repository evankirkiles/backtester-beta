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

// Handles downloading Yahoo Finance data into .csv's
class YahooFinanceDownloader {
public:
    // Basic default constructor
    YahooFinanceDownloader() = default;
    // Function to pull data from Yahoo Finance and put it into a CSV
    void downloadCSV(std::string symbol, unsigned long startdate, unsigned long enddate);

private:
    // Write function for pulling data with cURL
    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream);
    // Gets the cookie and crumb data from Yahoo Finance
    const char* get_crumb_and_cookies();
};