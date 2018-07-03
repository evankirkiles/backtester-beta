project(backtester)

set(HEADER_FILES
        constants.hpp
        DataHandling/YahooFinanceDownloader.hpp
        DataHandling/DataRetriever.hpp)

set(SOURCE_FILES
        constants.cpp
        DataHandling/YahooFinanceDownloader.cpp
        DataHandling/DataRetriever.cpp)

add_library(backtester STATIC ${SOURCE_FILES} ${HEADER_FILES})