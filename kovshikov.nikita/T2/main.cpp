#include <iostream>
//#include <limits>
#include <vector>
#include <algorithm>
#include <iterator>
#include "data_struct.hpp"

using namespace kovshikov;
int main()
{
  using input_it = std::istream_iterator<DataStruct>;
  std::vector<DataStruct> data(input_it{std::cin}, input_it{});
  using output_it = std::ostream_iterator<DataStruct>;
  std::copy(data.cbegin(), data.cend(), output_it{std::cout, "\n"});
 /* std::vector<DataStruct> data;
  DataStruct newstruct('a', -4, 7, "nikita");
  while(!std::cin.eof())
  {
    if(!(std::cin >> newstruct))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
      data.push_back(newstruct);
    }
  }
  while(!data.empty())
  {
    std::cout << data.back() << "\n";
    data.pop_back();
  }*/
}
