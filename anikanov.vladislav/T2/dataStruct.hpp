#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iosfwd>
#include <string>

namespace anikanov {
  struct DataStruct {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };
  struct DelimiterIO {
    char exp;
  };

  struct UllLitIO {
    unsigned long long &ref;
  };

  struct UllBinIO {
    unsigned long long &ref;
  };
  struct StringIO {
    std::string &ref;
  };

  struct DelStrIO {
    std::string exp;
  };

  class iofmtguard {
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
  std::istream &operator>>(std::istream &in, UllBinIO &&dest);
  std::istream &operator>>(std::istream &in, UllLitIO &&dest);
  std::istream &operator>>(std::istream &in, StringIO &&dest);
  std::istream &operator>>(std::istream &in, DelStrIO &&dest);
  std::istream &operator>>(std::istream &in, DataStruct &dest);
  std::ostream &operator<<(std::ostream &out, const DataStruct &src);
}

#endif
