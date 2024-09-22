#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <map>

namespace gorbunova
{
  using Dictionary = std::map< std::string, std::string >;
  extern std::map< std::string, Dictionary > dictionaries;

  void help();
  void create(const std::string &name);
  void remove(const std::string &name);
  void clear(const std::string &name);
  void print(const std::string &name);
  void size(const std::string &name);
  void list();
  void unite(const std::string &newName, const std::string &name1, const std::string &name2);
  void add(const std::string &name1, const std::string &name2);
  void intersection(const std::string &newName, const std::string &name1, const std::string &name2);
  void insert(const std::string &name, const std::string &key, const std::string &translation);
  void find(const std::string &name, const std::string &key);
  void change(const std::string &name, const std::string &key, const std::string &translation);
  void findLetter(const std::string &name, char letter);
  void deleteElem(const std::string &name, const std::string &key);

}

#endif
