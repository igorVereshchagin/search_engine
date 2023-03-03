//
// Created by igora on 21.07.2022.
//

#pragma once
#include <vector>
#include <string>
#include "nlohmann/json.hpp"
#include <exception>

class MissingConfig : public std::exception {};
class EmptyConfig : public std::exception 
{
public:
  EmptyConfig(const std::string& str): std::exception(), details(str){}
  const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT  {  return details.c_str();  }
private:
  std::string details;
};

class ConverterJSON
{
public:
  ConverterJSON();
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
  nlohmann::json configDict;
  static void readDict(const nlohmann::json &dict, std::vector<std::string> &list)
  {
    for (auto it = dict.begin(); it != dict.end(); it++)
      list.push_back(it.value());
  }
};


