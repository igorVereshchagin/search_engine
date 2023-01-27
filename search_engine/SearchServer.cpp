#include "SearchServer.h"

#include <sstream>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input)
{
  std::vector<std::vector<RelativeIndex>> ret;
  for (auto it = queries_input.begin(); it != queries_input.end(); it++)
  {
    std::stringstream ss(*it);
    std::string word;
    std::vector<std::pair<std::string, std::vector<Entry>>> entries;
    while (!ss.eof())
    {
      ss >> word;
      entries.push_back(std::make_pair(word, _index.GetWordCount(word)));
    }
  }
  return ret;
}