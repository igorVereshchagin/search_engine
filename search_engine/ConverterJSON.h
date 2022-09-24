//
// Created by igora on 21.07.2022.
//

#pragma once
#include <vector>
#include <string>
#include "nlohmann/json.hpp"
#include <exception>

class MissingConfig : public std::exception {};
class EmptyConfig : public std::exception {};

class ConverterJSON
{
public:
  ConverterJSON() = default;
///**
//* Метод получения содержимого файлов
//* @return Возвращает список с содержимым файлов перечисленных
//* в config.json
//*/
  std::vector<std::string> GetTextDocuments();
///**
//* Метод считывает поле max_responses для определения предельного
//* количества ответов на один запрос
//* @return
//*/
  int GetResponsesLimit();
///**
//* Метод получения запросов из файла requests.json
//* @return возвращает список запросов из файла requests.json
//*/
  std::vector<std::string> GetRequests();
///**
//* Положить в файл answers.json результаты поисковых запросов
//*/
  void putAnswers(std::vector<std::vector<std::pair<int, float>>> answers);

private:
  std::string name = "default name";
  std::string version = "0.1";
  int maxResponses = 5;
  static void readDict(const nlohmann::json &dict, std::vector<std::string> &list)
  {
    for (auto it = dict.begin(); it != dict.end(); it++)
      list.push_back(it.value());
  }
  auto parseConfig(const nlohmann::json &dict, const std::string key)
  {
    for (auto it = dict.begin(); it != dict.end(); it++)
      if (it.key() == key)
        return it.value();
    return dict.end().value();
  }
};


