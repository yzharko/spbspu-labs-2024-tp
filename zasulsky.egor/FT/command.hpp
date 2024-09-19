#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>

using dict = std::map< std::string, std::vector< std::string > >;
using dictOfDicts = std::map< std::string, dict >;

void help(dictOfDicts& ref, std::ostream& out);
void count(dictOfDicts& ref, std::ostream& out);

void translation(dictOfDicts& ref, std::string name, std::string word, std::string translation);
void add(dictOfDicts& ref, std::string name, std::string word, std::string value);

void translate(dictOfDicts& ref, std::string name, std::string word, std::ostream& out);
void search(dictOfDicts& ref, std::string name, std::string substr, std::ostream& out);

void calculate(dictOfDicts& ref, std::string name, std::ostream& out);
void print(dictOfDicts& ref, std::string name, std::ostream& out);
void build(dictOfDicts& ref, std::string name, std::ostream& out);

void combination(dictOfDicts& ref, std::string str);
void intersect(dictOfDicts& ref, std::string str);
void tag(dictOfDicts& ref, std::string str);

void create(dictOfDicts& ref, std::string name);

class Parser
{
public:
  explicit Parser(std::string toparse);
  std::string operator ()();

private:
  std::string parsable_;
  size_t current_;
};

#endif
