#include <iostream>
#include <vector>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  using input_it_t = std::istream_iterator< miheev::DataStruct >;
  input_it_t iter{std::cin};

  return 0;
}
