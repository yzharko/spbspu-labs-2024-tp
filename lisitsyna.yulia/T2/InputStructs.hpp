#ifndef INPUTSTRUCTS_HPP
#define INPUTSTRUCTS_H

#include <string>
#include "Delimiter.h"

namespace lisitsyna
{
    struct Label
    {
      std::string exp;
    };

    struct LongLong
    {
      long long& ref;
    };

    struct Char
    {
      char& ref;
    };

    struct StringKey
    {
      std::string& ref;
    };

    std::istream& operator>>(std::istream& in, Label&& dest);
    std::istream& operator>>(std::istream& in, LongLong&& dest);
    std::istream& operator>>(std::istream& in, Char&& dest);
    std::istream& operator>>(std::istream& in, StringKey&& dest);
}
#endif
