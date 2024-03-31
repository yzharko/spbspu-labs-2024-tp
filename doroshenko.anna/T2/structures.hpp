#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include<string>
#include<iostream>
#include<iterator>

namespace doroshenko
{
  struct DataStruct
  {
    double key1;
    char key2;
    std::string key3;
  };

  struct DelimiterIO
  {
    char exp;
  };

  struct DoubleIO
  {
    double& ref;
  };

  struct CharIO
  {
    char& ref;
  };

  struct StringIO
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

  std::istream& operator>>(std::istream& input, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& input, DoubleIO&& dest);
  std::istream& operator>>(std::istream& input, CharIO&& dest);
  std::istream& operator>>(std::istream& input, StringIO&& dest);
  std::istream& operator>>(std::istream& input, DataStruct& dest);
  std::ostream& operator<<(std::ostream& output, const DataStruct& src);
  bool compareStructs(const DataStruct& firstStruct, const DataStruct& secondStruct);
}

#endif
