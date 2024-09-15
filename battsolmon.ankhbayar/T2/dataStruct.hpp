#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <regex>
#include <iomanip>

namespace ankhbayar
{
  bool isULL_OCT(const std::string& str);
  bool isULL_HEX(const std::string& str);
  bool isString(const std::string& str);

  struct DataStruct
  {
    unsigned long long key1; //ULL OCT 01001; 076
    unsigned long long key2; //ULL HEX 0xFFFA; 0x0100f
    std::string key3;
  };

  std::istream& operator>>(std::istream& in, DataStruct& ds);
  std::ostream& operator<<(std::ostream& out, const DataStruct& ds);

  std::pair<std::string, std::string> getNextPair(std::strings& s);

  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
  private:
    std::basic_ios<char>& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
  };
}
#endif
