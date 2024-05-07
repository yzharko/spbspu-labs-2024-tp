#ifndef DELIMITERIO_HPP
#define DELIMITERIO_HPP

struct DelimiterIO
{
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);

#endif
