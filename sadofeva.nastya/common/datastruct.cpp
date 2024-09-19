#include <iomanip>
#include "datastruct.hpp"
#include "delimiter.hpp"
#include "guard.hpp"

std::istream & sadofeva::operator>>(std::istream & is, sadofeva::DelimiterIO && dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = 0;
  is >> c;
  if (is && (c != dest.exp))
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream & sadofeva::operator>>(std::istream & is, sadofeva::DoubleIO && dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  return is >> dest.ref;
}

std::istream & sadofeva::operator>>(std::istream & is, sadofeva::UnsignedLongLongIO && dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  is >> sadofeva::DelimiterIO{'0'} >> sadofeva::DelimiterIO{'x'} >> std::hex >> dest.ref;
  return is;
}

std::istream & sadofeva::operator>>(std::istream & is, sadofeva::StringIO && dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  return std::getline(is >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream & sadofeva::operator>>(std::istream & is, sadofeva::DataStruct & dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  DataStruct struct_;
  {
    using del = DelimiterIO;
    using dobl = DoubleIO;
    using lng = UnsignedLongLongIO;
    using str = StringIO;
    std::string key;
    is >> del{ '(' };
    for (size_t i = 0; i < 3;i++)
    {
      is >> del{ ':' } >> key;
      if (key == "key1")
      {
        is >> dobl{struct_.key1};
      }
      else if ( key == "key2")
      {
        is >> lng{struct_.key2};
      }
      else if ( key == "key3")
      {
        is >> str{struct_.key3};
      }
    }
    is >> del{ ':' } >> del{ ')' };
  }
  if (is)
  {
    dest = struct_;
  }
  return is;
}

bool sadofeva::operator<(const DataStruct & one, const sadofeva::DataStruct & two)
{
  if (one.key1 < two.key1)
  {
    return true;
  }
  if (one.key1 ==  two.key1)
  {
    if ( one.key2 < two.key2)
    {
      return true;
    }
    else if ( one.key2 == two.key2)
    {
      if (one.key3.size() < two.key3.size())
      {
        return true;
      }
    }
  }
  return false;
}

std::ostream & sadofeva::operator<<(std::ostream & out, const sadofeva::DataStruct & src)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:key1 ";
  int e = 0;
  double numberDouble = src.key1;
  if (numberDouble < 1 && numberDouble != 0)
  {
    for (; numberDouble < 1; e--)
    {
      numberDouble *= 10;
    }
  }
  else
  {
    for (; numberDouble > 9; e++)
    {
      numberDouble /= 10;
    }
  }
  out << std::fixed << std::setprecision(1);
  out << numberDouble << 'e' << std::showpos << e;
  out << ":key2 0x" << std::hex << std::uppercase << src.key2;
  out << ":key3" << " \"" << src.key3 << "\":)";
  return out;
}
