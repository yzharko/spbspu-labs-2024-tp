#ifndef INPUTPROCESSING_HPP
#define INPUTPROCESSING_HPP
#include <fstream>
#include <vector>
#include "FigureStructs.hpp"

namespace reznikova
{
  void readFromFile(std::ifstream & input, std::vector< Polygon > & inputData);
}

#endif
