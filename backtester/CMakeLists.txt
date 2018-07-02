project(backtester)

set(HEADER_FILES
        DataHandling/YahooFinanceDownloader.hpp
        DataHandling/DataRetriever.hpp)

set(SOURCE_FILES
        DataHandling/YahooFinanceDownloader.cpp
        DataHandling/DataRetriever.cpp)

add_library(backtester STATIC ${SOURCE_FILES} ${HEADER_FILES})