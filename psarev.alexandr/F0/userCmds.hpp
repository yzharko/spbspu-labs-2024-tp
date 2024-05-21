#ifndef USER_CMDS_HPP
#define USER_CMDS_HPP
#include "internalFuncs.hpp"
#include <iostream>
#include <fstream>

namespace psarev
{
  void cmdHelp(std::istream& in, std::ostream& out);
  void cmdCreate(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot);
  void cmdDelete(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot);
  void cmdList(std::istream& in, std::ostream& out);
  void cmdShow(std::istream& in, std::ostream& out);
  void cmdRename(std::istream& in, std::ostream& out);
  void cmdChoose(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot);
  void cmdSave(std::istream& in, std::ostream& out);

  void cmdPrint(storage_t& storage, std::istream& in, std::ostream& out);
  void cmdFono(storage_t& storage, std::istream& in, std::ostream& out);
  void cmdMakeSent(storage_t& storage, std::istream& in, std::ostream& out);
}

#endif