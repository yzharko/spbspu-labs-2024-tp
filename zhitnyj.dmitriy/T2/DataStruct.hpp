#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iosfwd>
#include <string>
#include "iofmtguard.hpp"
#include "DelimiterIO.hpp"
#include "UllLitIO.hpp"
#include "UllHexIO.hpp"
#include "StringIO.hpp"
#include "DelStrIO.hpp"

struct DataStruct
{
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;

    bool operator<(const DataStruct& other) const;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, UllLitIO&& dest);
std::istream& operator>>(std::istream& in, UllHexIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, DelStrIO&& dest);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& src);

#endif
