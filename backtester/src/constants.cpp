//
// Created by Evan Kirkiles on 7/2/18.
//

#include "backtester/include/constants.hpp"

// Use namespace constants for readability

// Contains all the filepaths to important files
namespace filepaths {

    // DEFINE all global constants here; project directories, etc.
    // Folder for the CSV files to be downloaded into
    const char* CSV_DIR = "./backtester/src/DataHandling/CSV/";
    // Directory of crumb and cookie files
    const char* CRUMB_DIR = "./backtester/src/DataHandling/crumb.txt";
    const char* COOKIE_DIR = "./backtester/src/DataHandling/cookie.txt";
}

// Contains important order filling constants
namespace order_constants {

    // The threshold for which the volume can be filled on the market
    const unsigned double MKTVOL_THRESHOLD = 0.025;
}