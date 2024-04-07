#include "dataStruct.hpp"
#include "iofmtguard.hpp"
#include "delimiter.hpp"

std::istream &gorbunova::operator>>(std::istream &in, DataStruct &data)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  DataStruct input;
  {
    std::string key = "";
    in >> delimiter{'('};
    for (size_t i = 0; i < 3; i++)
    {
      in >> delimiter{':'} >> key;
      if (key == "key1")
      {
        in >> complexx{input.key1};
      }
      else if (key == "key2")
      {
        in >> ratio{input.key2};
      }
      else if (key == "key3")
      {
        in >> str{input.key3};
      }
    }
    in >> delimiter{':'} >> delimiter{')'};
  }
  if (in)
  {
    data = input;
  }
  return in;
}
std::ostream &gorbunova::operator<<(std::ostream &out, const DataStruct &data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(" << ":key1 #c(" << data.key1.real() << " " << data.key1.imag() << ")";
  out << ":key2 " << "(:N " << data.key2.first << ":D " << data.key2.second << ":)";
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}
bool gorbunova::operator<(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return std::real(lhs.key1) < std::real(rhs.key1) ||
           (std::real(lhs.key1) == std::real(rhs.key1) && std::imag(lhs.key1) < std::imag(rhs.key1));
  }
  else if (lhs.key2 != rhs.key2)
  {
    return lhs.key2.first < rhs.key2.first ||
           (lhs.key2.first == rhs.key2.first && lhs.key2.second < rhs.key2.second);
  }
  else
  {
    return lhs.key3.length() < rhs.key3.length();
  }
}
std::istream &gorbunova::operator>>(std::istream &in, complexx &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double re = 0;
  double im = 0;
  in >> delimiter{'#'} >> delimiter{'c'} >> delimiter{'('} >> re >> im >> delimiter{')'};
  if (in)
  {
    dest.ref.real(re);
    dest.ref.imag(im);
  }
  return in;
}
std::istream &gorbunova::operator>>(std::istream &is, ratio &&value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  char tmp;
  is >> delimiter{'('} >> delimiter{':'};
  is >> tmp;
  if (tmp == 'N')
  {
    is >> value.ref.first;
  }
  else
  {
    is.setstate(std::ios::failbit);
    return is;
  }
  is >> delimiter{':'};
  is >> tmp;
  if (tmp == 'D')
  {
    is >> value.ref.second;
    return is;
  }
}
std::istream &gorbunova::operator>>(std::istream &in, str &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::getline(in >> delimiter{'"'}, dest.ref, '"');
  return in;
}
