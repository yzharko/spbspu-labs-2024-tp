#include "comparator.hpp"

bool ponomarev::compare_entry(const ponomarev::Data &e1, const ponomarev::Data &e2)
{
  if (e1.key1 != e2.key1)
  {
    return (e1.key1 < e2.key1);
  }
  else if (e1.key2 != e2.key2)
  {
    return (std::stoull(e1.key2) < std::stoull(e2.key2));
  }
  return (e1.key3.length() < e2.key3.length());
}
