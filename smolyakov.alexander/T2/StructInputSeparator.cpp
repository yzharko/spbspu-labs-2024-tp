#include "StructInputSeparator.hpp"
#include <iostream>

std::istream& operator >> (std::istream& inputStream, smolyakov::StructInputSeparator&& separator)
{
  std::istream::sentry guard(inputStream);
  if (!guard)
  {
    return inputStream;
  }

  char c = 0;
  inputStream >> c;
  if (c != separator.separatorCharacter)
  {
    inputStream.setstate(std::ios::failbit);
  }

  return inputStream;
}
