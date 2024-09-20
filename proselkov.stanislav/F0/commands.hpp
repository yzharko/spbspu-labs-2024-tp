#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iosfwd>
#include <map>

namespace proselkov
{
  using langDictionary = std::map< std::string, std::string >;
  using majorDictionary = std::map< std::string, langDictionary >;

  void helpCmd(std::ostream& out);
  void createCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void removeCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void printCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void clearCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void deleteCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void insertCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void searchCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void sizeCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void editCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void combineCmd(majorDictionary& major, std::istream& in, std::ostream& out);
  void saveCmd(majorDictionary& major, std::istream& in, std::ostream& out);
}

#endif
