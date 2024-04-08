#include "dataStruct.hpp"
#include <iostream>
#include <iomanip>

std::istream & sobolevsky::operator>>(std::istream & in, sobolevsky::DataStruct & value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  using del = sobolevsky::Delimitr_;
  DataStruct data;
  {
    in >> del{'('};
    std::string keyX;
    for (int i = 0; i < 3; i++)
    {
      in >> del{':'} >> keyX;
      if (keyX == "key1")
      {
        in >> Double_{data.key1} >> del{'d'};
      }
      else if (keyX == "key2")
      {
        in >> del{'\''} >> Char_{data.key2} >> del{'\''};
      }
      else if (keyX == "key3")
      {
        in >> del{'"'} >> String_{data.key3};
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> del{':'} >> del{')'};
  }
  if (in)
  {
    value = data;
  }
  return in;
}

std::ostream & sobolevsky::operator<<(std::ostream & out, const sobolevsky::DataStruct & value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 " << std::fixed << std::setprecision(1) << value.key1 << "d:key2 '"
  << value.key2 << "'" << ":key3 \"" << value.key3 << "\":)";
  return out;
}

bool sobolevsky::operator<(const sobolevsky::DataStruct & first, const sobolevsky::DataStruct & second)
{
  if (first.key1 != second.key1)
  {
    return first.key1 < second.key1;
  }

  if (first.key2 != second.key2)
  {
    return first.key2 < second.key2;
  }

  return first.key3.size() < second.key3.size();
}
