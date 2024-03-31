#include <iostream>
#include <vector>
#include <iterator>
#include "dataStruct.hpp"

int main()
{
  // using input_it_t = std::istream_iterator< miheev::DataStruct >;
  // std::vector< miheev::DataStruct > structs(input_it_t{std::cin}, input_it_t{});
  miheev::DataStruct example;
  std::cin >> example;
  miheev::printDS(example);
  return 0;
}
