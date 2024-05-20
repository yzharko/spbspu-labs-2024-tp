#include "commands.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <vector>

using dictionary = std::multimap< std::string, std::string >;

void doroshenko::help(std::istream& input, std::ostream& output)
{
  if (input.peek() != '\n')
  {
    throw std::exception();
  }
  std::string text = "   1) help - вывод списка доступных команд\n \
  2) create <name> - создание словаря с именем name\n \
  3) remove <name> - удаление словаря с именем name\n \
  4) print <name> - вывод содержимого словаря с именем name\n \
  5) sort <frequency> <name> - сортировка словаря по частоте\n \
  6) sort <alphabet> <name> - сортировка словаря по алфавиту\n \
  7) delete <key> - удаление элемента с ключом key\n \
  8) find <key> - вывод частоты словаря с ключом key\n \
  9) open <filename> - открытие файла для создание из его содержимого словаря\n \
  10) write <filename> - открытие файла для записи словаря\n \
  11) stop - закрытие словаря для записи\n \
  12) save - завершение работы с файлом, выход из режима редактирования, сохранение данных\n";
  output << text;
}

void doroshenko::createDict(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output)
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
    cmdDict["delete"] = std::bind(doroshenko::deleteKey, _1, _2, _3);
    cmdDict["find"] = std::bind(doroshenko::findKey, _1, _2, _3);
    cmdDict["open"] = std::bind(doroshenko::openFile, _1, _2, _3);
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

void doroshenko::deleteKey(dictionary& dict, std::istream& input, std::ostream& output)
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

void doroshenko::findKey(dictionary& dict, std::istream& input, std::ostream& output)
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

void doroshenko::openFile(dictionary& dict, std::istream& input, std::ostream& output)
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
      [](char c) { return std::tolower(c); }
    );
    words.push_back(lowercaseWord);
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

void doroshenko::writeToFile(const std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& outp)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "File does not exist\n");
  std::string filename;
  input >> filename;
  std::ofstream out;
  out.open(filename, std::ios::app);
  if (!out)
  {
    warningMes(outp);
    return;
  }
  auto warningMesDict = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string dictName;
  input >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    warningMesDict(outp);
    return;
  }
  dictionary dict = dicts.find(dictName)->second;
  out << "\n" << dictName << "\n";
  for (auto it = dict.begin(); it != dict.end(); it++)
  {
    out << it->first << ": " << it->second << "\n";
  }
  out.close();
}

void doroshenko::removeDict(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string dictName;
  input >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    warningMes(output);
    return;
  }
  dicts.erase(dictName);
}

void doroshenko::printDict(const std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string dictName;
  input >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    warningMes(output);
    return;
  }
  dictionary dictToPrint = dicts.find(dictName)->second;
  output << dictName << "\n";
  if (dictToPrint.empty())
  {
    return;
  }
  for (auto it = dictToPrint.begin(); it != dictToPrint.end(); it++)
  {
    output << it->first << ": " << it->second << "\n";
  }
}

void doroshenko::sortDict(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output)
{
  using namespace std::placeholders;
  using func = std::function< void(std::map< std::string, dictionary >&, std::istream&, std::ostream&) >;
  std::map< std::string, func > cmdSort;
  cmdSort["frequency"] = std::bind(doroshenko::sortByFrequency, _1, _2, _3);
  cmdSort["alphabet"] = std::bind(doroshenko::sortByAlphabet, _1, _2, _3);
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

void doroshenko::sortByFrequency(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string dictName;
  input >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    warningMes(output);
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

void doroshenko::sortByAlphabet(std::map< std::string, dictionary >& dicts, std::istream& input, std::ostream& output)
{
  auto warningMes = std::bind(warning, std::placeholders::_1, "Dictionary does not exist\n");
  std::string dictName;
  input >> dictName;
  if (dicts.find(dictName) == dicts.end())
  {
    warningMes(output);
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

void doroshenko::warning(std::ostream& output, const std::string& mes)
{
  output << mes;
}
