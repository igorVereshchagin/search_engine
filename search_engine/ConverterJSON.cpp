//
// Created by igora on 21.07.2022.
//

#include "ConverterJSON.h"
#include <iostream>
#include <fstream>
#include <exception>

class MissingConfig : public std::exception {};
class EmptyConfig : public std::exception {};



std::vector<std::string> ConverterJSON::GetTextDocuments()
{
  std::vector<std::string> docList;
  try
  {
    nlohmann::json configDict;
    std::ifstream configFile("..\\config.json");
    if (!configFile.is_open())
      throw (MissingConfig());
    configFile >> configDict;
    configFile.close();
    auto configIt = configDict.find("config");
    if (configIt != configDict.end())
      parseConfig(configIt.value());
    else
      throw (EmptyConfig());
    auto filesIt = configDict.find("files");
    if (filesIt != configDict.end())
      parseFiles(filesIt.value(), docList);
  }
  catch (const MissingConfig &ex)
  {
    std::cout << "Config file is missing" << std::endl;
    docList.clear();
  }
  catch (const EmptyConfig &ex)
  {
    std::cout << "Config file is empty" << std::endl;
    docList.clear();
  }
  return docList;
}

int ConverterJSON::GetResponsesLimit()
{
  return 0;
}

std::vector<std::string> ConverterJSON::GetRequests()
{
  std::vector<std::string> ret;
  return ret;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{

}
