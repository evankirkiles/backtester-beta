//
// Created by Evan Kirkiles on 6/29/18.
//

#ifndef ALGOBACKTESTERV2_CONSTANTS_HPP
#define ALGOBACKTESTERV2_CONSTANTS_HPP

// Holds all necessary global constants
namespace proj_constants {

    // Access with proj_constants::Constants.xxxxxxx
    class Constants {
    public:

        // The folder in which to put the data .csvs
        static const char* CSVDIR = "./Data-Handling/CSV/";
        // The file into which to save the crumbs and cookies from Yahoo Finance
        static const char* CRUMBDIR = "./Data-Handling/crumb.txt";
        static const char* COOKIEDIR = "./Data-Handling/cookies.txt";

    };
}

#endif //ALGOBACKTESTERV2_CONSTANTS_HPP
