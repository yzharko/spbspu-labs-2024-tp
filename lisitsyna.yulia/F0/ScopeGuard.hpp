#ifndef SCOPEGUARD_HPP
#define SCOPEGUARD_HPP

#include <iostream>

namespace lisitsyna
{
  class iofmtguard
  {
    public:
      explicit iofmtguard(std::basic_ios< char >& s);
      ~iofmtguard();

    private:
      std::basic_ios< char >& s_;
      std::streamsize precision_;
      std::basic_ios< char >::fmtflags fmt_;
  };
}
#endif
