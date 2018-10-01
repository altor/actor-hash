enable_testing()

add_executable(utils_test utils_test.cpp)
target_link_libraries (utils_test gtest gtest_main)
target_link_libraries (utils_test buffer)
target_link_libraries (utils_test utils)
gtest_discover_tests(utils_test)
add_test(toto utils_test)

add_executable(geohash_test geohash_test.cpp)
target_link_libraries (geohash_test gtest gtest_main)
target_link_libraries (geohash_test geohash)
target_link_libraries (geohash_test buffer)
target_link_libraries (geohash_test utils)
gtest_discover_tests(geohash_test)
add_test(geohash_encode_test geohash_test)



