#include <algorithm>
#include <iostream>
#include <fstream>

#include "polygon.cpp"
#include "point.cpp"
#include "../common/delimiterIO.hpp"
#include "../common/inOutPut.cpp"

int main(int argc, char **argv)
{
  using namespace anikanov;

  if (argc < 2 || argc > 2) {
    return 1;
  }
  std::ifstream input(argv[1]);
  if (!input) {
    return 1;
  }

  std::vector< Polygon > polygons;
  Polygon pol;
  while (std::getline(input, expression)) {
    if (expression.empty()) {
      expression.clear();
      continue;
    }

    try {
      postfix = toPostfix(expression);
      answers.push(calculate(postfix));
    } catch (const std::logic_error &err) {
      std::cerr << err.what() << "\n";
      return 1;
    } catch (const std::runtime_error &err) {
      std::cerr << err.what() << "\n";
      return 2;
    }

    expression.clear();
  }
  while (!input.eof()) {
    std::cout << "+\n";
    input >> pol;
    if (!input.fail()) {
      polygons.push_back(pol);
    } else {
      input.clear();
    }
  }

  return 0;
}