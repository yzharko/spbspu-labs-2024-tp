#include "commands.hpp"
#include <fstream>
#include <ios>
#include "helpDelimiters.hpp"

void mihalchenko::help(std::ostream &out)
{
  out << "List of available commands:\n";
  out << "1. help - displays information about available commands(active now)\n";
  out << "2. create < filename > - opening the filename file, if it does not exist,\n";
  out << "then creating it and forming a dictionary with the same name from its data\n";
  out << "3. save < filename > - saving changes to the 'filename' file\n";
  out << "4. edit < name > < word > < new frequency > - edit dictionary elements,\n";
  out << "their names and frequencies\n";
  out << "5. insert < name > < word > < frequency > - inserting a word-frequency pair\n";
  out << "6. remove < name > < word > - deleting an item(s) from the dictionary\n";
  out << "by word / frequency / word and frequency\n";
  out << "7. rename < oldname > < newname > - renaming the dictionary from oldname to newname\n";
  out << "8. delete < name > - deleting a frequency dictionary\n";
  out << "9. find < name > < word / frequency > - output of element(s) by word\n";
  out << "10. print < name > < sort:no / sort:alph / sort:freq > < reverse:true/false > - output\n";
  out << "dictionary elements according to the specified sorting conditions\n";
  out << "11. view - the output of the names of existing dictionaries\n";
  out << "12. clear < name > < start > < stop > - clear the entire dictionary or\n";
  out << "in the selected range\n";
  out << "13. swap < name1 > < name2 > - the exchange of dictionary contents,\n";
  out << "if there is a problem, the program displays the corresponding message\n";
  out << "14. merge < name1 > < name2 > < newname > - combines the contents of\n";
  out << "the first two dictionaries in the third\n";
  out << "15. unique < name1 > < name2 > < newName > - saves unique elements\n";
  out << "from dictionaries in a new file, if any of the files are missing or\n";
  out << "any other problem occurs, the corresponding message is also displayed\n";
  out << "16. count < name > < word / frequency > - counting elements with \n";
  out << "the same name or frequency\n";
  out << "17. size < name > - print the size of the dictionary\n";
}

void mihalchenko::create(mapOfDicts_t &mapOfDictionaries, std::istream &is)
{
  std::string fileName = "";
  if (!(is >> fileName))
  {
    std::cout << "ERROR" << "\n";
    return;
  }
  std::ifstream inputFile;
  inputFile.open(fileName);
  if (inputFile.is_open())
  {
    dict_t dict;
    std::string nameOfDict = mihalchenko::getDictName(fileName);
    while (!is.eof())
    {
      mihalchenko::dict_t dict;
      is >> dict;
    }
    mapOfDictionaries.emplace(nameOfDict, dict);
  }
  inputFile.close();
}

void mihalchenko::save(mapOfDicts_t &mapOfDictionaries, std::ostream &out)
{
  for (auto iterOfDicts : mapOfDictionaries)
  {
    std::ofstream outputFile(iterOfDicts.first);
    if (!outputFile)
    {
      throw std::invalid_argument("ERROR with file\n");
    }
    outputFile.open(iterOfDicts.first + "txt");
    if (outputFile.is_open())
    {
      for (auto it : iterOfDicts.second)
      {
        outputFile << it.first << " " << it.second << "\n";
      }
    }
    out << " The data was successfully written to the file";
    out << iterOfDicts.first << '\n';
    outputFile.close();
  }
  out << " The data was successfully written to all files" << '\n';
}

void mihalchenko::size(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDictionary = "";
  if (!(is >> nameOfDictionary))
  {
    printErrorMessage(out);
    return;
  }
  out << getSize(mapOfDictionaries, nameOfDictionary);
}

void mihalchenko::view(mapOfDicts_t &mapOfDictionaries, std::ostream &out)
{
  size_t num = 1;
  for (auto iter = mapOfDictionaries.cbegin(); iter != mapOfDictionaries.cend(); ++iter)
  {
    num++;
    out << num << ". " << iter->first << ", size = ";
    out << getSize(mapOfDictionaries, iter->first) << "\n";
  }
}

void mihalchenko::find(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string name = "";
  if (!(is >> name))
  {
    printErrorMessage(out);
    return;
  }
  std::string word = "";
  size_t freq = 0;
  auto iterOfDict = mapOfDictionaries.find(name)->second;
  if (is >> word)
  {
    if (iterOfDict.find(word) == iterOfDict.end())
    {
      printErrorMessage(out);
      return;
    }
    out << iterOfDict.find(word)->first;
  }
  else if (is >> freq)
  {
    for (auto it : iterOfDict)
    {
      if (it.second == freq)
      {
        out << it.first << "\n";
      }
      else
      {
        printErrorMessage(out);
        return;
      }
    }
  }
  else
  {
    printErrorMessage(out);
  }
}

void mihalchenko::rename(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string newnameOfDict = "";
  if (!(is >> nameOfDict >> newnameOfDict))
  {
    printErrorMessage(out);
    return;
  }
  auto iterOfDictName = mapOfDictionaries.find(nameOfDict);
  if (iterOfDictName != mapOfDictionaries.end())
  {
    auto iterOfNewDictName = mapOfDictionaries.find(newnameOfDict);
    if (iterOfNewDictName == mapOfDictionaries.end())
    {
      mapOfDictionaries.emplace(newnameOfDict, iterOfDictName->second);
      mapOfDictionaries.erase(iterOfDictName);
    }
    else
    {
      printErrorMessage(out);
      return;
    }
  }
  else
  {
    printErrorMessage(out);
  }
}

