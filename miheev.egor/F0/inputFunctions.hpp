#ifndef INPUT_FUNCTIONS_HPP
#define INPUT_FUNCTIONS_HPP

#include "workspace.hpp"

namespace miheev
{
  void miheev::initWorkspace(int argc, char* argv[], miheev::Workspace& workspace);
  void readGraph(const std::string& filename, Graph& container);
}

#endif
