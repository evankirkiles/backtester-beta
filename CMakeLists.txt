cmake_minimum_required(VERSION 3.10)
project(algobacktester)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(APP_DOMAIN ./domain)
set(APP_CALC ./calc)
set(CMAKE_PREFIX_PATH /Users/samkirkiles/Qt/5.11.0/clang_64)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(algobacktester_run
        main.cpp
        backtester/DataHandling/DataRetriever.cpp
        backtester/DataHandling/YahooFinanceDownloader.cpp)

include_directories(backtester)

add_subdirectory(backtester)
add_subdirectory(backtester_tests)

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