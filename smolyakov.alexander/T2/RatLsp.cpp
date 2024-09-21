#include "RatLsp.hpp"
#include <istream>
#include "StructInputSeparator.hpp"

std::istream& smolyakov::operator >> (std::istream& inputStream, smolyakov::RatLsp&& data)
{
  std::istream::sentry guard(inputStream);
  if (!guard)
  {
    return inputStream;
  }

  inputStream >> smolyakov::StructInputSeparator{'('} >> smolyakov::StructInputSeparator{':'}
              >> smolyakov::StructInputSeparator{'N'}
              >> data.value.first
              >> smolyakov::StructInputSeparator{':'}
              >> smolyakov::StructInputSeparator{'D'}
              >> data.value.second
              >> smolyakov::StructInputSeparator{':'} >> smolyakov::StructInputSeparator{')'};

  return inputStream;
}
