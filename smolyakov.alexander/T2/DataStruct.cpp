#include "DataStruct.hpp"
#include <istream>
#include <string>
#include "StructInputSeparator.hpp"
#include "UllOct.hpp"
#include "RatLsp.hpp"
#include "StringWrapper.hpp"

std::istream& smolyakov::operator >> (std::istream& inputStream, smolyakov::DataStruct& data)
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
      inputStream >> smolyakov::RatLsp{tmpDataHolder.key1};
    }
    else if (fieldName == "key2")
    {
      inputStream >> smolyakov::UllOct{tmpDataHolder.key2};
    }
    else if (fieldName == "key3")
    {
      inputStream >> smolyakov::StringWrapper{tmpDataHolder.key3};
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
