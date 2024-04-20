#ifndef DATASTRUST
#define DATASTRUCT
#include <string>
#include <utility>
#include <iostream>
#include "io_structures.hpp"
#include "scope_guard.hpp"

namespace kovshikov
{
  struct DataStruct
  {
    char key1;
    std::pair< long long, unsigned long long > key2;
    std::string key3;
  };

  std::istream & operator>>(std::istream &is, DataStruct &value);
  std::ostream & operator<<(std::ostream & out, const DataStruct &value);
}

std::istream & kovshikov::operator>>(std::istream &is, DataStruct &value)
{
  std::istream::sentry guard(is);
  if(!guard)
  {
    return is;
  }
  std::string key;
  DataStruct input;
  is >> Del{'('} >> Del{':'} >> key;
  for(int i = 0; i < 3; i++)
  {
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
  }
  is >> Del{')'};
  if(is)
  {
    value = input;
  }
  //учесть игнорирование неправильного ввода;
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
  out << "(:key1 " << value.key1 << ":key2 (:N " << value.key2.first
  << ":D " << value.key2.second << ":):key3 " << value.key3 << ":)";
  return out;
}

#endif
