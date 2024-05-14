#ifndef ULLHEXIO_HPP
#define ULLHEXIO_HPP

#include <iosfwd>

struct UllHexIO
{
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, UllHexIO&& dest);

#endif
