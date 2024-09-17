#include "interface.hpp"
#include <limits>

void maksimov::printError(std::ostream& output)
{
  output << "<INVALID COMMAND>\n";
}

void maksimov::printEmptyError(std::ostream& output)
{
  output << "<EMPTY>\n";
}

void maksimov::fixStream(std::istream& input)
{
  input.clear();
  input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void maksimov::handleError(std::istream& input, std::ostream& output)
{
  printError(output);
  fixStream(input);
}
