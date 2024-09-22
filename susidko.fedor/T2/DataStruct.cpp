#include "DataStruct.hpp"

#include <iostream>
#include <iomanip>
#include <limits>
namespace susidko
{
  long long DataStruct::getKey1() const
  {
    return key1_;
  }
  std::string DataStruct::getKey2() const
  {
    return key2_;
  }
  std::string DataStruct::getKey3() const
  {
    return key3_;
  }

  std::istream & operator>>(std::istream & in, DataStruct & value)
  {
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    using del = DelimiterI;
    bool flag = 0;
    DataStruct data;
    {
      in >> del{'('};
      std::string keyX;
      for (int i = 0; i < 3; i++)
      {
        if (flag == 0)
        {
          in >> del{':'} >> keyX;
        }
        else
        {
          in >> keyX;
          flag = 0;
        }
        if (keyX == "key1")
        {
          in >> LongLong_{data.key1_} >> del{'l'} >> del{'l'};
        }
        else if (keyX == "key2")
        {
          in >> del{'0'} >> del{'b'} >> UnsignedLLBin_{data.key2_};
          flag = 1;
        }
        else if (keyX == "key3")
        {
          in >> del{'"'} >> String_{data.key3_};
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
      }
      if (flag == 0)
      {
        in >> del{':'} >> del{')'};
      }
      else
      {
        in >> del{')'};
        flag = 0;
      }
    }
    if (in)
    {
      value = data;
    }
    return in;
  }

  std::ostream & operator<<(std::ostream & out, const DataStruct & value)
  {
    std::ostream::sentry guard(out);
    if (!guard)
    {
      return out;
    }
    out << "(:key1 " << std::fixed << std::setprecision(1) << value.key1_ << "ll:key2 0b"
    << value.key2_  << ":key3 \"" << value.key3_ << "\":)";
    return out;
  }
  bool compareStructs(const DataStruct& first, const DataStruct& second)
  {
    if (first.getKey1() == second.getKey1())
    {
      if (first.getKey2() == second.getKey2())
      {
        return (first.getKey3() < second.getKey3());
      }
      else
      {
        return (first.getKey2() < second.getKey2());
      }
    }
    else
    {
      return (first.getKey1() < second.getKey1());
    }
  }
}


