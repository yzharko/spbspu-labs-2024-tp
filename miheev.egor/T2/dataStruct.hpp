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
  std::istream& operator>>(std::istream& is, DelimiterIO&&);
  std::istream& operator>>(std::istream &in, LongLongIO&&);
  std::istream& operator>>(std::istream &in, RealIO&&);
  std::istream& operator>>(std::istream &in, LabelIO&&);
  std::istream& operator>>(std::istream &in, StringIO&&);
  std::istream& operator>>(std::istream &in, KeyIO&&);
  std::istream& operator>>(std::istream& is, DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const DataStruct& value);
  std::ostream& operator<<(std::ostream& out, const real&);
  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
  bool operator<(const miheev::real& lhs, const miheev::real& rhs);
}


#endif
