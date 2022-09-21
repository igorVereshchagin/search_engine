#include <iostream>
#include "ConverterJSON.h"

#include "gtest/gtest.h"
TEST(sample_test_case, sample_test)
{
EXPECT_EQ(1, 1);
}

int main()
{
  ::testing::InitGoogleTest();
  RUN_ALL_TESTS();
  ConverterJSON conv;
  std::vector<std::string> list = conv.GetTextDocuments();
  return 0;
}
