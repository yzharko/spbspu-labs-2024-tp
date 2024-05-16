#include "DataStruct.hpp"
#include <iomanip>

using delimimitr= kaseev::Delimiter;
std::istream& kaseev::operator>>(std::istream& in, DataStruct& data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct keeper;
  {
    in >> delimimitr{'('};
    std::string KeyNum;
    for (size_t i = 0; i < 3 && in; ++i)
    {
      in >> delimimitr{':'} >> KeyNum;
      if (KeyNum == "key1")
      {
        in >> DblLit{keeper.key1} >> delimimitr{'d'};
      }
      else if (KeyNum == "key2")
      {
        in >> UllOct{keeper.key2};
      }
      else if (KeyNum == "key3")
      {
        in >> String{keeper.key3};
      }
    }
    in >> delimimitr{':'} >> delimimitr{')'};
  }
  if (in)
  {
    data = keeper;
  }
  return in;
}

std::ostream& kaseev::operator<<(std::ostream& out, const DataStruct& data)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  iofmtguard fmtguard(out);
  out << "(:";
  out << "key1 " << std::fixed << std::setprecision(1) << data.key1 << "d";
  out << ":key2 " << std::oct << std::uppercase << data.key2;
  out << ":key3 " << std::quoted(data.key3) << ":)";
  return out;
}

bool kaseev::operator<(const DataStruct& first, const DataStruct& second)
{
  if (first.key1 != second.key1)
  {
    return first.key1 < second.key1;
  }
  else if (first.key2 != second.key2)
  {
    return first.key2 < second.key2;
  }
  else
  {
    return first.key3.size() < second.key3.size();
  }
}
std::istream & kaseev::operator>>(std::istream & in, DblLit && data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  return in >> data.ref;
}

std::istream & kaseev::operator>>(std::istream & in, UllOct && data)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> data.ref;
}

std::istream& kaseev::operator>>(std::istream& in, String&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> Delimiter{ '"' }, dest.ref, '"');
}
