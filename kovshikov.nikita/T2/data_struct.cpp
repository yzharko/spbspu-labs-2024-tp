#include "data_struct.hpp"

std::istream & kovshikov::operator>>(std::istream &is, DataStruct &value)
{
  std::istream::sentry guard(is);
  if(!guard)
  {
    return is;
  }
  iofmtguard fmtguard(is);
  std::string key = "";
  DataStruct input;
  is >> Del{'('} >> Del{':'};
  for(int i = 0; i < 3; i++)
  {
    is >> key;
    if(key == "key1")
    {
      is >> Chr{input.key1} >> Del{':'};
    }
    else if(key == "key2")
    {
      is >> Pair{input.key2} >> Del{':'};
    }
    else if(key == "key3")
    {
      is >> Str{input.key3} >> Del{':'};
    }
    else
    {
      is.setstate(std::ios::failbit);
    }
  }
  is >> Del{')'};
  if(is)
  {
    value = input;
  }
  return is;
}

std::ostream & kovshikov::operator<<(std::ostream & out, const DataStruct &value)
{
  std::ostream::sentry guard(out);
  if(!guard)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:key1 " << '\'' << value.key1 << '\'' << ":key2 (:N " << value.key2.first
  << ":D " << value.key2.second << ":):key3 " << "\"" << value.key3 << "\":)";
  return out;
}

bool kovshikov::operator>(const DataStruct &left, const DataStruct &right)
{
  if(left.key1 != right.key1)
  {
    int numberLeft = static_cast< int >(left.key1);
    int numberRight = static_cast< int >(right.key1);
    return numberLeft > numberRight;
  }
  else if(left.key2 != right.key2)
  {
    if(left.key2.first != right.key2.first)
    {
      return left.key2.first > right.key2.first;
    }
    else
    {
      return left.key2.second > right.key2.second;
    }
  }
  else if(left.key3.length() != right.key3.length())
  {
    return left.key3.length() > right.key3.length();
  }
  else
  {
    return false;
  }
}

bool kovshikov::operator<(const DataStruct &left, const DataStruct &right)
{
  return !(left > right);
}
