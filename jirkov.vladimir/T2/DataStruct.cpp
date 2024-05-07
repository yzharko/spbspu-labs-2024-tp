#include "DataStruct.hpp"

std::istream & jirkov::operator>>(std::istream &in, DataStruct &value)
{
  //some
  return in;
}

std::ostream & jirkov::operator<<(std::ostream & out, const DataStruct &value)
{
  //some2
  return out;
}

bool jirkov::operator>(const DataStruct &left, const DataStruct &right)
{
 //some3
  return false;
}

bool jirkov::operator<(const DataStruct &left, const DataStruct &right)
{
  return !(left > right);
}
