#include "Keys.hpp"
#include "Delimeter.hpp"
#include "ScopeGuard.hpp"

std::istream & reznikova::operator>>(std::istream & is, reznikova::ULLOCT && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  std::string str;
  is >> std::oct >> str;
  value.len = str.length();
  value.num = stoull(str);
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
  double real;
  double imag;
  is >> del{'#'} >> del{'c'} >> del{'('} >> real >> imag >> del{')'};
  value.num.real(real);
  value.num.imag(imag);
  return is;
}

std::istream & reznikova::operator>>(std::istream & is, reznikova::STR && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  return std::getline(is >> Delimiter{ '"' }, value.num, '"');
}

std::ostream & reznikova::operator<<(std::ostream & out, const reznikova::ULLOCT && value)
{
  std::ostream::sentry sentry(out);
  if(!sentry)
  {
    return out;
  }
  iofmtguard guard(out);
  while (value.len > std::to_string(value.num).length())
  {
    out << "0";
  }
  out << std::oct << value.num;
  return out;
}
