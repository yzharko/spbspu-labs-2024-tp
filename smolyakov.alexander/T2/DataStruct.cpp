#include "DataStruct.hpp"
#include <istream>
#include <string>
#include "StructInputSeparator.hpp"
#include "UllOct.hpp"

std::istream& operator >> (std::istream& inputStream, smolyakov::DataStruct& data)
{
  std::istream::sentry guard(inputStream);
  if (!guard)
  {
    return inputStream;
  }

  smolyakov::DataStruct tmpDataHolder;

  inputStream >> smolyakov::StructInputSeparator{'('};
  std::string fieldName;

  for (int i = 0; i < 3; i++)
  {
    inputStream >> smolyakov::StructInputSeparator{':'} >> fieldName;
    if (fieldName == "key1")
    {
      // TODO: input std::pair
    }
    else if (fieldName == "key2")
    {
      smolyakov::UllOct ullOct = smolyakov::UllOct{tmpDataHolder.key2};
      inputStream >> ullOct;
    }
    else if (fieldName == "key3")
    {
      // TODO: input string
    }
  }

  inputStream >> smolyakov::StructInputSeparator{':'};
  inputStream >> smolyakov::StructInputSeparator{')'};

  if (inputStream)
  {
    data = tmpDataHolder;
  }
  return inputStream;
}
