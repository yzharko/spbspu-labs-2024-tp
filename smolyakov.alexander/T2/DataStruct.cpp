#include "DataStruct.hpp"
#include <ios>
#include <istream>
#include <ostream>
#include <string>
#include "StructInputSeparator.hpp"
#include "UllOct.hpp"
#include "RatLsp.hpp"
#include "StringWrapper.hpp"
#include "ScopeGuard.hpp"

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

std::ostream& smolyakov::operator << (std::ostream& outputStream, const smolyakov::DataStruct& data)
{
  std::ostream::sentry guard(outputStream);
  if (!guard)
  {
    return outputStream;
  }

  iofmtguard fmtguard(outputStream);
  outputStream << "(:";
  outputStream << "key 1 (:N " << data.key1.first << ":D " << data.key1.second << ":)";
  outputStream << ":key2 0" << std::oct << std::uppercase << data.key2;
  outputStream << ":key3 \"" << data.key3 << "\":)";
  return outputStream;
}

bool smolyakov::operator < (const smolyakov::DataStruct& first, const smolyakov::DataStruct& second)
{
  if (first.key1 != second.key1)
  {
    return first.key1 < second.key1;
  }
  else if (first.key2 != second.key2)
  {
    return first.key2 < second.key2;
  }
  return first.key3.length() < second.key3.length();
}
