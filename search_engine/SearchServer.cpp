#include "SearchServer.h"
#include <sstream>
#include <algorithm>
#include <iostream>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queriesInput)
{
  std::vector<std::vector<RelativeIndex>> ret;
  for (auto itQueriesInput = queriesInput.begin(); itQueriesInput != queriesInput.end(); itQueriesInput++)
  {
    std::vector<RelativeIndex> relativeIndexList;
    std::stringstream ss(*itQueriesInput);
    std::vector<std::string> uniqWords;
    while (!ss.eof())
    {
      std::string word;
      ss >> word;
      uniqWords.push_back(word);
    }
    std::unique(uniqWords.begin(), uniqWords.end());

    std::map<std::string, std::vector<Entry>> wordEntries;
    for (auto itUniqWords = uniqWords.begin(); itUniqWords != uniqWords.end(); itUniqWords++)
    {
      std::vector<Entry> entry = _index.GetWordCount(*itUniqWords);
      if (!entry.empty())
        wordEntries.insert(std::make_pair(*itUniqWords, entry));
    }
    
    for (auto it = wordEntries.begin(); it != wordEntries.end(); it++)
    {

    }

    std::vector<std::pair<std::string, int>> wordCount;
    for (auto itWordEntries = wordEntries.begin(); itWordEntries != wordEntries.end(); itWordEntries++)
    {
      int count = 0;
      for (auto itEntry = itWordEntries->second.begin(); itEntry != itWordEntries->second.end(); itEntry++)
        count += itEntry->count;
      wordCount.push_back(std::make_pair(itWordEntries->first, count));
    }
    std::sort(wordCount.begin(), wordCount.end(), [] (std::pair<std::string, int> a, std::pair<std::string, int> b) {return a.second < b.second;});
    std::vector<size_t> docsList;
    for (auto itWordEntries = wordEntries.begin(); itWordEntries != wordEntries.end(); itWordEntries++)
      for (auto itEntry = itWordEntries->second.begin(); itEntry != itWordEntries->second.end(); itEntry++)
        docsList.push_back(itEntry->docId);
    std::unique(docsList.begin(), docsList.end());

    // for (auto itWordCount = wordCount.begin(); itWordCount != wordCount.end(); itWordCount++)
    // {
    //   std::vector<size_t> newDocsList;
    //   for (auto itEntry = wordEntries[itWordCount->first].begin(); itEntry != wordEntries[itWordCount->first].end(); itEntry++)
    //     if (std::find(docsList.begin(), docsList.end(), itEntry->docId) != docsList.end())
    //       newDocsList.push_back(itEntry->docId);
    //   docsList = newDocsList;
    // }

    if (!docsList.empty())
    {
      std::map<size_t, size_t> absRelevancy;
      for (auto itDocList = docsList.begin(); itDocList != docsList.end(); itDocList++)
      {
        for (auto itUniqueWords = uniqWords.begin(); itUniqueWords != uniqWords.end(); itUniqueWords++)
        {
          std::vector<Entry> entryList = _index.GetWordCount(*itUniqueWords);
          for (auto itEntryList = entryList.begin(); itEntryList != entryList.end(); itEntryList++)
            if (itEntryList->docId == *itDocList)
              absRelevancy[*itDocList] += itEntryList->count;
        }
      }
      size_t maxRelevancy = absRelevancy.begin()->second;
      for (auto itAbsRel = absRelevancy.begin(); itAbsRel != absRelevancy.end(); itAbsRel++)
        if (itAbsRel->second > maxRelevancy)
          maxRelevancy = itAbsRel->second;
      
      for (auto itAbsRel = absRelevancy.begin(); itAbsRel != absRelevancy.end(); itAbsRel++)
      {
        RelativeIndex relativeIndex = {itAbsRel->first, (double)(itAbsRel->second) / maxRelevancy};
        relativeIndexList.push_back(relativeIndex);
      }
    }
    ret.push_back(relativeIndexList);
  }
  for (auto it = ret.begin(); it != ret.end(); it++)
  {
    std::cout << "{" << std::endl;
    for (auto it2 = it->begin(); it2 != it->end(); it2++)
      std::cout << "  {" << it2->doc_id << ", " << it2->rank << "}, " << std::endl;
    std::cout << "}" << std::endl;
  }
  return ret;
}