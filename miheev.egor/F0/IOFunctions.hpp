#ifndef IO_FUNCTIONS_HPP
#define IO_FUNCTIONS_HPP

#include "workspace.hpp"
#include <vector>

namespace miheev
{
  void getGraphsNames(const Workspace&, std::vector< std::string >&);
  void initWorkspace(int argc, char* argv[], miheev::Workspace& workspace);
  void readGraph(const std::string& filename, Graph& container);
  std::ostream& sendMessage(std::ostream&, const std::string&);
}

#endif
