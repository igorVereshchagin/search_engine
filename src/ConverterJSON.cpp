//
// Created by igora on 21.07.2022.
//

#include "ConverterJSON.h"
#include <iostream>
#include <fstream>

ConverterJSON::ConverterJSON()
{
  std::ifstream configFile(".\\config.json");
  if (!configFile.is_open())
    throw (MissingConfig());
  configFile >> configDict;
  configFile.close();
  auto configIt = configDict.find("config");
  if (configIt == configDict.end())
    throw (EmptyConfig("no config section!"));
  std::string name;
  if (configIt->find("name") != configIt->end())
    name = configIt->find("name").value();
  std::cout << "Starting " << name << std::endl;
}

std::vector<std::string> ConverterJSON::GetTextDocuments()
{
  std::vector<std::string> docList;
  std::vector<std::string> fileList;

  auto filesIt = configDict.find("files");
  if (filesIt != configDict.end())
    readDict(filesIt.value(), fileList);
  for (auto itFileList = fileList.begin(); itFileList != fileList.end(); itFileList++)
  {
    std::string docStr;
    std::ifstream docFile(*itFileList);
    if (docFile.is_open())
    {
      int counter = 0;
      while(!docFile.eof())
      {
        std::string word;
        docFile >> word;
        if (word.length() <= 100)
          docStr += " " + word;
        if (++counter == 1000)
          break;
      }
      docFile.close();
    }
    else
    {
      std::cout << "Can't open file: " << *itFileList << std::endl;
    }
    docList.push_back(docStr);
  }
  return docList;
}

int ConverterJSON::GetResponsesLimit()
{
  auto it = configDict.find("config").value().find("max_responses");
  if (it == configDict.find("config").value().end())
    throw(EmptyConfig("no max_responses!"));
  else
    return it.value();
}

std::vector<std::string> ConverterJSON::GetRequests()
{
  std::vector<std::string> reqList;
  nlohmann::json reqDict;
  std::ifstream reqFile(".\\requests.json");
  if (reqFile.is_open())
  {
    reqFile >> reqDict;
    reqFile.close();
  }
  auto filesIt = reqDict.find("requests");
  if (filesIt != reqDict.end())
    readDict(filesIt.value(), reqList);
  return reqList;
}

void ConverterJSON::putAnswers(std::vector<std::vector<std::pair<int, float>>> answers)
{
  nlohmann::json ansDict;
  int maxResp = GetResponsesLimit();
  for (int i = 0; i < answers.size(); i++)
  {
    std::string respName = "response" + std::to_string(i + 1);
    ansDict["answers"][respName]["result"] = answers[i].begin() != answers[i].end() ? "true" : "false";
    int cnt = 0;
    for (auto ansIt = answers[i].begin(); cnt < maxResp && ansIt != answers[i].end(); cnt++, ansIt++)
    {
      nlohmann::json tDict;
      tDict["docid"] = ansIt->first;
      tDict["rank"] = ansIt->second;
      ansDict["answers"][respName]["relevance"].push_back(tDict);
    }
  }
  std::ofstream ansFile(".\\answers.json");
  if (ansFile.is_open())
  {
    ansFile << ansDict;
    ansFile.close();
  }
  else
  {
    std::cout << "Unable to open file: answers.json" << std::endl;
  }
}
