#include <iomanip>
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
    in >> Delimiter{'('};
    for (size_t i = 0; i < 3; ++i)
    {
      in >> Delimiter{':'} >> key;
      if (key == "key1")
      {
        in >> Complexx{input.key1};
      }
      else if (key == "key2")
      {
        in >> Ratio{input.key2};
      }
      else if (key == "key3")
      {
        in >> Str{input.key3};
      }
    }
    in >> Delimiter{':'} >> Delimiter{')'};
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
  out << "(" << ":key1 #c(" << std::fixed << std::setprecision(1) << data.key1.real() << " " << data.key1.imag() << ")";
  out << ":key2 " << "(:N " << data.key2.first << ":D " << data.key2.second << ":)";
  out << ":key3 \"" << data.key3 << "\":)";
  return out;
}
bool gorbunova::operator<(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return abs(lhs.key1) < abs(rhs.key1);
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
std::istream &gorbunova::operator>>(std::istream &in, Complexx &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double re = 0;
  double im = 0;
  in >> Delimiter{'#'} >> Delimiter{'c'} >> Delimiter{'('} >> re >> im >> Delimiter{')'};
  if (in)
  {
    dest.ref.real(re);
    dest.ref.imag(im);
  }
  return in;
}
std::istream &gorbunova::operator>>(std::istream &is, Ratio &&value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  char tmp = '\0';
  is >> Delimiter{'('} >> Delimiter{':'};
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
  is >> Delimiter{':'};
  is >> tmp;
  if (tmp == 'D')
  {
    is >> value.ref.second;
  }
  else
  {
    is.setstate(std::ios::failbit);
    return is;
  }
  is >> Delimiter{':'} >> Delimiter{')'};
  return is;
}
std::istream &gorbunova::operator>>(std::istream &in, Str &&dest)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::getline(in >> Delimiter{'"'}, dest.ref, '"');
  return in;
}
