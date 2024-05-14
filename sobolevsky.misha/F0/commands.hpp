#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

namespace sobolevsky
{
  void getCommands(std::istream & in, std::ostream & out);
  void getLoadAndCreate(std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > > myVec,
  std::istream & in, std::ostream & out);
  void getDelete(std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > > myVec, std::istream & in,
  std::ostream & out);
  void getAllDicts(std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > > myVec,
  std::istream & in, std::ostream & out);
  void getSelect(std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > > myVec, std::istream & in,
  std::ostream & out);
  void holyTrinity(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::istream & in, std::ostream & out);
  void printDict(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::istream & in, std::ostream & out);
  void uniqeWords(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::istream & in, std::ostream & out);
  void wordCount(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::istream & in, std::ostream & out);
  void getRename(std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > > myVec, std::istream & in,
  std::ostream & out);
  void save(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::istream & in);

  void error(std::ostream & out, const std::string &text);
  bool isNameHere(std::pair< std::string, std::multimap< size_t, std::string > > &pair, const std::string &name);
  void dictOutput(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::ostream & out, size_t n, bool mode);
}

#endif
