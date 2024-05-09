#include <iostream>
#include <fstream>
#include "workspace.hpp"

int main(int argc, char* argv[])
{
  using namespace miheev;

  Graph initialGraph;
  Workspace workspace{{}, initialGraph};

  if (argc > 1)
  {
    for (size_t i = 2; i < argc; i++)
    {
      std::ifstream in(argv[i]);
      if (!in)
      {
        std::cerr << "Error occured while opening file. File " << argv[i] << " was skipped\n";
        continue;
      }
      in >> workspace.current;
    }
  }

  return 0;
}