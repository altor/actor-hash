#include <stdio.h>
#include <string.h>
#include <gtest/gtest.h>

extern "C" {
#include "../src/utils/utils.h"
#include "../src/utils/buffer.h"
#include <errno.h>
}


// utils_extract_bit_n
TEST(utils_extract_bit_n_test, return_1) {
  EXPECT_TRUE(utils_extract_bit_n(40, 3) == 1);
}

TEST(utils_extract_bit_n_test, return_0) {
  EXPECT_TRUE(utils_extract_bit_n(40, 1) == 0);
}

TEST(utils_extract_bit_n_test, return_1_1_bit) {
  EXPECT_TRUE(utils_extract_bit_n(1, 0) == 1);
}

TEST(utils_extract_bit_n_test, return_0_1_bit) {
  EXPECT_TRUE(utils_extract_bit_n(0, 0) == 0);
}


// utils_to_b32

buffer_t * buffer = buffer_create(50);

TEST(utils_to_b32_test, correct_value_1digit_1) {
  utils_to_b32(3, buffer);
  EXPECT_TRUE(errno == 0);
  EXPECT_TRUE(strcmp("3", buffer_get_memory(buffer)) == 0);

}

TEST(utils_to_b32_test, correct_value_1digit_2) {
  utils_to_b32(31,buffer);
  EXPECT_TRUE(errno == 0);
  EXPECT_TRUE(strcmp("z", buffer_get_memory(buffer)) == 0);
}

TEST(utils_to_b32_test, correct_value) {
  utils_to_b32(42,buffer);
   EXPECT_TRUE(errno == 0);
  EXPECT_TRUE(strcmp("1b", buffer_get_memory(buffer)) == 0);
}

TEST(utils_to_b32_test, buffer_to_small) {
  buffer_t * small_buffer = buffer_create(1);
  utils_to_b32(42, small_buffer);
  EXPECT_TRUE(errno == -1);
}
