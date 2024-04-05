#ifndef GUARD_HPP
#define GUARD_HPP

namespace sadofeva
{
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios<char> & s);
    ~iofmtguard();
  private:
    std::basic_ios<char> & s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtdlags fmt_;
  };
}
