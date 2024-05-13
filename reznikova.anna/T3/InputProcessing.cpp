#include "InputProcessing.hpp"
#include <exception>
#include "Delimeter.hpp"

void reznikova::readFromFile(std::ifstream & input, std::vector< Polygon > & inputData)
{
  if (!input)
  {
    throw std::ios_base::failure("can't read from file file\n");
  }
  else
  {
    while (!input.eof())
    {
      input.clear();
      std::copy(std::istream_iterator< Polygon >(input),
        std::istream_iterator< Polygon >(),
        std::back_inserter(inputData)
      );
      input.close();
    }
  }
}
