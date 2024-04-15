#include "structures.hpp"
#include <iomanip>

doroshenko::iofmtguard::iofmtguard(std::basic_ios< char >& s) :
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}

doroshenko::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}

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

std::istream& doroshenko::operator>>(std::istream& input, DataStruct& dest)
{
  std::istream::sentry sentry(input);
  if (!sentry)
  {
    return input;
  }
  DataStruct structure;
  {
    using separator = DelimiterIO;
    using dbl = DoubleIO;
    using chr = CharIO;
    using str = StringIO;
    std::string key;
    input >> separator{ '(' };
    for (int i = 0; i < 3; i++)
    {
      input >> separator{ ':' } >> key;
      if (key == "key1")
      {
        input >> dbl{ structure.key1 };
      }
      else if (key == "key2")
      {
        input >> chr{ structure.key2 };
      }
      else if (key == "key3")
      {
        input >> str{ structure.key3 };
      }
      else
      {
        input.setstate(std::ios::failbit);
      }
    }
    input >> separator{ ':' } >> separator{ ')' };
  }
  if (input)
  {
    dest = structure;
  }
  return input;
}

std::ostream& doroshenko::operator<<(std::ostream& output, const DataStruct& src)
{
  std::ostream::sentry sentry(output);
  if (!sentry)
  {
    return output;
  }
  iofmtguard fmtguard(output);
  output << "(:key1 ";
  outDblSci(output, src.key1);
  output << ":key2 " << "'" << src.key2 << "'";
  output << ":key3 " << '"' << src.key3 << '"' << ":)";
  return output;
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

bool doroshenko::compareStructs(const DataStruct& firstStruct, const DataStruct& secondStruct)
{
  if (firstStruct.key1 == secondStruct.key1)
  {
    if (firstStruct.key2 == secondStruct.key2)
    {
      return (firstStruct.key3.length() < secondStruct.key3.length());
    }
    else
    {
      return (firstStruct.key2 < secondStruct.key2);
    }
  }
  else
  {
    return (firstStruct.key1 < secondStruct.key1);
  }
}
