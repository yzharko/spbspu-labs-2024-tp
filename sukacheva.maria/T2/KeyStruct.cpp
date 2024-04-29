#include "KeyStruct.hpp"
#include "Delimeter.hpp"
#include "StreamGuard.hpp"


std::istream& sukacheva::operator>>(std::istream& is, SllLit&& value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  return is >> value.val >> Delimeter{ 'l' } >> Delimeter{ 'l' };
}

std::istream& sukacheva::operator>>(std::istream& is, String&& value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  return std::getline(is >> Delimeter{ '"' }, value.val, '"');
}

std::istream& sukacheva::operator>>(std::istream& is, DblLit&& value)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  return is >> value.val >> Delimeter{ 'd' };
}
