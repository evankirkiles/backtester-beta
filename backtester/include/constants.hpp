//
// Created by Evan Kirkiles on 7/1/18.
//

#ifndef ALGOBACKTESTERV2_CONSTANTS_HPP
#define ALGOBACKTESTERV2_CONSTANTS_HPP

// Use a namespace for readability
// Contains all the filepath constants
namespace filepaths {

    // DECLARE all global filepaths here; project directories, etc.
    // Folder for the CSV files to be downloaded into
    extern const char* CSV_DIR;
    // Directory of crumb and cookie files
    extern const char* CRUMB_DIR;
    extern const char* COOKIE_DIR;
}

// Contains types of data requested from Yahoo Finance Data
namespace hist_data_types_YFD {

    // Last close price
    extern const char* OPEN;
    extern const char* CLOSE;
    extern const char* HIGH;
    extern const char* LOW;
    extern const char* VOLUME;
    extern const char* ADJ_CLOSE;
}

// Contains all the order-related constants
namespace order_constants {
    // The threshold for which the volume can be filled on the market
    extern const unsigned double MKTVOL_THRESHOLD;
}



#endif //ALGOBACKTESTERV2_CONSTANTS_HPP
