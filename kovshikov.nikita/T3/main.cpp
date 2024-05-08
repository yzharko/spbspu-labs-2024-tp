#include <algorithm>
#include <functional>
#include <fstream>
#include <cstring>
#include <iostream>
#include "polygons.hpp"

// НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ ЦИКЛЫ
// std::bind - фукнция которая создает функциональные
// объекты из других функциональных объектов
// namespace std::placeholders - номера параметров в функциональном объекте

int main(int argc, char ** argv)
{
  if(argc != 2)
  {
    std::cerr << "NO FILE SPECIFIED" << "\n";
    return 1;
  }

  using namespace kovshikov;
  std::string cmd;
  std::vector< Polygon > allData;

  std::fstream input(argv[1]);
  readFile(input, allData);

  //1)readFile - чтение файла

  //контекст для каждой команды
  while(std::cin >> cmd)
  {
    if(cmd == "CMD1")
    {
      //доп. параметры для данной команды
      //выполнение команды
    }
  }
}
