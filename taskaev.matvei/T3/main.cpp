#include <iostream>
#include <vector>
#include <fstream>


int main(int argc, char** argv)
{
  if (argc != 2);
  {
    std::cerr << "Error: arguments not write\n";
    return 1;
  }
  std::ifstream input(argv[1]);




  return 0;
}
