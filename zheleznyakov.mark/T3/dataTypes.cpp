#include "dataTypes.hpp"

std::istream & zheleznyakov::operator>>(std::istream & in, IntIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref;
};

std::istream & zheleznyakov::operator>>(std::istream & in, SizeTIO &&dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref;
};