void mihalchenko::deleteDict(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDelDict = "";
  if (!(is >> nameOfDelDict))
  {
    printErrorMessage(out);
    return;
  }
  if (!mapOfDictionaries.erase(nameOfDelDict))
  {
    printErrorMessage(out);
    return;
  }
  else
  {
    out << "Dict deleted\n";
  }
}

void mihalchenko::edit(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string word = "";
  if (!(is >> nameOfDict >> word))
  {
    printErrorMessage(out);
    return;
  }
  auto iterOfDict = mapOfDictionaries.find(nameOfDict);
  size_t newFreq;
  if (!(is >> newFreq))
  {
    printErrorMessage(out);
    return;
  }
  if (iterOfDict->second.find(word) == iterOfDict->second.end())
  {
    printErrorMessage(out);
    return;
  }
  else
  {
    iterOfDict->second.find(word)->second = newFreq;
  }
}

void mihalchenko::insert(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string word;
  if (!(is >> nameOfDict))
  {
    printErrorMessage(out);
    return;
  }
  auto iterOfDicts = mapOfDictionaries.find(nameOfDict);
  if (iterOfDicts != mapOfDictionaries.end())
  {
    auto iterOfElem = iterOfDicts->second;
    dictElement_t dictElem;
    is >> dictElem;
    if (iterOfElem.find(word) != iterOfElem.end())
    {
      iterOfDicts->second.insert(iterOfElem.end(), dictElem);
    }
    else
    {
      printErrorMessage(out);
    }
  }
}

void mihalchenko::remove(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string word;
  if (!(is >> nameOfDict))
  {
    printErrorMessage(out);
    return;
  }
  auto iterOfDicts = mapOfDictionaries.find(nameOfDict);
  if (iterOfDicts != mapOfDictionaries.end())
  {
    auto iterOfElem = iterOfDicts->second;
    if (!(is >> word))
    {
      printErrorMessage(out);
      return;
    }
    if (iterOfElem.find(nameOfDict) != iterOfElem.end())
    {
      iterOfDicts->second.erase(word);
    }
  }
}

void mihalchenko::print(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string sortParam = "";
  if (!(is >> nameOfDict >> sortParam))
  {
    printErrorMessage(out);
    return;
  }
  if (mapOfDictionaries.find(nameOfDict) != mapOfDictionaries.end())
  {
    if (sortParam == "no")
    {
      for (const auto &iterOfElem : mapOfDictionaries.find(nameOfDict)->second)
      {
        out << iterOfElem.first << " : " << iterOfElem.second << "\n";
      }
    }
    else if (sortParam == "freq")
    {
      sortByFreq(mapOfDictionaries, nameOfDict, is, out);
    }
    else if (sortParam == "alph")
    {
      sortByAlph(mapOfDictionaries, nameOfDict, is, out);
    }
    else
    {
      printErrorMessage(out);
    }
  }
}

void mihalchenko::clear(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string param1 = "";
  if (!(is >> nameOfDict >> param1))
  {
    printErrorMessage(out);
    return;
  }
  if (param1 == "-all")
  {
    auto iterOfDicts = mapOfDictionaries.find(nameOfDict)->second;
    for (auto iterOfElem : iterOfDicts)
    {
      iterOfDicts.erase(iterOfElem.first);
    }
  }
  else
  {
    std::string param2 = "";
    if (!(is >> param2))
    {
      printErrorMessage(out);
      return;
    }
    auto iterOfDicts = mapOfDictionaries.find(nameOfDict)->second;
    auto startIterOfElem = iterOfDicts.find(param1);
    auto stopIterOfElem = iterOfDicts.find(param2);
    if (startIterOfElem != iterOfDicts.end() && stopIterOfElem != iterOfDicts.end())
    {
      for (auto iterOfElem : iterOfDicts)
      {
        iterOfDicts.erase(iterOfElem.first);
      }
    }
    else
    {
      printErrorMessage(out);
    }
  }
}

void mihalchenko::count(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  if (!(is >> nameOfDict))
  {
    printErrorMessage(out);
    return;
  }
  size_t freq = 0;
  if (!(is >> freq))
  {
    printErrorMessage(out);
    return;
  }
  auto iterOfDicts = mapOfDictionaries.find(nameOfDict)->second;
  size_t count = 0;
  for (auto it : iterOfDicts)
  {
    if (it.second == freq)
    {
      count++;
    }
    else
    {
      printErrorMessage(out);
      return;
    }
  }
  out << count << "\n";
}

void mihalchenko::merge(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict1 = "";
  std::string nameOfDict2 = "";
  std::string newname = "";
  if (!(is >> nameOfDict1 >> nameOfDict2 >> newname))
  {
    printErrorMessage(out);
    return;
  }
  auto iterOfDict1 = mapOfDictionaries.find(nameOfDict1);
  auto iterOfDict2 = mapOfDictionaries.find(nameOfDict2);
  /*if (iterOfDict1->second.size() != iterOfDict2->second.size())
  {
    printErrorMessage(out);
    return;
  }*/
  if (iterOfDict1 != mapOfDictionaries.end() && iterOfDict2 != mapOfDictionaries.end())
  {
    dict_t newDict;
    for (auto iterOfElem : iterOfDict1->second)
    {
      newDict.emplace(iterOfElem.first, iterOfElem.second);
    }
    for (auto iterOfElem : iterOfDict2->second)
    {
      newDict.emplace(iterOfElem.first, iterOfElem.second);
    }
    mapOfDictionaries.emplace(newname, newDict);
  }
  else
  {
    printErrorMessage(out);
  }
}
