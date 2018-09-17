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

// Contains all the order-related constants
namespace order_constants {

    // The threshold for which the volume can be filled on the market
    extern const unsigned int MKTVOL_THRESHOLD;
}



#endif //ALGOBACKTESTERV2_CONSTANTS_HPP
