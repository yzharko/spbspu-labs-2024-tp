#include "InpOutTypes.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include "Iofmtguard.hpp"

std::istream& zasulsky::operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char exp = '0';
  in >> exp;
  if (in && exp != dest.exp)
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}
std::istream& zasulsky::operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (size_t i = 0; i < dest.exp.length(); ++i)
  {
    in >> DelimiterIO{ dest.exp[i] };
  }
  return in;
}
std::istream& zasulsky::operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.exp, '"');
}
std::istream& zasulsky::operator>>(std::istream& in, SllIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.num >> zasulsky::LabelIO{ "ll" };
}
std::istream& zasulsky::operator>>(std::istream& in, DblI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  int mantisa = 0;
  int numb = 0;
  int pow = 0;
  in >> mantisa >> DelimiterIO{ '.' };
  in >> numb >> DelimiterIO{ 'e' } >> pow;
  dest.num = (mantisa * 1.0 + numb * 0.01) * std::pow(10, pow);
  return in;
}
std::ostream& zasulsky::operator<<(std::ostream& out, const DblO&& dest)
{
  std::ostream::sentry sentry(out);
  iofmtguard guard(out);
  if (!sentry)
  {
    return out;
  }
  double numb = dest.num;
  int pow = 0;
  while (std::abs(numb) < 1)
  {
    numb *= 10;
    pow--;
  }
  while (std::abs(numb) >= 10)
  {
    numb /= 10;
    pow++;
  }
  out << std::fixed << std::setprecision(1);
  out << numb << 'e' << std::showpos << pow;
  return out;
}
