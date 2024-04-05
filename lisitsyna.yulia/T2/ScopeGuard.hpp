#ifndef STREAM_GUARD_HPP
#define STREAM_GUARD_HPP
#include <ios>

namespace lisitsyna
{
  class StreamGuard
  {
    public:
      StreamGuard(std::basic_ios<char>& s):
        s_(s),
        fill_(s.fill()),
        precision_(s.precision()),
        flags(s.flags())
      {}
      ~StreamGuard()
      {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(flags);
      }
    private:
      char fill_
      std::basic_ios<char>& s_;
      std::streamsize precision_;
      std::basic_ios<char>::fmtflags flags;
  };
}
#endif
