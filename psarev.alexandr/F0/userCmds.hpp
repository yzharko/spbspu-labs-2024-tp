#ifndef USER_CMDS_HPP
#define USER_CMDS_HPP
#include "internalFuncs.hpp"
#include <iostream>
#include <fstream>

namespace psarev
{
  void cmdHelp(std::istream& in, std::ostream& out);
  void cmdCreate(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot, std::string dest);
  void cmdDelete(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot);
  void cmdList(std::ostream& out, std::map< std::string, storage_t >& depot);
  void cmdShow(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot);
  void cmdRename(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot);
  void cmdChoose(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot, std::string& storage);
  void cmdSave(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot);

  void cmdPrint(std::istream& in, std::ostream& out, std::map< std::string, storage_t >& depot, std::string& storage);
  void cmdFono(std::istream& in, std::string& storage);
  void cmdMakeSent(std::istream& in, std::string& storage);
}

#endif
