//
// Created by Evan Kirkiles on 7/2/18.
//

#include "backtester/include/constants.hpp"

// DEFINE all global constants here; project directories, etc.
// Use namespace constants for readability

// Contains all the filepaths to important files
namespace filepaths {

    // Folder for the CSV files to be downloaded into
    const char* CSV_DIR = "./backtester/src/DataHandling/CSV/";
    // Directory of crumb and cookie files
    const char* CRUMB_DIR = "./backtester/src/DataHandling/crumb.txt";
    const char* COOKIE_DIR = "./backtester/src/DataHandling/cookie.txt";
}

// Contains types of data requested from Yahoo Finance Data
namespace hist_data_types_YFD {

    // Last close price
    const char* OPEN = "open";
    const char* CLOSE = "close";
    const char* HIGH = "high";
    const char* LOW = "low";
    const char* VOLUME = "volume";
    const char* ADJ_CLOSE = "adj";
}

// Contains important order filling constants
namespace order_constants {

    // The threshold for which the volume can be filled on the market
    const unsigned double MKTVOL_THRESHOLD = 0.025;
    // The bps slippage to simulate the buy-ask spread not going in your favor
    const unsigned double BPS_DECREASE = 0.0005;
}