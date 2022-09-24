//
// Created by igora on 21.07.2022.
//

#include "ConverterJSON.h"
#include <iostream>
#include <fstream>


std::vector<std::string> ConverterJSON::GetTextDocuments()
{
  std::vector<std::string> docList;
  nlohmann::json configDict;
  std::ifstream configFile("..\\config.json");
  if (!configFile.is_open())
    throw (MissingConfig());
  configFile >> configDict;
  configFile.close();
  auto filesIt = configDict.find("files");
  if (filesIt != configDict.end())
    readDict(filesIt.value(), docList);
  return docList;
}

int ConverterJSON::GetResponsesLimit()
{
  nlohmann::json configDict;
  std::ifstream configFile("..\\config.json");
  if (!configFile.is_open())
    throw (MissingConfig());
  configFile >> configDict;
  configFile.close();
  int maxResp = 0;
  auto configIt = configDict.find("config");
  if (configIt != configDict.end())
    maxResp = parseConfig(configIt.value(), "max_responses");
  else
    throw (EmptyConfig());
  return maxResp;
}

std::vector<std::string> ConverterJSON::GetRequests()
{
  std::vector<std::string> reqList;
  nlohmann::json reqDict;
  std::ifstream reqFile("..\\requests.json");
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
  for (int i = 0; i < answers.size(); i++)
  {
    std::string respName = "response" + std::to_string(i + 1);
    auto ansIt = answers[i].begin();
    ansDict["answers"][respName]["result"] = ansIt != answers[i].end() ? "true" : "false";
    for (; ansIt != answers[i].end(); ansIt++)
    {
      nlohmann::json tDict;
      tDict["docid"] = ansIt->first;
      tDict["rank"] = ansIt->second;
      ansDict["answers"][respName]["relevance"].push_back(tDict);
    }
  }
  std::ofstream ansFile("..\\answers.json");
  if (ansFile.is_open())
  {
    ansFile << ansDict;
    ansFile.close();
  }
}
