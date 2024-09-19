#include <map>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
namespace hohlova
{
  using Dictionary = std::unordered_map< std::string, std::string >;
  using DictOfDictionary = std::unordered_map<std::string, Dictionary>;

  void help(std::ostream& stream);
  void create(DictOfDictionary& dictOfdict, std::istream& is);
  void size(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
  void view(DictOfDictionary& dictOfdict, std::ostream& out);
  void find(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
  void rename(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
  void edit(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
  void insert(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
  void remove(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out);
  void save(DictOfDictionary& dictOfdict, std::ostream& out);

void printError(const std::string& err);
}
