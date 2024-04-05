#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include "dataStruct.hpp"
#include "helpStructs.hpp"

int main()
{
  std::vector< sobolevsky::DataStruct > vec;
  std::string test = "biba";
  sobolevsky::DataStruct struc(0.0, 'a', test);
  std::cout << struc;
  return 0;
}
