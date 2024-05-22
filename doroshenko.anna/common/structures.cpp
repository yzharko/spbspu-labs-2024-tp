#include "structures.hpp"
#include <iomanip>

std::istream& doroshenko::operator>>(std::istream& input, DelimiterIO&& dest)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  char c = '0';
  input >> c;
  if (input && (c != dest.exp))
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::istream& doroshenko::operator>>(std::istream& input, DoubleIO&& dest)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  if (!(input >> dest.ref) || dest.ref == 0)
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::istream& doroshenko::operator>>(std::istream& input, CharIO&& dest)
{
  std::istream::sentry guard(input);
  if (!guard)
  {
    return input;
  }
  using separator = DelimiterIO;
  if (!(input >> separator{ '\'' } >> dest.ref >> separator{ '\'' }) || !std::isalpha(dest.ref))
  {
    input.setstate(std::ios::failbit);
  }
  return input;
}

std::istream& doroshenko::operator>>(std::istream& input, StringIO&& dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  return std::getline(input >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::ostream& doroshenko::outDblSci(std::ostream& output, double number)
{
  int mantissa = 0;
  char sign = '0';
  if (number >= 1.0)
  {
    while (number > 1.0)
    {
      number /= 10;
      mantissa++;
    }
    sign = '+';
  }
  else
  {
    while (number < 1.0 && mantissa < 10)
    {
      number *= 10;
      mantissa++;
    }
    sign = '-';
  }
  output << std::fixed << std::setprecision(1) << number << 'e' << sign << mantissa;
  return output;
}
