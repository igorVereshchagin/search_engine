//
// Created by igora on 09.10.2022.
//

#include "InvertedIndex.h"
#include <thread>
#include <sstream>
#include <utility>

void InvertedIndex::UpdateDocumentTask(InvertedIndex* pThis, std::queue<std::pair<size_t, std::string*>> *inQueue, std::mutex *queueLock)
{
  bool queueNotEmpty;
  do
  {
    std::pair<size_t, std::string*> doc;
    queueLock->lock();
    queueNotEmpty = !inQueue->empty();
    if (queueNotEmpty)
    {
      doc = inQueue->front();
      inQueue->pop();
      queueLock->unlock();
    }
    else
    {
      queueLock->unlock();
      continue;
    }
    size_t id = doc.first;
    std::stringstream ss(*doc.second);
    std::string word;
    while (!ss.eof())
    {
      ss >> word;
      pThis->dictLock.lock();
      bool found = false;
      for (auto it = pThis->freqDictionary[word].begin(); it != pThis->freqDictionary[word].end(); it++)
      {
        if (it->docId == id)
        {
          found = true;
          it->count++;
          break;
        }
      }
      if (!found)
      {
        Entry newEntry;
        newEntry.docId = id;
        newEntry.count = 1;
        pThis->freqDictionary[word].push_back(newEntry);
      }
      pThis->dictLock.unlock();
    }
  }while (queueNotEmpty);
}

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> inputDocs)
{
  const int maxThreads = 10;
  std::queue<std::pair<size_t, std::string*>> inputQueue;
  docs = inputDocs;
  size_t id = 0;
  for (auto it = docs.begin(); it != docs.end(); it++)
  {
    inputQueue.push(std::make_pair(id++, &(*it)));
  }
  std::mutex queueLock;
  std::thread *updateThreads[maxThreads];
  for (int i = 0; i < maxThreads; i++)
    updateThreads[i] = new std::thread(InvertedIndex::UpdateDocumentTask, this, &inputQueue, &queueLock);
  for (int i = 0; i < maxThreads; i++)
    updateThreads[i]->join();
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word)
{
  return freqDictionary[word];
}