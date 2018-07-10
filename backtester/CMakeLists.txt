project(backtester)

set(HEADER_FILES
        constants.hpp
        DataHandling/YahooFinanceDownloader.hpp
        DataHandling/DataRetriever.hpp
        Infrastructure/data.hpp
        Infrastructure/execution.hpp)

set(SOURCE_FILES
        constants.cpp
        DataHandling/YahooFinanceDownloader.cpp
        DataHandling/DataRetriever.cpp
        Infrastructure/data.cpp
        Infrastructure/execution.cpp)

add_library(backtester STATIC ${SOURCE_FILES} ${HEADER_FILES})