#include <iostream>
#include "ConverterJSON.h"
#include "InvertedIndex.h"
#include "SearchServer.h"

int main()
{
  try
  {
    ConverterJSON conv;
    InvertedIndex index;
    index.UpdateDocumentBase(conv.GetTextDocuments());
    SearchServer srv(index);
    std::vector<std::vector<RelativeIndex>> relIndex = srv.search(conv.GetRequests());
    std::vector<std::vector<std::pair<int, float>>> answersList;
    for (auto itRelIndex = relIndex.begin(); itRelIndex != relIndex.end(); itRelIndex++)
    {
      std::vector<std::pair<int, float>> answer;
      for (auto itItRelIndex = itRelIndex->begin(); itItRelIndex != itRelIndex->end(); itItRelIndex++)
        answer.push_back(std::make_pair(itItRelIndex->doc_id, itItRelIndex->rank));
      answersList.push_back(answer);
    }
    conv.putAnswers(answersList);
  }
  catch(const MissingConfig& e)
  {
    std::cerr << "MissingConfig" << std::endl;
  }
  catch(const EmptyConfig& e)
  {
    std::cerr << "EmptyConfig: " << e.what() << std::endl;
  }
      
  return 0;
}
