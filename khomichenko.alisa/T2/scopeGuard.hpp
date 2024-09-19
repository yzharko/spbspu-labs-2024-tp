#ifndef SCOPE_GUARD_HPP
#define SCOPE_GUARD_HPP

#include <ios>

namespace khomichenko
{
  class Guard
  {
    public:
      Guard(std::basic_ios< char > &s);
      ~Guard();
    private:
      std::basic_ios< char > &s_;
      char fill_;
      std::streamsize precision_;
      std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif
