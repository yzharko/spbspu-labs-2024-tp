#include "commands.hpp"
#include <fstream>
#include <ios>
#include <vector>
#include <iterator>
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
    printWrongInput(std::cout);
    return;
  }
  if (fileName.empty())
  {
    printErrorMessage(std::cout);
    return;
  }
  if (fileName.find(".txt") != fileName.size() - 4)
  {
    printErrorMessage(std::cout);
    return;
  }
  std::ifstream inputFile;
  inputFile.open(fileName);
  if (inputFile.is_open())
  {
    dict_t dict;
    std::string nameOfDict = getDictName(fileName);
    while (!inputFile.eof())
    {
      dictElement_t elem;
      inputFile >> elem;
      dict.emplace(elem.first, elem.second);
    }
    mapOfDictionaries.emplace(nameOfDict, dict);
    std::cout << "The dictionary was created successfully from the file\n";
  }
  inputFile.close();
}

void mihalchenko::save(mapOfDicts_t &mapOfDictionaries, std::ostream &out)
{
  for (const auto &iterOfDicts : mapOfDictionaries)
  {
    std::ofstream outputFile;
    if (!outputFile)
    {
      throw std::invalid_argument("ERROR with file\n");
    }
    outputFile.open(iterOfDicts.first + ".txt");
    if (outputFile.is_open())
    {
      for (const auto &it : iterOfDicts.second)
      {
        outputFile << it.first << " " << it.second << "\n";
      }
    }
    out << " The data was successfully written to the file: ";
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
    printWrongInput(out);
    return;
  }
  out << mapOfDictionaries.find(nameOfDictionary)->second.size() << "\n";
}

void mihalchenko::view(mapOfDicts_t &mapOfDictionaries, std::ostream &out)
{
  size_t num = 0;
  out << "List of created dictionaries and their sizes:\n";
  for (const auto &iter : mapOfDictionaries)
  {
    num++;
    out << num << ". " << iter.first << ", size = ";
    if (iter.second.begin() == iter.second.end())
    {
      out << 0 << "\n";
    }
    else
    {
      out << iter.second.size() << "\n";
    }
  }
}

void mihalchenko::find(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string name = "";
  if (!(is >> name))
  {
    printWrongInput(out);
    return;
  }
  size_t freq = 0;
  const auto &iterOfDict = mapOfDictionaries.find(name)->second;
  if (is >> freq)
  {
    for (auto iterOfElem = iterOfDict.begin(); iterOfElem != iterOfDict.end(); iterOfElem++)
    {
      if (iterOfElem->second == freq)
      {
        out << iterOfElem->first << "\n";
      }
    }
  }
  else
  {
    std::string word = "";
    is >> word;
    if (iterOfDict.find(word) == iterOfDict.end())
    {
      throw std::invalid_argument("Error: This elem doesn't exist\n");
    }
    out << "The frequency of this word is: " << iterOfDict.find(word)->second << "\n";
  }
}

void mihalchenko::rename(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string newnameOfDict = "";
  if (!(is >> nameOfDict >> newnameOfDict))
  {
    printWrongInput(out);
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
      out << "The dictionary has been successfully renamed\n";
    }
    else
    {
      throw std::invalid_argument("Error: This dictionary doesn't exist\n");
    }
  }
  else
  {
    throw std::invalid_argument("Error: This dictionary doesn't exist\n");
  }
}

void mihalchenko::deleteDict(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDelDict = "";
  if (!(is >> nameOfDelDict))
  {
    printWrongInput(out);
    return;
  }
  if (!mapOfDictionaries.erase(nameOfDelDict))
  {
    printErrorMessage(out);
    return;
  }
  else
  {
    out << "The dictionary has been successfully deleted\n";
  }
}

void mihalchenko::edit(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string word = "";
  if (!(is >> nameOfDict >> word))
  {
    printWrongInput(out);
    return;
  }
  auto iterOfDict = mapOfDictionaries.find(nameOfDict);
  size_t newFreq;
  if (!(is >> newFreq))
  {
    printWrongInput(out);
    return;
  }
  if (iterOfDict->second.find(word) == iterOfDict->second.end())
  {
    throw std::invalid_argument("Error: This dictionary doesn't exist\n");
  }
  else
  {
    iterOfDict->second.find(word)->second = newFreq;
    out << "The data has been successfully changed\n";
  }
}

