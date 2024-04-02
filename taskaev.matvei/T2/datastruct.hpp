#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <complex>
#include <string>

struct DataStruct
{
  unsigned long long key1;
  std::complex< double > key2;
  std::string key3;
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
}

std::istream& operator >> (std::istream& is, DataStruct& dest);
std::ostream& operator << (std::ostream& out, const DataStruct& dest);
bool operator<(const DataStruct& left, const DataStruct& right);

#endif
