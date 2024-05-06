#include <fstream>
#include <iostream>
#include <map>
#include <functional>
#include <limits>

int main(int argc, char * argv[])
{
  if (argc != 2)
  {
    std::cerr << "Error: wrong number of parameters\n";
    return 2;
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    std::cerr << "Error: unable to open the file\n";
    return 2;
  }
  return 0;
}
