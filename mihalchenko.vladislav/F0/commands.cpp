#include "commands.hpp"
#include <fstream>
#include <ios>
#include "helpDelimiters.hpp"

void mihalchenko::help(std::ostream &out)
{
  out << "List of available commands:\n\
  1. help - output of all commands(active now)\n\
  2. open < filename > - opening a dictionary file, if there is no file - create and open\n\
  3. close < filename > - closing the filename file, if there is no such file - error message\n\
  4. save < filename > - saving changes to the 'filename' file\n\
  5. edit < filename > - editing the 'filename' file\n\
  6. insert < filename > < word > < frequency > - inserting a word-frequency pair into a 'filename' file\n\
  7. remove < filename > < word / frequency > - deleting an item(s) from the dictionary by word / frequency / word and frequency\n\
  8. find < filename > < word / frequency > - output of elements by word or with a given frequency\n\
  9. print < filename > < sort:alph / sort:freq > < reverse:true/false > - output of sorted file elements\n\
  10. view < partOfName > - the output of the names of existing dictionaries, an additional parameter is a part of the name\n\
  11. clear <filename > < start > < stop > - clear the entire dictionary or in the selected range\n\
  12. merge < filename1 > < filename2 > - the exchange of dictionary contents, if there is a problem, the program displays\n\
  the corresponding message\n\
  13. unique < filename1 > < filename2 > < newFileName > - saves unique elements from dictionaries in a new file,\n\
  if any of the files are missing or any other problem occurs, the corresponding message is also displayed\n\
  14. count < filename > < name / frequency > - counting elements with the same name or frequency\n\
  15. size < filename > - print the size of the dictionary\n";
}

void mihalchenko::open(mapOfDicts_t &mapOfDictionaries, std::istream &is)
{
  std::string fileName = "";
  is >> fileName;
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

void mihalchenko::save(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
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
    out << " The data was successfully written to the file" << iterOfDicts.first << '\n';
    outputFile.close();
  }
  out << " The data was successfully written to all files" << '\n';
}

void mihalchenko::size(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDictionary = "";
  is >> nameOfDictionary;
  out << getSize(mapOfDictionaries, nameOfDictionary);
}

void mihalchenko::view(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  size_t num = 1;
  for (auto iter = mapOfDictionaries.cbegin(); iter != mapOfDictionaries.cend(); ++iter)
  {
    num++;
    std::cout << num << ". " << iter->first << ", size = " << getSize(mapOfDictionaries, iter->first) << "\n";
  }
}

void mihalchenko::find(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string name = "";
  is >> name;
  std::string word = "";
  size_t freq = 0;
  auto iterOfDict = mapOfDictionaries.find(name);
  if (is >> word)
  {
    if (iterOfDict->first.find(word) == *iterOfDict->first.end())
    {
      printErrorMessage(out);
    }
    out << iterOfDict->first.find(word);
  }
  else if (is >> freq)
  {
    for (auto it : iterOfDict->second)
    {
      if (it.second == freq)
      {
        out << it.first << "\n";
      }
      else
      {
        printErrorMessage(out);
      }
    }
  }
}

void mihalchenko::rename(mapOfDicts_t &mapOfDictionaries, std::istream &is, std::ostream &out)
{
  std::string nameOfDict = "";
  std::string newnameOfDict = "";

  is >> nameOfDict >> newnameOfDict;

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
  is >> nameOfDelDict;
  if (!mapOfDictionaries.erase(nameOfDelDict))
  {
    printErrorMessage(out);
  }
  else
  {
    out << "Delete dict\n";
  }
}
