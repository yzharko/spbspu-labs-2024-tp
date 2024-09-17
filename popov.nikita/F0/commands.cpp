#include <iostream>
#include <map>
#include <string>
#include <limits>
#include <vector>
#include <algorithm> 
#include "commands.hpp"

using indictionary = std::map< std::string, size_t >;
using outdictionary = std::map< std::string, indictionary >;

void popov::helpCmd(std::ostream& out)
{
  out << "help - output all possible commands" << "\n";
  out << "create<name> - create a dictionary named name" << "\n";
  out << "add_word<word, name> - adds a word to the frequency dictionary named name" << "\n";
  out << "remove_word<word, name> - removes a word from the frequency dictionary, if it is present" << "\n";
  out << "get_frequency<word, name> - returns the frequency (number of times) the specified word appears in the dictionary" << "\n";
  out << "top_words<name> - displays all words from the most common to the least common" << "\n";
  out << "reset<name> - clears the entire frequency dictionary with the name name" << "\n";
  out << "delete<name> - deletes a dictionary named name" << "\n";
  out << "add_word_frequency<word, amount, name> - adding a word to the dictionary with the specified frequency amount" << "\n";
  out << "increase_frequency<word, amount, name> - increases the frequency of the specified word by a specified amount" << "\n";
  out << "decrease_frequency<word, amount, name> - reduces the frequency of the specified word by a specified amount" << "\n";
  out << "get_words_with_frequency<frequency, name> - returns a list of words with the specified frequency of occurrence in the name dictionary" << "\n";
  out << "print<name> - output of the entire dictionary" << "\n";
  out << "create_same<name1, name2> - create a name2 dictionary with the same words and frequency as in the name1 dictionary" << "\n";
}

void popov::createCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string name;
  if (!(in >> name))
  {
    printWrongInput(out);
    return;
  }
  if (dictionaries.count(name) > 0) 
  {
    out << "Error: Dictionary with name '" << name << "' already exists." << "\n";
    return;
  }
  dictionaries[name] = indictionary();
  out << "Dictionary '" << name << "' created." << "\n";
}

void popov::addWordCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string word, name;
  if (!(in >> word >> name)) 
  {
    printWrongInput(out);
    return;
  }
  if (dictionaries.count(name) == 0) 
  {
    printDictNot(out, name);
    return;
  }
  if (dictionaries[name].count(word) > 0)
  {
    if (dictionaries[name][word] == std::numeric_limits<size_t>::max()) 
    {
      out << "Error: Word count overflow for '" << word << "' in dictionary '" << name << "'." << '\n';
      return;
    }
  }
  dictionaries[name][word]++;
  out << "Word '" << word << "' added to dictionary '" << name << "'." << '\n';
}

void popov::removeWordCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string word, name;
  if (!(in >> word >> name)) 
  {
    printWrongInput(out);
    return;
  }
  if (dictionaries.count(name) == 0)
  {
    printDictNot(out, name);
    return;
  }
  if (dictionaries[name].erase(word) > 0) 
  {
    out << "Word '" << word << "' removed from dictionary '" << name << "'." << '\n';
  }
  else 
  {
    out << "Word '" << word << "' not found in dictionary '" << name << "'." << '\n';
  }
}

void popov::getFrequencyCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string word, name;
  if (!(in >> word >> name)) 
  {
    printWrongInput(out);
    return;
  }
  if (dictionaries.count(name) == 0) 
  {
    printDictNot(out, name);
    return;
  }
  auto it = dictionaries[name].find(word);
  if (it != dictionaries[name].end()) 
  {
    out << "Frequency of word '" << word << "' in dictionary '" << name << "': " << it->second << "\n";
  }
  else 
  {
    out << "Word '" << word << "' not found in dictionary '" << name << "'." << "\n";
  }
}

void popov::topWordsCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string name;
  if (!(in >> name)) 
  {
    printWrongInput(out);
    return;
  }
  if (dictionaries.count(name) == 0) 
  {
    printDictNot(out, name);
    return;
  }
  std::vector<std::pair<std::string, size_t>> wordPairs;
  std::copy(dictionaries[name].begin(), dictionaries[name].end(), std::back_inserter(wordPairs));
  std::sort(wordPairs.begin(), wordPairs.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
    });
  out << "Top words in dictionary '" << name << "':" << "\n";
  std::for_each(wordPairs.begin(), wordPairs.end(), [&out](const auto& pair) {
    out << pair.first << ": " << pair.second << "\n";
    });
}

void popov::resetCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string name;
  if (!(in >> name)) 
  {
    printWrongInput(out);
    return;
  }
  if (dictionaries.count(name) == 0) 
  {
    printDictNot(out, name);
    return;
  }
  dictionaries[name].clear();
  out << "Dictionary '" << name << "' reset." << "\n";
}