void mihalchenko::insert(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string word;
  if (!(is >> nameOfDict))
  {
    printWrongInput(out);
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
      iterOfDicts->second.emplace(dictElem);
      out << "The item was successfully added to the dictionary\n";
    }
    else
    {
      throw std::invalid_argument("Error: This element doesn't exist\n");
    }
  }
  else
  {
    throw std::invalid_argument("Error: This dictionary doesn't exist\n");
  }
}

void mihalchenko::remove(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string word;
  if (!(is >> nameOfDict))
  {
    printWrongInput(out);
    return;
  }
  auto iterOfDicts = mapOfDictionaries.find(nameOfDict);
  if (iterOfDicts != mapOfDictionaries.end())
  {
    auto iterOfElem = iterOfDicts->second;
    if (!(is >> word))
    {
      printWrongInput(out);
      return;
    }
    if (iterOfElem.find(word) != iterOfElem.end())
    {
      iterOfDicts->second.erase(word);
      out << "The item was successfully deleted from the dictionary\n";
    }
    else
    {
      throw std::invalid_argument("Error: This dictionary doesn't exist\n");
    }
  }
}

void mihalchenko::print(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string sortParam = "";
  if (!(is >> nameOfDict >> sortParam))
  {
    printWrongInput(out);
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
  else
  {
    throw std::invalid_argument("Error: This dictionary doesn't exist\n");
  }
}

void mihalchenko::clear(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string param1 = "";
  if (!(is >> nameOfDict >> param1))
  {
    printWrongInput(out);
    return;
  }
  auto &iterOfDicts = mapOfDictionaries.find(nameOfDict)->second;
  if (param1 == "-all")
  {
    mapOfDictionaries.find(nameOfDict)->second.clear();
    out << "The dictionary has been successfully cleared\n";
  }
  else
  {
    std::string param2 = "";
    if (!(is >> param2))
    {
      printWrongInput(out);
      return;
    }
    auto startIterOfElem = iterOfDicts.find(param1);
    auto stopIterOfElem = iterOfDicts.find(param2);
    if (startIterOfElem != iterOfDicts.end() && stopIterOfElem != iterOfDicts.end())
    {
      for (auto iterOfElem = iterOfDicts.find(param1); iterOfElem != iterOfDicts.find(param2); iterOfElem++)
      {
        iterOfDicts.erase(iterOfElem->first);
      }
      out << "Dictionary elements from word " << startIterOfElem->first << " to word "
          << stopIterOfElem->first << " have been successfully deleted\n";
    }
    else
    {
      throw std::invalid_argument("Error: One of these elements doesn't exist\n");
    }
  }
}

void mihalchenko::count(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  size_t freq = 0;
  if (!(is >> nameOfDict >> freq))
  {
    printWrongInput(out);
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
  }
  out << "Words with frequency " << freq << " : " << count << "\n";
}

void mihalchenko::merge(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict1 = "";
  std::string nameOfDict2 = "";
  std::string newname = "";
  if (!(is >> nameOfDict1 >> nameOfDict2 >> newname))
  {
    printWrongInput(out);
    return;
  }
  auto iterOfDict1 = mapOfDictionaries.find(nameOfDict1);
  auto iterOfDict2 = mapOfDictionaries.find(nameOfDict2);
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
    out << "The elements from these dictionaries has been successfully merged into a new file\n";
  }
  else
  {
    throw std::invalid_argument("Error: This dictionary doesn't exist\n");
  }
}

void mihalchenko::unique(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict1 = "";
  std::string nameOfDict2 = "";
  std::string newname = "";
  if (!(is >> nameOfDict1 >> nameOfDict2 >> newname))
  {
    printWrongInput(out);
    return;
  }
  dict_t newDict;
  findUnique(mapOfDictionaries, newDict, nameOfDict1, nameOfDict2, out);
  findUnique(mapOfDictionaries, newDict, nameOfDict2, nameOfDict1, out);
  mapOfDictionaries.emplace(newname, newDict);
  out << "The unique elements from these dictionaries has been successfully merged into a new file\n";
}

void mihalchenko::swap(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict1 = "";
  std::string nameOfDict2 = "";
  if (!(is >> nameOfDict1 >> nameOfDict2))
  {
    printWrongInput(out);
    return;
  }
  std::swap(mapOfDictionaries.find(nameOfDict1)->second, mapOfDictionaries.find(nameOfDict2)->second);
  out << "These dictionaries have successfully exchanged elements\n";
}
