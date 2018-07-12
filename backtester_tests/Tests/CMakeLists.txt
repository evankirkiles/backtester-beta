set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(APP_DOMAIN ./domain)
set(APP_CALC ./calc)
set(CMAKE_PREFIX_PATH /Users/evankirkiles/Qt/5.11.1/clang_64)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include_directories(backtester_tests/lib/googletest/include backtester_tests/lib/googletest)

add_executable(runbacktestertests
        YahooFinanceDownloader_UTESTS.cpp
        DataRetriever_UTESTS.cpp
        DataHandler_UTESTS.cpp)

find_package(Boost REQUIRED)
IF (BOOST_FOUND)
    include_directories(${Boost_INCLUDE_DIR})
endif()
find_package(CURL REQUIRED)
IF (CURL_FOUND)
    include_directories(%{CURL_INCLUDE_DIRS})
    target_link_libraries(runbacktestertests ${CURL_LIBRARIES})
endif()

target_link_libraries(runbacktestertests gtest gtest_main)
target_link_libraries(runbacktestertests backtester)