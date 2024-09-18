#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <iostream>

namespace batunov
{
  struct DataStruct
  {
    double key1;
    double key2;
    std::string key3;
  };
  struct DelimiterIO
  {
    char exp;
  };

  struct DblLitIO
  {
    double &ref;
  };

  struct DblSciIO
  {
    double &ref;
  };
  struct StringIO
  {
    std::string &ref;
  };

  struct DelStrIO
  {
    std::string exp;
  };

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char > &s);
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };

  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
  std::istream &operator>>(std::istream &in, DblSciIO &&dest);
  std::istream &operator>>(std::istream &in, DblLitIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, DelStrIO &&dest);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &src);
}
#endif
