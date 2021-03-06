cmake_minimum_required(VERSION 3.10)
project(algobacktester)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(APP_DOMAIN ./domain)
set(APP_CALC ./calc)
set(CMAKE_PREFIX_PATH /Users/evankirkiles/Qt/5.11.1/clang_64)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(algobacktester_run
        main.cpp
        backtester/src/DataHandling/YFDDataRetriever.cpp
        backtester/src/DataHandling/YahooFinanceDownloader.cpp
        backtester/src/Infrastructure/data.cpp
        backtester/src/Infrastructure/events.cpp
        backtester/src/Infrastructure/execution.cpp
        backtester/src/Infrastructure/portfolio.cpp
        backtester/src/Strategies/strategy.cpp
        backtester/src/constants.cpp)

include_directories(backtester)

include_directories(backtester_tests/lib/googletest/include backtester_tests/lib/googletest)

add_subdirectory(backtester)
add_subdirectory(backtester_tests)

target_link_libraries(backtester)

find_package(Boost REQUIRED)
IF (BOOST_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()
find_package(CURL REQUIRED)
IF (CURL_FOUND)
    include_directories(%{CURL_INCLUDE_DIRS})
    target_link_libraries(algobacktester_run ${CURL_LIBRARIES})
endif()

include_directories(${APP_DOMAIN})
include_directories(${APP_CALC})