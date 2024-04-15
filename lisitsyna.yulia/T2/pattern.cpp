#include "DataStruct.hpp"
#include "pattern.hpp"
#include "Structure.hpp"

#include <iostream>

std::istream& lisitsyna::operator>>(std::istream& in, SllLit&& dest)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    return in >> dest.ref >> Delimiter{ 'l' } >> Delimiter{ 'l' };
}
std::istream& lisitsyna::operator>>(std::istream& in, ChrLit&& dest)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    in >> Delimiter{ '\'' } >> dest.ref >> Delimiter{ '\'' };
}
std::istream& lisitsyna::operator>>(std::istream& in, StringKey&& dest)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
      return in;
    }
    std::getline(in >> Delimiter{ '"' }, dest.ref, '"');
}
