#ifndef ULLLITIO_HPP
#define ULLLITIO_HPP

#include <iosfwd>

struct UllLitIO
{
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, UllLitIO&& dest);

#endif
