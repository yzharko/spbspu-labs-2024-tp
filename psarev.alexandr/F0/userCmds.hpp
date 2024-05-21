#ifndef USER_CMDS_HPP
#define USER_CMDS_HPP
#include "internalFuncs.hpp"
#include <iostream>
#include <fstream>

namespace psarev
{
  void cmdHelp(std::istream& in, std::ostream& out);
  void cmdCreate(std::map< std::string, storage_t >& depot, std::istream& in, std::ostream& out);
  void cmdDelete(std::istream& in, std::ostream& out);
  void cmdList(std::istream& in, std::ostream& out);
  void cmdShow(std::istream& in, std::ostream& out);
  void cmdRename(std::istream& in, std::ostream& out);
  void cmdChoose(std::map< std::string, storage_t >& depot, std::istream& in, std::ostream& out);
  void cmdSave(std::istream& in, std::ostream& out);

  void cmdPrint(storage_t& storage, std::istream& in, std::ostream& out);
  void cmdFono(storage_t& storage, std::istream& in, std::ostream& out);
  void cmdMakeSent(storage_t& storage, std::istream& in, std::ostream& out);
}

#endif