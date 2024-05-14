#include "InputProcessing.hpp"
#include <iterator>
#include <limits>
#include "Delimeter.hpp"

void reznikova::readFromFile(std::ifstream & input, std::vector< Polygon > & inputData)
{
  while (!input.eof())
  {
    std::copy(
      std::istream_iterator< Polygon >(input),
      std::istream_iterator< Polygon >(),
      std::back_inserter(inputData)
    );
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
