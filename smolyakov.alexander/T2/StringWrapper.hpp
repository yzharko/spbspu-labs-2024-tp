#ifndef STRING_WRAPPER_HPP
#define STRING_WRAPPER_HPP
#include <istream>
#include <string>

namespace smolyakov
{
  struct StringWrapper
  {
    std::string& value;
  };
}

std::istream& operator >> (std::istream& inputStream, smolyakov::StringWrapper&& data);

#endif
