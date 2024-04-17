#ifndef STREAMGUARD_HPP
#define STREAMGUARD_HPP
#include <iostream>

namespace {
  class StreamGuard
  {
  public:
    explicit StreamGuard(std::basic_ios<char>& s) noexcept;
    ~StreamGuard();
  private:
    std::basic_ios<char>& s_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags flags_;
  };

  StreamGuard::StreamGuard(std::basic_ios<char>& s) noexcept :
    s_(s),
    precision_(s.precision()),
    flags_(s.flags())
  {};

  StreamGuard::~StreamGuard()
  {
    s_.precision(precision_);
    s_.flags(flags_);
  }
}

#endif