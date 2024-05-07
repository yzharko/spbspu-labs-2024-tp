#ifndef ULLHEXIO_HPP
#define ULLHEXIO_HPP

struct UllHexIO
{
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, UllHexIO&& dest);

#endif
