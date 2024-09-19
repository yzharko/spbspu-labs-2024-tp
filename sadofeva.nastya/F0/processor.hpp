#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP
#include <functional>
#include "helpcommand.hpp"

namespace sadofeva
{
  class CommandProcessor
  {
  public:
    CommandProcessor();
    void processCommand(dictionaryOfNames& dictionaries, const std::string cmd, std::istream& in, std::ostream& out);

  private:
    using FunctionType = std::function< void(dictionaryOfNames&, std::istream&, std::ostream&) >;
    using mapOfFunctions = std::map< std::string, FunctionType >;
    mapOfFunctions commandsList;
  };
}
#endif
