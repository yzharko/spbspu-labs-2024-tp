#ifndef INPUT_FUNCTIONS_HPP
#define INPUT_FUNCTIONS_HPP

#include "workspace.hpp"
#include <vector>

namespace miheev
{
  void getGraphsNames(const Workspace&, std::vector< std::string >&);
  void initWorkspace(int argc, char* argv[], miheev::Workspace& workspace);
  void readGraph(const std::string& filename, Graph& container);
}

#endif
