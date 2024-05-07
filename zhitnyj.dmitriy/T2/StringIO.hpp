#ifndef STRINGIO_HPP
#define STRINGIO_HPP

#include <iosfwd>
#include <string>

struct StringIO
{
    std::string& ref;
};

std::istream& operator>>(std::istream& in, StringIO&& dest);

#endif
