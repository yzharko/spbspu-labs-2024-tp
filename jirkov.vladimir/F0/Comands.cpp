#include "Comands.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <vector>

using dictionary = std::multimap< std::string, std::string >;

void jirkov::help(std::istream& input, std::ostream& output)
{
  if (input.peek() != '\n')
  {
    throw std::exception();
  }
  output << "1) help - output of available commands\n";
  output << "2) create <name> - create a dictionary named name\n";
  output << "3) remove <name> - delete a dictionary named name\n";
  output << "4) print <name> - output the contents of the dictionary named name\n";
  output << "5) sort <frequency> <name> - sort the dictionary by frequency\n";
  output << "6) sort <alphabet> <name> - sort the dictionary by alphabet\n";
  output << "7) delete <key> - delete the element\n";
  output << "8) find <key> - output the frequency of an element\n";
  output << "9) open <filename> - open a file to create dictionary from its contents\n";
  output << "10) write <filename> - open a file to write a dictionary\n";
  output << "11) stop - close the dictionary to edit\n";
  output << "12) save - shut down a file, exit edit module, save data\n";
}

void jirkov::createDict(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output)
{
  std::string dictName;
  input >> dictName;
  if (!input)
  {
    return;
  }
  dicts.emplace(dictName, dictionary());
  dictionary currentDict = dicts[dictName];
  using namespace std::placeholders;
  std::map< std::string, std::function< void(dictionary&, std::istream&, std::ostream&) > > cmdDict;
  {
    cmdDict["delete"] = std::bind(jirkov::deleteKey, _1, _2, _3);
    cmdDict["find"] = std::bind(jirkov::findKey, _1, _2, _3);
    cmdDict["open"] = std::bind(jirkov::openFile, _1, _2, _3);
  }
  auto warningMes = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string cmdType;
  while (input >> cmdType && cmdType != "stop")
  {
    try
    {
      cmdDict.at(cmdType)(currentDict, input, output);
      dicts[dictName] = currentDict;
    }
    catch (const std::out_of_range& e)
    {
      warningMes(output);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

void jirkov::deleteKey(dictionary& dict, std::istream& input, std::ostream& output)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "Element does not exist\n");
  std::string key;
  input >> key;
  if (dict.find(key) == dict.end())
  {
    warningMes(output);
    return;
  }
  dict.erase(key);
}

void jirkov::findKey(dictionary& dict, std::istream& input, std::ostream& output)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "Element does not exist\n");
  std::string key;
  input >> key;
  if (dict.find(key) == dict.end() || dict.find(key)->second.empty())
  {
    warningMes(output);
    return;
  }
  output << dict.find(key)->second;
}

void jirkov::openFile(dictionary& dict, std::istream& input, std::ostream& output)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "File does not exist\n");
  std::string word;
  std::vector< std::string > words;
  std::string filename;
  input >> filename;
  std::ifstream in(filename);
  if (!in)
  {
    warningMes(output);
    return;
  }
  while (in >> word)
  {
    std::string lowercaseWord = word;
    std::transform
    (
      word.begin(),
      word.end(),
      lowercaseWord.begin(),
      [](char c)
      {
        return std::tolower(c);
      }
    );
    std::string result = "";
    for (char c : lowercaseWord)
    {
      if (std::isalnum(c))
      {
        result += c;
      }
    }
    words.push_back(result);
  }
  for (auto it = words.begin(); it != words.end(); it++)
  {
    size_t frequency = std::count
    (
      words.begin(),
      words.end(),
      *it
    );
    if (dict.find(*it) == dict.end())
    {
      dict.emplace(*it, std::to_string(frequency));
    }
  }
}

void jirkov::writeToFile(const std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream& out)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "File does not exist\n");
  std::string filename;
  in >> filename;
  std::ofstream output;
  output.open(filename, std::ios::app);
  if (!output)
  {
    warningMes(out);
    return;
  }
  auto warningMesDict = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string dictName;
  in >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    warningMesDict(out);
    return;
  }
  dictionary dict = dicts.find(dictName)->second;
  output << "\n" << dictName << "\n";
  for (auto it = dict.begin(); it != dict.end(); it++)
  {
    output << it->first << ": " << it->second << "\n";
  }
  output.close();
}

void jirkov::removeDict(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream& out)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string dictName;
  in >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    warningMes(out);
    return;
  }
  dicts.erase(dictName);
}

void jirkov::printDict(const std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream& out)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string dictName;
  in >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    warningMes(out);
    return;
  }
  dictionary dictToPrint = dicts.find(dictName)->second;
  out << dictName << "\n";
  if (dictToPrint.empty())
  {
    return;
  }
  for (auto it = dictToPrint.begin(); it != dictToPrint.end(); it++)
  {
    out << it->first << ": " << it->second << "\n";
  }
}

void jirkov::sortDict(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output)
{
  using namespace std::placeholders;
  using func = std::function< void(std::map< std::string, dictionary >&, std::istream&, std::ostream&) >;
  std::map< std::string, func > cmdSort;
  cmdSort["frequency"] = std::bind(jirkov::sortByFrequency, _1, _2, _3);
  cmdSort["alphabet"] = std::bind(jirkov::sortByAlphabet, _1, _2, _3);
  auto warningMes = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string sortType;
  input >> sortType;
  try
  {
    if (dicts.empty())
    {
      warningMes(output);
    }
    else
    {
      cmdSort.at(sortType)(dicts, input, output);
    }
  }
  catch (const std::out_of_range& e)
  {
    warningMes(output);
    std::cin.clear();
    std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
  }
}

void jirkov::sortByFrequency(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream& out)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string dictName;
  in >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    warningMes(out);
    return;
  }
  dictionary dictToSort = dicts.find(dictName)->second;
  if (dictToSort.empty() || std::isdigit(dictToSort.begin()->first[0]))
  {
    return;
  }
  std::multimap< std::string, std::string > temp;
  for (const auto& pair : dictToSort)
  {
    temp.emplace(pair.second, pair.first);
  }
  dicts.erase(dictName);
  dicts.emplace(dictName, temp);
}

void jirkov::sortByAlphabet(std::map< std::string, dictionary >& dicts, std::istream& in, std::ostream& out)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string dictName;
  in >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    warningMes(out);
    return;
  }
  dictionary dictToSort = dicts.find(dictName)->second;
  if (dictToSort.empty() || !std::isdigit(dictToSort.begin()->first[0]))
  {
    return;
  }
  std::multimap< std::string, std::string > temp;
  for (const auto& pair : dictToSort)
  {
    temp.emplace(pair.second, pair.first);
  }
  dicts.erase(dictName);
  dicts.emplace(dictName, temp);
}

void jirkov::warning(std::ostream& output, const std::string& mes)
{
  output << mes;
}
