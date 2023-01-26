//
// Created by igora on 09.10.2022.
//

#pragma once

#include <string>
#include <vector>
#include <map>
#include <queue>
#include <mutex>

struct Entry {
  size_t docId, count;
  // Данный оператор необходим для проведения тестовых сценариев
  bool operator == (const Entry& other) const {
    return (docId == other.docId && count == other.count);
  }
};

class InvertedIndex
{
public:
  InvertedIndex() = default;
  InvertedIndex(const InvertedIndex& index): docs(index.docs), freqDictionary(index.freqDictionary){};
/**
* Обновить или заполнить базу документов, по которой будем совершать поиск
* @param texts_input содержимое документов
*/
  void UpdateDocumentBase(std::vector<std::string> inputDocs);
/**
  * Метод определяет количество вхождений слова word в загруженной базе документов
  * @param word слово, частоту вхождений которого необходимо определить
  * @return возвращает подготовленный список с частотой слов
  */
  std::vector<Entry> GetWordCount(const std::string& word);

private:
  static void UpdateDocumentTask(InvertedIndex* pThis, std::queue<std::pair<size_t, std::string*>> *inQueue, std::mutex *queueLock, std::mutex *dictLock);
  std::vector<std::string> docs;
  std::map<std::string, std::vector<Entry>> freqDictionary;
};


