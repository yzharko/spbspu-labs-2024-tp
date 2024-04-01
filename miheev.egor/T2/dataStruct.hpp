#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <utility>
#include <string>
#include <iostream>

namespace miheev
{
  using real = std::pair<long long, unsigned long long>;
  struct DataStruct
  {
    long long key1;
    real key2;
    std::string key3;
  };
  struct DelimiterIO
  {
    char expected;
  };
  struct LongLongIO
  {
    long long& ref;
  };
  struct RealIO
  {
    real& ref;
  };
  struct StringIO
  {
    std::string& ref;
  };
  struct labelIO
  {
    std::string exp;
  };
}

std::istream& operator>>(std::istream& is, miheev::DelimiterIO&& exp);
std::istream &operator>>(std::istream &in, miheev::LongLongIO&& exp);
std::istream &operator>>(std::istream &in, miheev::RealIO&& exp);
std::istream &operator>>(std::istream &in, miheev::labelIO&& exp );
std::istream &operator>>(std::istream &in, miheev::StringIO&& exp );
std::istream& operator>>(std::istream& is, miheev::DataStruct& value);
std::ostream& operator<<(std::ostream& out, const miheev::DataStruct& value);
std::ostream& operator<<(std::ostream& out, const miheev::real&);

#endif
