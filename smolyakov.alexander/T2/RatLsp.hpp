#ifndef RAT_LSP_H
#define RAT_LSP_H
#include <istream>
#include <utility>

namespace smolyakov
{
  struct RatLsp
  {
    std::pair<long long, unsigned long long>& value;
  };
}

std::istream& operator >> (std::istream& inputStream, smolyakov::RatLsp&& data);

#endif
