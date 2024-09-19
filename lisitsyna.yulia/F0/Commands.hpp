#ifndef COMMANDS_H
#define COMMANDS_H

#include <iosfwd>
#include <fstream>

#include "WordsDict.hpp"

class Commands
{
public:
  Commands(std::istream&, std::ostream&);
  void help();
  void openFile();
  void analyze();
  void closeFile();
  void print();
  void deleteKey();
  void exist() const;
  void search() const;
  void showSize() const;
  void remove();

  void invalidCommand();

private:
  std::istream& in_;
  std::ostream& out_;

  std::ifstream fin_;

  std::map<std::string, WordsDict> dicts_;
};

#endif
