#include "helpFunctions.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string mihalchenko::getDictName(std::string &str)
{
  return str.substr(0, str.find(".txt"));
}

size_t mihalchenko::getSize(mapOfDicts_t &mapOfDictionaries, const std::string &nameOfDict)
{
  size_t size = 0;
  for (auto iter = mapOfDictionaries.cbegin(); iter != mapOfDictionaries.cend(); ++iter)
  {
    if (iter->first == nameOfDict)
    {
      for (auto iterDictElem = iter->second.cbegin();
           iterDictElem != iter->second.cend(); ++iterDictElem)
      {
        size++;
      }
      break;
    }
  }
  return size;
}

std::ostream &mihalchenko::sortByFreq(mapOfDicts_t &mapOfDictionaries, const std::string &nameOfDict,
                                      std::istream &is, std::ostream &out)
{
  std::vector<std::pair<std::string, size_t>> vecToSort;
  for (const auto &iterOfElem : mapOfDictionaries.find(nameOfDict)->second)
  {
    vecToSort.push_back({iterOfElem.first, iterOfElem.second});
  }
  std::sort(vecToSort.begin(), vecToSort.end(), compareElemByFreq);
  bool reverseParam = false;
  is >> reverseParam;
  if (reverseParam == true)
  {
    std::reverse(vecToSort.begin(), vecToSort.end());
  }
  for (const auto &iterOfElem : vecToSort)
  {
    out << iterOfElem.first << " : " << iterOfElem.second << "\n";
  }
  return out;
}

bool mihalchenko::compareElemByFreq(const pair_t &iterOfElem1, const pair_t &iterOfElem2)
{
  return iterOfElem1.second > iterOfElem2.second;
}

std::ostream &mihalchenko::sortByAlph(mapOfDicts_t &mapOfDictionaries, const std::string &nameOfDict,
                                      std::istream &is, std::ostream &out)
{
  std::vector<std::pair<std::string, size_t>> vecToSort;
  for (const auto &iterOfElem : mapOfDictionaries.find(nameOfDict)->second)
  {
    vecToSort.push_back({iterOfElem.first, iterOfElem.second});
  }
  std::sort(vecToSort.begin(), vecToSort.end(), compareElemByFreq);
  bool reverseParam = false;
  is >> reverseParam;
  if (reverseParam == true)
  {
    std::reverse(vecToSort.begin(), vecToSort.end());
  }
  for (const auto &iterOfElem : vecToSort)
  {
    out << iterOfElem.first << " : " << iterOfElem.second << "\n";
  }
  return out;
}

bool mihalchenko::compareElemByAlph(const pair_t &iterOfElem1, const pair_t &iterOfElem2)
{
  return iterOfElem1.first > iterOfElem2.first;
}

std::ostream &mihalchenko::printInvalidCommand(std::ostream &out)
{
  out << "<INVALID COMMAND>" << '\n';
  return out;
}

std::ostream &mihalchenko::printErrorMessage(std::ostream &out)
{
  out << "ERROR" << '\n';
  return out;
}
