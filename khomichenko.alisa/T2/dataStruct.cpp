#include "dataStruct.hpp"
#include "helpers.hpp"
#include "scopeGuard.hpp"

namespace khomichenko
{
std::istream & operator>>(std::istream & in, DataStruct & dataStr)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Guard guard(in);

  DataStruct data;
  std::string key;

  in >> DelimiterIO{'('};
  for (int i =  0; i < 3; i++)
  {
    in >> DelimiterIO{':'}>>key;
    if (key == "key1")
    {
      in>>DoubleIO{data.key1};
    }
    else if (key == "key2")
    {
      in>> CharIO{data.key2};
    }
    else if (key == "key3")
    {
      in>> StringIO{data.key3};
    }
    else
    {
      in.setstate(std::ios::failbit);
    }
  }
  in >> DelimiterIO{':'} >> DelimiterIO {')'};
  if (in)
  {
    dataStr = data;
  }
  return in;
}

std::ostream & operator<<(std::ostream & out, const DataStruct & dataStr)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  out << "(:key1 " << dataStr.key1 << ":" << "key2 '" << dataStr.key2;
  out << "':key3 " << "\"" << dataStr.key3 << "\":)";
  return out;
}

}
