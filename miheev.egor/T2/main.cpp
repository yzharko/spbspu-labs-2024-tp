#include <iostream>
#include <vector>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  using input_it_t = std::istream_iterator< miheev::DataStruct >;
  // input_it_t iter{std::cin};
  // std::vector< miheev::DataStruct > structs(input_it_t{std::cin}, input_it_t{});
  input_it_t iter(std::cin);

  return 0;
}
