#ifndef SCOPEGUARD_HPP
#define SCOPEGUARD_HPP

#include <ios>

namespace lisitsyna
{
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
  private:
    std::basic_ios<char>& s_;
    char fill_;
    std::basic_ios<char>::fmtflags fmt_;
  };
}
#endif
