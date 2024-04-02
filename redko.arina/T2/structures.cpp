#include "structures.hpp"
#include "iofmtguard.hpp"
#include <iomanip>

std::istream & redko::operator>>(std::istream & in, DelimiterIO && dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (tolower(c) != dest.expected))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

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

std::istream & redko::operator>>(std::istream & in, DataStruct & dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  DataStruct input;
  {
    using del = DelimiterIO;
    using ll = LongLongIO;
    using comp = ComplexIO;
    using str = StringIO;
    std::string key = "";
    in >> del{ '(' };
    for (size_t i = 0; i < 3; ++i)
    {
      in >> del{ ':' } >> key;
      if (key == "key1")
      {
        in >> ll{ input.key1 };
      }
      else if (key == "key2")
      {
        in >> comp{ input.key2 };
      }
      else if (key == "key3")
      {
        in >> str{ input.key3 };
      }
    }
    in >> del{ ':' } >> del{ ')' };
  }
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream & redko::operator<<(std::ostream & out, const DataStruct & dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(";
  out << ":key1 " << dest.key1 << "ll";
  out << ":key2 #c(" << std::fixed << std::setprecision(1) << dest.key2.real() << " " << dest.key2.imag() << ")";
  out << ":key3 \"" << dest.key3 << "\":)";
  return out;
}

redko::iofmtguard::iofmtguard(std::basic_ios< char > & s):
  s_(s),
  fill_(s.fill()),
  precision_(s.precision()),
  fmt_(s.flags())
{}

redko::iofmtguard::~iofmtguard()
{
  s_.fill(fill_);
  s_.precision(precision_);
  s_.flags(fmt_);
}

bool redko::operator<(const DataStruct & lhs, const DataStruct & rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return (lhs.key1 < rhs.key1);
  }
  else if (abs(lhs.key2) != abs(rhs.key2))
  {
    return (abs(lhs.key2) < abs(rhs.key2));
  }
  return (lhs.key3.size() < rhs.key3.size());
}
