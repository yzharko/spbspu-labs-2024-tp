#include <iostream>
#include <list>
#include <iterator>
#include <limits>
#include "dataStruct.hpp"

int main()
{
  using namespace tellez;
  using input_it_t = std::istream_iterator<DataStruct>;
  std::list<DataStruct> data;
  while (true)
  {
    DataStruct temp;
    std::cin >> temp;
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break;
    }
    data.push_back(temp);
  }

  data.sort();
  for (const auto &item : data)
  {
    std::cout << item << '\n';
  }
}
