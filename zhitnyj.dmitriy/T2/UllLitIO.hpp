#ifndef ULLLITIO_HPP
#define ULLLITIO_HPP

struct UllLitIO
{
    unsigned long long& ref;
};

std::istream& operator>>(std::istream& in, UllLitIO&& dest);

#endif
