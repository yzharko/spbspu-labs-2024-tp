#include "StringWrapper.hpp"
#include <istream>
#include <string>
#include "StructInputSeparator.hpp"


std::istream& smolyakov::operator >> (std::istream& inputStream, smolyakov::StringWrapper&& data)
{
  std::istream::sentry guard(inputStream);
  if (!guard)
  {
    return inputStream;
  }

  return std::getline(inputStream >> smolyakov::StructInputSeparator{'"'}, data.value, '"');
}
