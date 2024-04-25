#ifndef SCOPEGUARD
#define SCOPEGUARD
#include <ios>

namespace kovshikov
{
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios< char > &s) explicit;
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
