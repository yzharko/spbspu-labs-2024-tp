/*
#include <algorithm>
#include <functional>
#include <fstream>
#include <cstring>
#include <iostream>
#include <iterator>
#include "polygons.hpp"
*/
#include <limits>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "point.hpp"
#include "polygons.hpp"

// НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ ЦИКЛЫ
// std::bind - фукнция которая создает функциональные
// объекты из других функциональных объектов
// namespace std::placeholders - номера параметров в функциональном объекте

int main()    //int argc, char ** argv)
{
  using namespace kovshikov;
  std::vector< Polygon > allData;
  using input_it = std::istream_iterator< Polygon >;
  while(!std::cin.eof())
  {
    std::copy(input_it{std::cin}, input_it{}, std::back_inserter(allData));
    if(std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  using output_it = std::ostream_iterator< Polygon >;
  std::copy(allData.cbegin(), allData.cend(), output_it{std::cout, "\n"});



  return 0;
}





 /* if(argc != 2)
  {
    std::cerr << "NO FILE SPECIFIED" << "\n";
    return 1;
  }

  using namespace kovshikov;
  std::string cmd;
  std::vector< Polygon > allData;

  std::fstream input(argv[1]);

  using input_it = std::istream_iterator< Polygon >;  //блок ввода, нужно перегрузить оператор >> для struct Polygon
  while(!input.eof())
  {
    std::copy(input_it{input}, input_it{}, std::back_inserter(allData));
    if(input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  //контекст для каждой команды
  while(std::cin >> cmd)
  {
    if(cmd == "CMD1")
    {
      //доп. параметры для данной команды
      //выполнение команды
    }
  }*/
//}
