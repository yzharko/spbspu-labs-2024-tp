#include "delimiters.hpp"

std::istream &mihalchenko::operator>>(std::istream &is, DelimiterIO &&exp)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = 0;
  is >> c;
  if (c != exp.expected)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream &mihalchenko::operator>>(std::istream &in, UllBinIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string strForBinUllIO = "";
  std::getline(in >> DelimiterIO{'0'} >> DelimiterIO{'b'}, strForBinUllIO, ':');

  dest.ref = strForBinUllIO;
  return in;
}

std::istream &mihalchenko::operator>>(std::istream &in, ComplexIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  double real = 0;
  double imag = 0;
  in >> DelimiterIO{'#'} >> DelimiterIO{'c'} >> DelimiterIO{'('} >> real >> imag >> DelimiterIO{')'};
  if (in)
  {
    dest.ref.real(real);
    dest.ref.imag(imag);
  }
  return in;
}

std::istream &mihalchenko::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{'"'}, dest.ref, '"');
}
