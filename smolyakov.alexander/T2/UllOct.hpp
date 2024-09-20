#ifndef ULL_OCT_H
#define ULL_OCT_H
#include <istream>

namespace smolyakov
{
  struct UllOct
  {
    unsigned long long& value;
  };
  std::istream& operator >> (std::istream& inputStream, smolyakov::UllOct&& data);
}

#endif
