#include "Delimeter.hpp"

namespace lisitsyna
{
  DelimeterIO::DelimeterIO(char src) :
     exp(src)
  {}

  LabelIO::LabelIO(std::string src) :
     exp(src)
  {}

  std::istream& operator>>(std::istream& in, DelimeterIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0'; in >> c;
    if (in && (c != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    std::string data = "";
    if ((in >> data) && (data != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
  }
}
