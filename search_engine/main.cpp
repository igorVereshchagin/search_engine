#include <iostream>
#include "ConverterJSON.h"

int main()
{
  ConverterJSON conv;
  std::vector<std::string> list = conv.GetTextDocuments();
  return 0;
}
