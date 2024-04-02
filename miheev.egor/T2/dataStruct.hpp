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
  struct LabelIO
  {
    std::string exp;
  };
  struct KeyIO
  {
    std::string& ref;
  };
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char >& s);
    ~iofmtguard();
  private:
    std::basic_ios< char >& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

std::istream& operator>>(std::istream& is, miheev::DelimiterIO&&);
std::istream &operator>>(std::istream &in, miheev::LongLongIO&&);
std::istream &operator>>(std::istream &in, miheev::RealIO&&);
std::istream &operator>>(std::istream &in, miheev::LabelIO&&);
std::istream &operator>>(std::istream &in, miheev::StringIO&&);
std::istream &operator>>(std::istream &in, miheev::KeyIO&&);
std::istream& operator>>(std::istream& is, miheev::DataStruct& value);
std::ostream& operator<<(std::ostream& out, const miheev::DataStruct& value);
std::ostream& operator<<(std::ostream& out, const miheev::real&);

#endif
