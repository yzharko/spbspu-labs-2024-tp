#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include "command.hpp"

using dictionary = std::map<std::string, int>;

void sadofeva::menuCommand(std::istream&, std::ostream& out)
{
  out << "1. help - displaying a list of available commands with parameters\n"; //+
  out << "2. insert <name dictionary> <word> - \n"; // + 
  out << "3. remove <name dictionary> <world> -\n"; // +
  out << "4. search <name dictionary> <world> - \n"; // +
  out << "5. printMaxCountWorld <name dictionary> <name> - \n"; // +
  out << "7. size <name dictionary> -\n"; // +
  out << "8. union <name new dictionary> <name 1> <name 2> -\n"; // +
  out << "9. save <name dictionary> <file name> - \n"; // +
  out << "10. clear <name dictionary> - \n"; // +
  out << "11. count <name dictionary> - \n"; // +
  out << "12. print <name dictionary> -\n"; // +
}

void sadofeva::print(const std::map < std::string, dictionary >& dicts, std::istream& in, std::ostream& out) // ������� ���� 
{
  std::string dictName;
  in >> dictName;
  auto it = dicts.find(dictName);
  if (it != dicts.end())
  {
    const auto& words = it->second;
    for (const auto& [word, count] : words)
    {
      out << word << count << "\n";
    }
  }
  else
  {
    out << "Dinctionary not found.\n";
  }
}

void sadofeva::countTo(const std::map < std::string, dictionary >& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName;
  in >> dictName;
  auto it = dicts.find(dictName);
  if (it != dicts.end())
  {
    if (it->second.empty())
    {
      out << "Dictionary is empty\n";
    }
  }
  std::vector< std::pair < std::string, int > > wordList(it->second.begin(), it->second.end());

  std::sort(wordList.begin(), wordList.end(), [](const auto& a, const auto& b)
    {
      if (a.second == b.second)
      {
        return a.first < b.first;
      }
      return a.second > b.second;
    });
  int countTo = std::min(5, static_cast<int> (wordList.size()));
  out << "TOP\"" << countTo << "most frequent words in dictionary \"" << dictName << "\n";
  for (int i = 0; i < countTo; i++)
  {
    out << wordList[i].first << wordList[i].second << "\n";
  }
}

void sadofeva::insert(std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName, word;
  in >> dictName >> word;
  if (dictName.empty() || word.empty())
  {
    throw std::invalid_argument("Dictionary name or word us empty");
  }
  auto it = dicts.find(dictName);
  if (it != dicts.end())
  {
    it->second[word]++;
    out << "Word added to dictionary";
  }
  else
  {
    out << "Create dictionary";
  }
}

void sadofeva::remove(std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName, word;
  in >> dictName >> word;
  auto it = dicts.find(dictName);
  if (it != dicts.end())
  {
    auto wordIt = it->second.find(word);
    if (wordIt != it->second.end())
    {
      it->second.erase(wordIt);
      out << "Word removed";
    }
    else
    {
      out << "Word not found";
    }
  }
}

void sadofeva::search(const std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName, word;
  in >> dictName >> word;

  auto it = dicts.find(dictName);
  if (it != dicts.end())
  {
    auto wordIt = it->second.find(word);
    if (wordIt != it->second.end())
    {
      out << "Word found in dictionary:" << dictName;
    }
  }
  else
  {
    out << "Dictionary not found.\n";
  }
}

void sadofeva::printMaxCountWorld(const std::map< std::string, dictionary>& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName, word;
  in >> dictName >> word;

  auto it = dicts.find(dictName);
  if (it != dicts.end())
  {
    auto wordIt = it->second.find(word);
    if (wordIt != it->second.end())
    {
      out << "Word found in dictionary:" << dictName << "count" << wordIt->second << "\n";
    }
  }
  else
  {
    out << "Dictionary not found.\n";
  }
}

void sadofeva::size(const std::map< std::string, dictionary>& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName;
  in >> dictName;

  auto it = dicts.find(dictName);
  if (it != dicts.end())
  {
    out << "Dictionary" << dictName << "size = " << it->second.size() << "\n";
  }
  else
  {
    out << "Dictionary not found\n";
  }
}

void sadofeva::save(const std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName, fileName;
  in >> dictName >> fileName;
  auto it = dicts.find(dictName);
  if (it != dicts.end())
  {
    std::ofstream file(fileName);
    if (!file.is_open())
    {
      out << "Error:: could not open file\n";
      return;
    }

    for (const auto& wordEntry : it->second)
    {
      file << wordEntry.first << " " << wordEntry.second << "\n";
    }
    out << "Dictionary " << dictName << " saved to file" << fileName;
  }
  else
  {
    out << "Dictionary not found\n";
  }
}

void sadofeva::clear(std::map < std::string, dictionary>& dicts, std::istream& in, std::ostream& out)
{
  std::string dictName;
  in >> dictName;
  auto it = dicts.find(dictName);
  if (it != dicts.end())
  {
    dicts.erase(it);
    out << "Dinctionary clear\n";
  }
  else
  {
    out << "Dinctionary not found\n";
  }
}

void sadofeva::union1(std::map<std::string, dictionary>& dicts, std::istream& in, std::ostream& out)
{
  std::string newDictName, dict1Name, dict2Name;
  in >> newDictName >> dict1Name >> dict2Name;

  auto it1 = dicts.find(dict1Name);
  auto it2 = dicts.find(dict2Name);

  if (it1 != dicts.end() && it2 != dicts.end())
  {
    dictionary newDict;

    for (const auto& wordEntry : it1->second)
    {
      newDict[wordEntry.first] = wordEntry.second;
    }

    for (const auto& wordEntry : it2->second)
    {
      newDict[wordEntry.first] += wordEntry.second;
    }
    dicts[newDictName] = newDict;
    out << "New dictionary " << newDictName << "has been created by mergind" << dict1Name << "and" << dict2Name << "\n";
  }
  else
  {
    if (it1 == dicts.end())
    {
      out << "Dictionare not found";
    }
    if (it2 == dicts.end())
    {
      out << "Dictionary not found";
    }
  }
}

