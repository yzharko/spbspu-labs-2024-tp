#include "datastruct.hpp"


std::istream & sadofeva::operator>>(std::istream & is, DelimiterIO && dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = "0";
  is >> c;
  if (is && (c != dest.exp))
  {
    is.setctate(std::ios::failbit);
  }
  return is;
}

std::istream & sadofeva::operator >> (std::istream & is, DoubleIO && dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  return is >> dest.ref;
}

std::istream & sadofeva::operator >> (std::istream & is, UnsignedLongLongIO && dest)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  is >> sadofeva::DelimiterIO{"0"} >> sadofeva::Delimiter{"x"} >> std::hex >> dest.ref;
  return is;
}

std::istream & sadofeva::operator>> (std::istream & is, StringIo && dest_
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  return std::getline(is >> DelimiterIO{'"'}, dest.ref,'"');
}

std::istream & sadofeva::operator >> (std::istream & is, DataStruct & dest)
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
    is >> del{'('};
    for (size_t i = 0; i < 3;i++)
    {
      is >> del{':'} >> key;
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
    is >> del{':'} >> del{')'};
  }
  if (is)
  {
    dest = struct_;
  }
  return is;
}

bool sadofeva::operator < (const DataStruct & one, const DataStruct & two)
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
}

std::ostream & sadofeva::operator << (std::ostream & out, const DataStruct & src)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "key1" << std::scientidic << std::setprecision(1) << src.key1;
  out << ":key0x" << " " << std::hex << src.key2 << " ";
  out << ":key3" << " " << src.key3 << " ";
  return out:
}
