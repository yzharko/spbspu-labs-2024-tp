#ifndef DELSTRIO_HPP
#define DELSTRIO_HPP

#include <string>

struct DelStrIO
{
    std::string exp;
};

std::istream& operator>>(std::istream& in, DelStrIO&& dest);

#endif
