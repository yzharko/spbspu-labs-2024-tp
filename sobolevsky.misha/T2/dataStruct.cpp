#include "dataStruct.hpp"

sobolevsky::DataStruct::DataStruct()
{
  key1 = 0;
  key2 = 0;
  key3 = "";
  Dd = 0;
}

sobolevsky::DataStruct::DataStruct(double a_, char b_, std::string c_, char Dd_)
{
  key1 = a_;
  key2 = b_;
  key3 = c_;
  Dd = Dd_;
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

char sobolevsky::DataStruct::getD() const
{
  return Dd;
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
  std::string c = "";
  using del = sobolevsky::Delimitr;
  in >> del{'('};
  std::string keyX;
  for (int i = 0; i < 3; i++)
  {
    in >> del{':'} >> keyX;
    if (keyX == "key1")
    {
      in >> a >> helpChar;
      if (!(helpChar == 'd' || helpChar == 'D'))
      {
        in.setstate(std::ios::failbit);
      }
    }
    else if (keyX == "key2")
    {
      in >> del{'\''} >> b >> del{'\''};
    }
    else if (keyX == "key3")
    {
      in >> del{'"'};
      getline(in, c, '"');
    }
  }
  in >> del{':'} >> del{')'};
  if (in)
  {
    value = sobolevsky::DataStruct(a, b, c, helpChar);
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
  out << "(:key1 " << std::fixed << std::setprecision(1) << value.get1() << value.getD();
  out << ":key2 '" << value.get2() << "'" << ":key3 \"" << value.get3() << "\":)\n";
  return out;
}
