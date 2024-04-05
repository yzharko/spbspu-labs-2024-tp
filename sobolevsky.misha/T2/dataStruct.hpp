#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <string>
#include <iostream>
#include <cctype>
#include <iomanip>
#include "helpStructs.hpp"


namespace sobolevsky
{
  struct DataStruct
  {
    public:
      DataStruct();
      DataStruct(double a_, char b_, std::string c_, char Dd);
      double get1() const;
      char get2() const;
      std::string get3() const;
      char getD() const;

    private:
      double key1;
      char key2;
      std::string key3;
      char Dd;
  };

std::istream & operator>>(std::istream & in, sobolevsky::DataStruct & value);
std::ostream & operator<<(std::ostream & out, const sobolevsky::DataStruct & value);
}

#endif
