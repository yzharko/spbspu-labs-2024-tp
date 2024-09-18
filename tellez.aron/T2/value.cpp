#include "value.hpp"
#include <istream>

std::string removeZeros(std::string str)
{
  str.erase(str.find_last_not_of('0') + 1, std::string::npos);
  if (str.back() == '.')
  {
    str = str + '0';
  }
  return str;
}

std::string printScientific(double number)
{
  std::string out;
  int exp = 0;
  char mark = 0;
  if (number != 0)
  {
    if (number >= 1.0)
    {
      while (number > 1.0)
      {
        number = number / 10;
        exp++;
      }
      mark = '+';
    }
    else
    {
      while (number < 1.0)
      {
        number = number * 10;
        exp++;
      }
      mark = '-';
    }
    out = removeZeros(std::to_string(number)) + "e";
    out += mark + std::to_string(exp);
  }
  else
  {
    out = std::to_string(number);
  }
  return out;
}

std::istream& tellez::operator>>(std::istream& in, DblSci&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double num = 0;
  in >> num;
  if (in)
  {
    value.value = num;
  }
  return in;
}

std::ostream& tellez::operator<<(std::ostream& out, const DoubleSci&& value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << printScientific(value.value);
  return out;
}

std::istream& tellez::operator>>(std::istream& in, StringStr&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Delimeterchar{ '"' };
  std::getline(in, value.value, '"');
  return in;
}

std::istream& tellez::operator>>(std::istream& in, RatLsp&& value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  long long num = 0;
  unsigned long long den = 0;
  using ds = Delimeterstring;
  in >> ds{ "(:n" } >> num >> ds{ ":d" } >> den >> ds{ ":)" };
  if (in)
  {
    value.value.first = num;
    value.value.second = den;
  }
  return in;
}
