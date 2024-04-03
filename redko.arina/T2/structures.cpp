#include "structures.hpp"
#include "delimeter.hpp"

std::istream & redko::operator>>(std::istream & in, LongLongIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> dest.ref >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
}

std::istream & redko::operator>>(std::istream & in, ComplexIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double re = 0;
  double im = 0;
  in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' } >> re >> im >> DelimiterIO{')'};
  if (in)
  {
    dest.ref.real(re);
    dest.ref.imag(im);
  }
  return in;
}

std::istream & redko::operator>>(std::istream & in, StringIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}
