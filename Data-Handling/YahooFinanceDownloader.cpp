//
// Created by Evan Kirkiles on 6/29/18.
//

// Includes
#include <constants.hpp>
#include "YahooFinanceDownloader.hpp"

// Downloads CSV data for the given period and symbol on a daily frequency
void YahooFinanceDownloader::downloadCSV(std::string symbol, unsigned long startdate, unsigned long enddate) {

    // Create cURL session
    CURL *curl = curl_easy_init();

    // Set cURL run settings
    // Determine cookie file directory
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, proj_constants::Constants::COOKIEDIR);
    // Set website to go to download the .csv
    curl_easy_setopt(curl, CURLOPT_URL,
                     (std::string("https://query1.finance.yahoo.com/v7/finance/download/") + symbol +
                      std::string("?period1=") + std::to_string(startdate) +
                      std::string("?period2=") + std::to_string(enddate) +
                      std::string("&interval=1d&event=history&crumb=") +
                      get_crumb_and_cookies()
                     ).c_str());
    // Goes to a redirefcted URL instead of the given one, if one crops up
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    // Download the body of the linked URL
    curl_easy_setopt(curl, CURLOPT_NOBODY, 0L);
    // Send all the data through custom write data function
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

    // Open the file to write to
    FILE *fp = fopen((proj_constants::Constants::CSVDIR + symbol + ".csv").c_str(), "wb");
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

// Fetches cookie and crumb data from Yahoo Finance
const char* YahooFinanceDownloader::get_crumb_and_cookies() {

    // Netscape format for the cookie file
    char nline[256];
    snprintf(nline, sizeof(nline), "%s\t%s\t%s\t%s\t%lu\t%s\t%s", ".example.com", "TRUE", "/", "FALSE",
             (unsigned long)time(nullptr) + 31337UL, "PREF", "hello example");

    // Create cookie cURL session
    CURL *cookiecurl = curl_easy_init();

    // Set cURL run settings
    // Set URL to go to finance.yahoo.com
    curl_easy_setopt(cookiecurl, CURLOPT_URL, "https://finance.yahoo.com");
    // Set cookie file
    curl_easy_setopt(cookiecurl, CURLOPT_COOKIEFILE, proj_constants::Constants::COOKIEDIR);
    // Set the cookie file as the cookie jar
    curl_easy_setopt(cookiecurl, CURLOPT_COOKIESESSION, true);
    curl_easy_setopt(cookiecurl, CURLOPT_COOKIEJAR, proj_constants::Constants::COOKIEDIR);
    // Format the cookie in Netscape format
    curl_easy_setopt(cookiecurl, CURLOPT_COOKIELIST, nline);
    // Goes to a redirected URL instead of the given one, if one crops up
    curl_easy_setopt(cookiecurl, CURLOPT_FOLLOWLOCATION, 0L);
    // Does not download the header, only the body
    curl_easy_setopt(cookiecurl, CURLOPT_HEADER, 0L);
    curl_easy_setopt(cookiecurl, CURLOPT_NOBODY, 0L);

    // Open the file
    FILE* crumbfile = fopen(proj_constants::Constants::CRUMBDIR, "wb");
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
    std::ifstream searchFile(proj_constants::Constants::CRUMBDIR);
    std::string str;
    while(getline(searchFile, str)) {

        // If the crumb identifier is found, return it
        unsigned long stringpos = str.find(R"("CrumbStore\":{\"crumb\":\"")");
        if (stringpos != str.npos) {

            // Crumb is always 11 characters long, so make substring of 11 characters
            return (str.substr(stringpos + 22, 11).c_str();
        }
    }

    // If does not find crumb, throw an exception
    throw std::runtime_error(std::string("Could not locate crumb."));
}

// Simple data writing function
size_t YahooFinanceDownloader::write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    return fwrite(ptr, size, nmemb, stream);
}