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

  // Cambio en la declaración de la lista, ahora se crea vacía

  while (true) // Cambio en la condición del bucle, no necesitamos verificar eof() antes de leer
  {
    DataStruct temp;
    std::cin >> temp;
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      break; // Salir del bucle si la entrada falla
    }
    data.push_back(temp); // Agregar al final de la lista en lugar de usar std::copy
  }

  data.sort();
  for (const auto &item : data) // Cambio en el bucle de salida
  {
    std::cout << item << '\n';
  }
}
