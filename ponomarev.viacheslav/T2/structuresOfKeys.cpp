#include "structuresOfKeys.hpp"
#include "delimiter.hpp"
#include <cmath>

std::istream &ponomarev::operator>>(std::istream &in, DoubleIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string numberStr;
  std::string degreeStr;
  char symbol = '0';
  char sign;
  const char temp = 'e';
  in >> symbol;
  numberStr += symbol;
  numberStr += '.';
  in >> symbol;
  if (symbol != '.')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> symbol;

  while (std::isdigit(symbol))
  {
    numberStr += symbol;
    in >> symbol;
  }

  symbol = tolower(symbol);
  if (symbol == temp)
  {
    in >> sign;
  }
  else
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> symbol;

  while (std::isdigit(symbol))
  {
    degreeStr += symbol;
    in >> symbol;
  }

  if (symbol != ':')
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  double numberDoub = std::stod(numberStr);
  double degreeInt = std::stoi(degreeStr);
  if (sign == '+')
  {
    dest.ref = numberDoub * std::pow(10, degreeInt);
  }
  else if (sign == '-')
  {
    dest.ref = numberDoub * std::pow(10, -degreeInt);
  }
  else
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream &ponomarev::operator>>(std::istream &in, LongLongIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::getline(in >> DelimiterIO{ '0' } >> DelimiterIO{ 'b' }, dest.ref, ':');
  return in;
}

std::istream &ponomarev::operator>>(std::istream &in, StringIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}








