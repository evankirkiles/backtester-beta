project(backtester)

set(HEADER_FILES
        include/constants.hpp
        include/YahooFinanceDownloader.hpp
        include/YFDDataRetriever.hpp
        include/data.hpp
        include/execution.hpp
        include/portfolio.hpp)

set(SOURCE_FILES
        src/constants.cpp
        src/DataHandling/YahooFinanceDownloader.cpp
        src/DataHandling/YFDDataRetriever.cpp
        src/Infrastructure/data.cpp
        src/Infrastructure/execution.cpp
        src/Infrastructure/portfolio.cpp)

add_library(backtester STATIC ${SOURCE_FILES} ${HEADER_FILES})