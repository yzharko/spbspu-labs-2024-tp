#include "dataStruct.hpp"

sobolevsky::DataStruct::DataStruct()
{
  key1 = 0;
  key2 = 0;
  key3 = "";
}

sobolevsky::DataStruct::DataStruct(double a_, char b_, std::string c_)
{
  key1 = a_;
  key2 = b_;
  key3 = c_;
}

double sobolevsky::DataStruct::get1() const
{
  return key1;
}

char sobolevsky::DataStruct::get2() const
{
  return key2;
}

std::string sobolevsky::DataStruct::get3() const
{
  return key3;
}

std::istream & sobolevsky::operator>>(std::istream & in, sobolevsky::DataStruct & value)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  double a = 0;
  char b = 0;
  char helpChar = 0;
  std::string c = 0;
  using del = sobolevsky::Delimitr;
  in >> del{'('};
  std::string keyX;
  for (int i = 0; i < 3; i++)
  {
    in >> del{':'} >> keyX;
    if (keyX == "key1")
    {
      in >> a;
      in >> helpChar;
      if (helpChar != 'd' || helpChar != 'D')
      {
        in.setstate(std::ios::failbit);
      }
    }
    else if (keyX == "key2")
    {
      in >> del{'\''} >> b >> del{'\''};
    }
    else
    {
      in >> del{'\"'} >> c >> del{'\"'};
    }
  }
  in >> del{':'} >> del{')'};
  if (in)
  {
    value = sobolevsky::DataStruct(a, b, c);
  }
  return in;
}

std::ostream & sobolevsky::operator<<(std::ostream & out, const sobolevsky::DataStruct & value)
{
  std::ostream::sentry guard(out);
  if (!guard)
  {
    return out;
  }
  out << "(:key1 "  << value.get1() << ":key2 '" << value.get2() << "'" << ":key3 \"" << value.get3() << "\":";
  return out;
}
