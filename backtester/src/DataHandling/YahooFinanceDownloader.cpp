//
// Created by Evan Kirkiles on 6/29/18.
//

// Includes
#include "backtester/include/YahooFinanceDownloader.hpp"

// Downloads CSV data for the given period and symbol on a specific frequency.
//
// @param symbol         the symbol for which to download the data
// @param startdate      the starting date for the data download period (in seconds since 1970)
// @param enddate        the ending date for the data download period (in seconds since 1970)
// @param interval       "1d" for daily, "1wk" for weekly, "1mo" for monthly
//
void YahooFinanceDownloader::downloadCSV(std::string symbol, unsigned long startdate, unsigned long enddate,
                                         const std::string& interval) {

    std::string down_url = std::string("https://query1.finance.yahoo.com/v7/finance/download/") + symbol +
                            std::string("?period1=") + std::to_string(startdate) +
                            std::string("&period2=") + std::to_string(enddate) +
                            std::string("&interval=") + interval + ("&events=history&crumb=") +
                            std::string(get_crumb_and_cookies(symbol));

    // Create cURL session
    CURL *curl = curl_easy_init();

    // Set cURL run settings
    // Determine cookie file directory
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, filepaths::COOKIE_DIR);
    // Set website to go to download the .csv
    curl_easy_setopt(curl, CURLOPT_URL, down_url.c_str());
    // Goes to a redirefcted URL instead of the given one, if one crops up
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // Download the body of the linked URL
    curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);

    // Open the file to write to
    FILE *fp = fopen((filepaths::CSV_DIR + symbol + ".csv").c_str(), "wb");
    if (fp) {

        // Write the page body to the file
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

        // Perform file download
        curl_easy_perform(curl);

        // Close the file
        fclose(fp);
    }

    // Clean up cURL
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

// Fetches cookie and crumb data from Yahoo Finance, returning the crumb and saving the cookie
// to a file which is used to access the .csv download link externally.
//
// @param symbol         the symbol to append to the URL to get the correct crumb
// @return               the crumb located by the function
//
const char* YahooFinanceDownloader::get_crumb_and_cookies(const std::string &symbol) {

    // Netscape format for the cookie file
    char nline[256];
    snprintf(nline, sizeof(nline), "%s\t%s\t%s\t%s\t%lu\t%s\t%s", ".example.com", "TRUE", "/", "FALSE",
             (unsigned long)time(nullptr) + 31337UL, "PREF", "hello example");

    // Create cookie cURL session
    CURL *cookiecurl = curl_easy_init();

    // Set cURL run settings
    // Set URL to go to finance.yahoo.com
    curl_easy_setopt(cookiecurl, CURLOPT_URL, std::string("https://finance.yahoo.com/quote/" + symbol + "/history?p=" + symbol).c_str());
    // Set cookie file
    curl_easy_setopt(cookiecurl, CURLOPT_COOKIEFILE, filepaths::COOKIE_DIR);
    curl_easy_setopt(cookiecurl, CURLOPT_COOKIELIST, "ALL");
    // Set the cookie file as the cookie jar
    curl_easy_setopt(cookiecurl, CURLOPT_COOKIESESSION, true);
    curl_easy_setopt(cookiecurl, CURLOPT_COOKIEJAR, filepaths::COOKIE_DIR);
    // Format the cookie in Netscape format
    curl_easy_setopt(cookiecurl, CURLOPT_COOKIELIST, nline);
    // Goes to a redirected URL instead of the given one, if one crops up
    curl_easy_setopt(cookiecurl, CURLOPT_FOLLOWLOCATION, 1);
    // Does not download the header, only the body
    curl_easy_setopt(cookiecurl, CURLOPT_HEADER, 0);

    // Open the file
    FILE* crumbfile = fopen(filepaths::CRUMB_DIR, "wb");
    if (crumbfile) {

        // Write the page body to the crumb file
        curl_easy_setopt(cookiecurl, CURLOPT_WRITEDATA, crumbfile);

        // Performs file transfer
        curl_easy_perform(cookiecurl);

        // Close the file
        fclose(crumbfile);
    }

    // Clean up cURL
    curl_easy_cleanup(cookiecurl);
    curl_global_cleanup();

    // Search for the crumb in newly created crumb file
    std::ifstream searchFile(filepaths::CRUMB_DIR);
    std::string str;
    while(getline(searchFile, str)) {

        // If the crumb identifier is found, return it
        unsigned long stringpos = str.find(R"(CrumbStore":{"crumb":")");
        if (stringpos != str.npos) {

            // Crumb always comes between the two given strings, so find it and take out formatted characters
            std::string toFormat = str.substr(stringpos + 22, str.find(R"("},"UserStore")") - (stringpos+22));
            ReplaceAll(toFormat, "\\u002F", "/");
            return toFormat.c_str();
        }
    }

    // If does not find crumb, throw an exception
    throw std::runtime_error(std::string("Could not locate crumb."));
}