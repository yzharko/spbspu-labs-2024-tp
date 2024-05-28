#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <map>
#include <ios>
#include <functional>
#include "dict.hpp"

namespace zheleznyakov
{
  namespace commands
  {
    std::ostream & help(std::istream & in, std::ostream & out);
    std::ostream & list(strings_t & strings, std::istream & in, std::ostream & out);
    std::ostream & rm(strings_t & strings, std::istream & in, std::ostream & out);
    std::ostream & cmp(strings_t & strings, std::istream & in, std::ostream & out);
    std::ostream & diff(strings_t & strings, std::istream & in, std::ostream & out);
    std::ostream & create(strings_t & strings, std::istream & in, std::ostream & out);
    std::ostream & enter(strings_t & strings, std::string & active, std::istream & in, std::ostream & out);

    std::ostream & read(strings_t & strings, std::string & active, std::istream & in, std::ostream & out);
    std::ostream & table(strings_t & strings, std::string & active, std::istream & in, std::ostream & out);
    std::ostream & info(strings_t & strings, std::string & active, std::istream & in, std::ostream & out);
    std::ostream & stats(strings_t & strings, std::string & active, std::istream & in, std::ostream & out);
    std::ostream & quit(std::string &, std::istream & in, std::ostream & out);
  }

  std::string statusString(std::string, std::string);
  std::string prompt(std::string);

  std::string extractKeyFromStringsPair(const std::pair< std::string, string_t > & pair);
  std::string extractKeyFromWordpair(const std::pair< std::string, wordpair_t > & pair);
  std::string coordsToPairs(const wordcoord_t & wordCoord);
  std::string wordEntryToString(const std::pair< std::string, wordpair_t >& pair);
  bool hasWord(const wordpairs_t & ref, const std::string word);
}
#endif
