#include <stdio.h>
#include <string.h>
#include <gtest/gtest.h>

extern "C" {
#include "../src/hash/geohash.h"
#include "../src/utils/buffer.h"
#include <errno.h>
}

buffer_t * buffer = buffer_create(50);

void test_encode(double latitude, double longitude, int prec){
  coordinate_t coordinate;
  coordinate.latitude = latitude;
  coordinate.longitude = longitude;
  geohash_encode(coordinate, prec, buffer);
}

TEST(geohash_encode_test, correct_return1_quality4) {
  test_encode(50, 40, 4);

  EXPECT_TRUE(strcmp("ubuk", buffer_get_memory(buffer)) == 0);
  EXPECT_TRUE(errno == 0);
}

TEST(geohash_encode_test, correct_return2_quality4) {
  test_encode(48.310, -32.34, 4);

  EXPECT_TRUE(strcmp("g294", buffer_get_memory(buffer)) == 0);
  EXPECT_TRUE(errno == 0);
}

TEST(geohash_encode_test, invalid_latitude) {

  test_encode(98.310, 32.34, 4);
  EXPECT_TRUE(errno == -1);
}

TEST(geohash_encode_test, invalid_longitude) {
  test_encode(48.310, 190, 4);
  EXPECT_TRUE(errno == -1);
}
