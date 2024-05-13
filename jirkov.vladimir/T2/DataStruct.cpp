#include "DataStruct.hpp"

namespace jirkov
{
  bool operator>(const DataStruct &left, const DataStruct &right)
  {
    if(left.key1 != right.key1)
    {
      return left.key1 > right.key1;
    }
    else if (left.key2 != right.key2)
    {
      return left.key2 > right.key2;
    }
    else if (left.key3.length() != right.key3.length())
    {
      return left.key3.length() > right.key3.length();
    }
    else
    {
      return false;
    }
  }
  bool operator<(const DataStruct &left, const DataStruct &right)
  {
    return !(left > right);
  }
}
