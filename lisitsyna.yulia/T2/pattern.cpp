#include "pattern.hpp"
#include "delimiter.hpp"
#include "ScopeGuard.hpp"

std::istream & lisitsyna::operator>>(std::istream & in, SllLit && exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  return in >> exp.ref >> Separator{ 'l' } >> Separator{ 'l' };
}
std::istream& lisitsyna::operator>>(std::istream& in, ChrLit&& exp)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  in >> Separator{'\''} >> exp.ref >> Separator{'\''};
  return in;
}
std::istream& kozlov::operator>>(std::istream& in, StringVal&& key)
{
  std::istream::sentry guard(in);
  if (!guard)
  {
    return in;
  }
  std::getline(in >> Separator{'"'}, exp.ref, '"');
  return in;
}
