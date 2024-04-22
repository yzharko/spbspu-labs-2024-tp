#include "Keys.hpp"
#include <ios>
#include "Delimeter.hpp"
#include "ScopeGuard.hpp"

std::istream & reznikova::operator>>(std::istream & is, reznikova::ULLOCT && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  is >> std::oct >> value.num;
  return is;
}

std::istream & reznikova::operator>>(std::istream & is, reznikova::CMPLSP && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  using del = Delimiter;
  double real, imag;
  is >> del{'#'} >> del{'c'} >> del{'('} >> real >> imag >> del{')'};
  if (is)
  value.num.real(real);
  value.num.real(imag);
  return is;
}

std::istream & reznikova::operator>>(std::istream & is, reznikova::STR && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  is >> value.num;
  return is;
}
