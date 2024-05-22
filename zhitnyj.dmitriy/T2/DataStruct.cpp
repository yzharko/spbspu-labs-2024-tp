#include <iomanip>
#include "DataStruct.hpp"
#include "iofmtguard.hpp"
#include "DelimiterIO.hpp"
#include "UllLitIO.hpp"
#include "UllHexIO.hpp"
#include "StringIO.hpp"
#include "DelStrIO.hpp"

bool DataStruct::operator<(const DataStruct& other) const
{
  if (key1 != other.key1)
  {
    return key1 < other.key1;
  }
  if (key2 != other.key2)
  {
    return key2 < other.key2;
  }
  return key3.length() < other.key3.length();
}

std::istream& operator>>(std::istream& in, UllLitIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> dest.ref >> DelimiterIO{ 'u' } >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
  return in;
}

std::istream& operator>>(std::istream& in, UllHexIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> std::hex >> dest.ref >> std::dec;
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, DelStrIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  for (char c : dest.exp)
  {
    in >> DelimiterIO{ c };
  }
  return in;
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  in >> DelStrIO{ "(:" };
  int keyNumber = 0;
  for (size_t i = 0; i < 3; ++i)
  {
    in >> DelStrIO{ "key" } >> keyNumber;
    if (keyNumber == 1)
    {
      in >> UllLitIO{ input.key1 };
    }
    else if (keyNumber == 2)
    {
      in >> UllHexIO{ input.key2 };
    }
    else if (keyNumber == 3)
    {
      in >> StringIO{ input.key3 };
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
    in >> DelimiterIO{ ':' };
  }
  in >> DelimiterIO{ ')' };
  if (in)
  {
    dest = input;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& src)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }

  iofmtguard fmtguard(out);
  out << "(:key1 " << src.key1 << "ull";
  out << ":key2 0x" << std::uppercase << std::hex << src.key2 << std::dec;
  out << ":key3 \"" << src.key3 << "\":)";
  return out;
}