void popov::deleteCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string name;
  if (!(in >> name)) 
  {
    printWrongInput(out);
    return;
  }
  if (dictionaries.count(name) == 0) 
  {
    printDictNot(out, name);
    return;
  }
  dictionaries.erase(name);
  out << "Dictionary '" << name << "' deleted." << "\n";
}

void popov::addWordFrequencyCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string word, name;
  size_t amount;
  if (!(in >> word >> amount >> name)) 
  {
    printWrongInput(out);
    throw std::runtime_error("not enough data");
  }
  if (dictionaries.count(name) == 0) 
  {
    printDictNot(out, name);
    return;
  }
  dictionaries[name][word] = amount;
  out << "Word '" << word << "' added to dictionary '" << name << "' with frequency " << amount << "." << "\n";
}

void popov::increaseFrequencyCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string word, name;
  size_t amount;
  if (!(in >> word >> amount >> name)) 
  {
    printWrongInput(out);
    throw std::runtime_error("not enough data");
  }
  if (dictionaries.count(name) == 0) 
  {
    printDictNot(out, name);
    return;
  }
  if (amount > std::numeric_limits<size_t>::max() - dictionaries[name][word]) 
  {
    out << "Error: Invalid increase value. It exceeds the maximum allowed value." << "\n";
    return;
  }
  dictionaries[name][word] += amount;
  out << "Frequency of word '" << word << "' in dictionary '" << name << "' increased by " << amount << "." << "\n";
}

void popov::decreasFrequencyCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string word, name;
  size_t amount;
  if (!(in >> word >> amount >> name)) 
  {
    printWrongInput(out);
    throw std::runtime_error("not enough data");
  }
  if (dictionaries.count(name) == 0) 
  {
    printDictNot(out, name);
    return;
  }
  auto it = dictionaries[name].find(word);
  if (it == dictionaries[name].end()) 
  {
    out << "Word '" << word << "' not found in dictionary '" << name << "'." << "\n";
    return;
  }
  if (it->second >= amount)
  {
    it->second -= amount;
    out << "Frequency of word '" << word << "' in dictionary '" << name << "' decreased by " << amount << "." << "\n";
  }
  else 
  {
    out << "Frequency of word '" << word << "' in dictionary '" << name << "' is less than " << amount << "." << "\n";
  }
}

void popov::getWordsWithFrequencyCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string name;
  size_t frequency;
  if (!(in >> frequency >> name)) 
  {
    printWrongInput(out);
    throw std::runtime_error("not enough data");
  }
  if (dictionaries.count(name) == 0) 
  {
    printDictNot(out, name);
    return;
  }
  std::vector<std::string> wordsWithFrequency;
  for (const auto& item : dictionaries[name]) 
  {
    if (item.second == frequency) 
    {
      wordsWithFrequency.push_back(item.first);
    }
  }
  if (wordsWithFrequency.empty()) 
  {
    out << "No words found with frequency " << frequency << " in dictionary '" << name << "'." << "\n";
  }
  else 
  {
    out << "Words with frequency " << frequency << " in dictionary '" << name << "':" << "\n";
    for (const auto& word : wordsWithFrequency) 
    {
      out << word << "\n";
    }
  }
}

void popov::printCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string name;
  if (!(in >> name)) 
  {
    printWrongInput(out);
    return;
  }
  if (dictionaries.count(name) == 0) 
  {
    printDictNot(out, name);
    return;
  }
  out << "Dictionary '" << name << "':" << "\n";
  if (dictionaries[name].empty()) 
  {
    out << " empty" << "\n";
  }
  else 
  {
    std::for_each(dictionaries[name].begin(), dictionaries[name].end(),
      [&out](const auto& pair) {
        out << "  " << pair.first << ": " << pair.second << "\n";
      });
  }
}

void popov::createSameCmd(outdictionary& dictionaries, std::istream& in, std::ostream& out)
{
  std::string name1, name2;
  if (!(in >> name1 >> name2)) 
  {
    printWrongInput(out);
    return;
  }
  if (dictionaries.count(name1) == 0) 
  {
    printDictNot(out, name1);
    return;
  }
  if (dictionaries.count(name2) > 0) {
    out << "Error: Dictionary with name '" << name2 << "' already exists." << std::endl;
    return;
  }
  dictionaries[name2].insert(dictionaries[name1].begin(), dictionaries[name1].end());
  out << "Dictionary '" << name2 << "' created with the same words and frequencies as '" << name1 << "'." << "\n";
}

void popov::printDictNot(std::ostream& out, std::string name)
{
  out << "Error: Dictionary with name '" << name << "' does not exist." << '\n';
}

void popov::printWrongInput(std::ostream& out)
{
  out << "Wrong input!" << "\n";
}