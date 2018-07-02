include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(runbacktestertests
        YahooFinanceDownloader_UTESTS.cpp)

target_link_libraries(runbacktestertests gtest gtest_main)