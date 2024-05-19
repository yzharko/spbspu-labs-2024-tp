#ifndef MYCOMMANDS_HPP
#define MYCOMMANDS_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <vector>

using mypair = std::pair< std::string, std::multimap< size_t, std::string > >;

namespace sobolevsky
{
  void getCommands(std::istream & in, std::ostream & out);
  void getLoadAndCreate(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in);
  void getDelete(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in);
  void getAllDicts(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in, std::ostream & out);
  void getSelect(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in, std::ostream & out);
  void holyTrinity(mypair &myPair, std::istream & in, std::ostream & out);
  void printDict(mypair &myPair, std::istream & in, std::ostream & out);
  void uniqeWords(mypair &myPair, std::istream & in, std::ostream & out);
  void wordCount(mypair &myPair, std::istream & in, std::ostream & out);
  void getRename(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in);
  void save(mypair &myPair, std::istream & in);
  void getCompareDicts(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in, std::ostream & out);

  void error(std::ostream & out, const std::string &text);
  bool isNameHere(mypair &pair, const std::string &name);
  void dictOutput(mypair &myPair, std::ostream & out, size_t n, bool mode);
}

#endif
