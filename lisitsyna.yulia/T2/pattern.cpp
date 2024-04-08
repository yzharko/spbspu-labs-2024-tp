#include "pattern.hpp"
#include "delimiter.hpp"
#include "ScopeGuard.hpp"
#include <iostream>

std::istream& lisitsyna::operator>>(std::istream& in, SllLit&& dest)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    return in >> dest.ref >> Separator{ 'l' } >> Separator{ 'l' };
}
std::istream& lisitsyna::operator>>(std::istream& in, ChrLit&& dest)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    in >> Separator{ '\'' } >> dest.ref >> Separator{ '\'' };
    return in;
}
std::istream& lisitsyna::operator>>(std::istream& in, StringKey&& dest)
{
    std::istream::sentry guard(in);
    if (!guard)
    {
        return in;
    }
    std::getline(in >> Separator{ '"' }, dest.ref, '"');
    return in;
}
