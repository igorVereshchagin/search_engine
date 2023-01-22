#include <iostream>
#include "ConverterJSON.h"

#include "gtest/gtest.h"

int main()
{
  ::testing::InitGoogleTest();
  return RUN_ALL_TESTS();
  // ConverterJSON conv;
  // std::vector<std::string> list = conv.GetTextDocuments();
  // std::vector<std::vector<std::pair<int, float>>> answers;
  // answers.resize(3);
  // answers[0].resize(3);
  // answers[0][0] = std::make_pair((int)0, (double)0.989);
  // answers[0][1] = std::make_pair((int)1, (double)0.897);
  // answers[0][2] = std::make_pair((int)2, (double)0.750);
  // answers[1].resize(1);
  // answers[1][0] = std::make_pair((int)0, (double)0.769);
  // conv.putAnswers(answers);
  // return 0;
}
