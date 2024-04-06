#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>

struct DataStruct
{
    unsigned long long key1 = 0;
    unsigned long long key2 = 0;
    std::string key3 = "";

    friend std::istream& operator>>(std::istream& is, DataStruct& data);
    friend std::ostream& operator<<(std::ostream& os, const DataStruct& data);
};

#endif
