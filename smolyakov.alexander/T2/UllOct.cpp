#include "UllOct.hpp"
#include <iostream>

std::istream& operator >> (std::istream& inputStream, smolyakov::UllOct&& data)
{
  std::istream::sentry guard(inputStream);
  if (!guard)
  {
    return inputStream;
  }

  return inputStream >> std::oct >> data.value;
}
