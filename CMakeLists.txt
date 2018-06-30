cmake_minimum_required(VERSION 3.10)
project(algobacktesterv2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(APP_DOMAIN ./domain)
set(APP_CALC ./calc)
set(CMAKE_PREFIX_PATH /Users/samkirkiles/Qt/5.11.0/clang_64)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(algobacktesterv2 main.cpp
        Data-Handling/YahooFinanceDownloader.cpp
        Data-Handling/DataRetriever.cpp
        constants.hpp)

find_package(Boost REQUIRED)
IF (BOOST_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()
find_package(CURL REQUIRED)
IF (CURL_FOUND)
    include_directories(%{CURL_INCLUDE_DIRS})
endif()

include_directories(${APP_DOMAIN})
include_directories(${APP_CALC})