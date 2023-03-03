#include "SearchEngine.h"
#include "gtest/gtest.h"

TEST(TestCaseSearchServer, TestSimple) 
{
  const vector<string> docs = {
    "milk milk milk milk water water water",
    "milk water water",
    "milk milk milk milk milk water water water water water",
    "americano cappuccino"
  };
  const vector<string> request = {"milk water", "sugar"};
  const std::vector<vector<RelativeIndex>> expected = {
  {
    {2, 1},
    {0, 0.7},
    {1, 0.3}
  },
    {}
  };
  InvertedIndex idx;
  idx.UpdateDocumentBase(docs);
  SearchServer srv(idx);
  std::vector<vector<RelativeIndex>> result = srv.search(request);
  ASSERT_EQ(result, expected);
}

TEST(TestCaseSearchServer, TestTop5) 
{
  const vector<string> docs = {
    "london is is the capital of great britain",
    "paris is the capital of france",
    "berlin the capital of germany",
    "rome the capital of italy",
    "madrid the capital of spain",
    "lisboa the capital of portugal",
    "bern the capital of switzerland",
    "moscow is the capital of russia",
    "kiev the capital of ukraine",
    "minsk the capital of belarus",
    "astana the capital of kazakhstan",
    "beijing the capital of china",
    "tokyo the capital of japan",
    "bangkok the capital of thailand",
    "welcome to moscow the capital of russia is the third rome",
    "amsterdam the capital of netherlands",
    "helsinki the capital of finland",
    "oslo the capital of norway",
    "stockholm the capital of sweden",
    "riga the capital of latvia",
    "tallinn the capital of estonia",
    "warsaw the capital of poland",
  };
  const vector<string> request = {"moscow is the capital of russia"};
  const std::vector<vector<RelativeIndex>> expected = {
  {
    {14, 1},
    {7, 0.857142857},
    {0, 0.7142857142857},
    {1, 0.57142857},
    {2, 0.42857},
    {3, 0.42857},
    {4, 0.42857},
    {5, 0.42857},
    {6, 0.42857},
    {8, 0.42857},
    {9, 0.42857},
    {10, 0.42857},
    {11, 0.42857},
    {12, 0.42857},
    {13, 0.42857},
    {15, 0.42857},
    {16, 0.42857},
    {17, 0.42857},
    {18, 0.42857},
    {19, 0.42857},
    {20, 0.42857},
    {21, 0.42857}
  }};
  InvertedIndex idx;
  idx.UpdateDocumentBase(docs);
  SearchServer srv(idx);
  std::vector<vector<RelativeIndex>> result = srv.search(request);
  ASSERT_EQ(result[0][0], expected[0][0]);
  ASSERT_EQ(result[0][1], expected[0][1]);
  ASSERT_EQ(result[0][2], expected[0][2]);
  ASSERT_EQ(result[0][3], expected[0][3]);
}

