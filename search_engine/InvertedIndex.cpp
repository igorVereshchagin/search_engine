//
// Created by igora on 09.10.2022.
//

#include "InvertedIndex.h"

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> inputDocs)
{

}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
  std::vector<Entry> ret;
  ret.clear();
  Entry entry = {0, 0};
  for(auto it = docs.begin(); it != docs.end(); it++, entry.docId++)
  {
    entry.count = 0;
    auto pos = it->find(word);
    while (pos != std::string::npos)
    {
      entry.count++;
      pos = it->find(word, pos);
    }
    ret.push_back(entry);
  }
  return ret;
}