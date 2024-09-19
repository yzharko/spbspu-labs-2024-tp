#include "DataStruct.h"
#include <cmath>
#include <iomanip>
#include <string>

namespace batunov
{
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    char c = '0';
    in >> c;
    if (in && (std::tolower(c) != std::tolower(dest.exp)))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, DblLitIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    in >> dest.ref >> DelimiterIO{ 'd' };
    if (!in)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, DblSciIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    std::string temp = "";
    std::getline(in, temp, ':');
    std::istringstream iss(temp);
    bool findE = (temp.find('E') != std::string::npos  || temp.find('e') != std::string::npos );
    if (findE && iss >> dest.ref && iss.eof()) {
    }
    else {
      in.setstate(std::ios::failbit);
    }

    return in;
  }
  std::istream &operator>>(std::istream &in, StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
     std::getline(in >> DelimiterIO{ '"'}, dest.ref, '"');
    return in;
  }
  std::istream &operator>>(std::istream &in, DelStrIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    size_t i = 0;
    while (dest.exp[i] != '\0')
    {
      in >> DelimiterIO({dest.exp[i++]});
    }
    return in;
  }

  std::istream &operator>>(std::istream &in, DataStruct &dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    DataStruct input;
    {
      using sep = DelimiterIO;
      using sepStr = DelStrIO;
      using dblLit = DblLitIO;
      using dblSci = DblSciIO;
      using str = StringIO;
      in >> sepStr({"(:"});
      int keyNumber = 0;
      for (size_t i = 0; i < 3 ; i++) {
        in >> sepStr({"key"}) >> keyNumber;
        if (keyNumber == 1)
        {
          in >> dblLit{ input.key1 };
          in >> sep{ ':'};
        }
        else if (keyNumber == 2)
        {
          in >> std::scientific >> dblSci {input.key2};
        }
        else if (keyNumber == 3)
        {
          in >> str{input.key3};
          in >> sep{ ':'};
        }
        else
        {
          in.setstate(std::ios::failbit);
        }
      }
      in >> sep{ ')'};
    }
    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::string expForm(double number) {
    std::stringstream ss;
    ss << std::setprecision(1) << std::scientific << number;
    std::string str = "";
    ss >> str;
    bool extraZeros = true;
    std::string temp = "";
    for (size_t i = str.find('e') + 2; i < str.length() && extraZeros; i++) {
      if (str[i] != '0') {
        temp = str.substr(i);
        extraZeros = false;
      }
    }

    return str.substr(0, str.find('e')+2) + temp;
  }

  std::ostream &operator<<(std::ostream &out, const DataStruct &src)
  {
    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }
    iofmtguard fmtguard(out);
    out << "(:key1 "  << std::fixed << std::setprecision(1) << src.key1 << "d";
    out << ":key2 "  << expForm(src.key2) ;
    out << ":key3 \"" << src.key3 << "\":)";
    return out;
  }

  iofmtguard::iofmtguard(std::basic_ios< char > &s) :
      s_(s),
      fill_(s.fill()),
      precision_(s.precision()),
      fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
