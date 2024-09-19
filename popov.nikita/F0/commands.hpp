#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>
#include <string>

namespace popov
{
  using indictionary = std::map< std::string, size_t >;
  using outdictionary = std::map< std::string, indictionary >;

  void helpCmd(std::ostream& out);
  void createCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void addWordCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void removeWordCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void getFrequencyCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void topWordsCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void resetCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void deleteCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void addWordFrequencyCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void increaseFrequencyCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void decreasFrequencyCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void getWordsWithFrequencyCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void printCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);
  void createSameCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out);

  void printDictNot(std::ostream& out, std::string name);
  void printWrongInput(std::ostream& out);
}

#endif
