#include "commands.hpp"
#include <fstream>
#include <string>
#include <cctype>

std::string nikiforov::cutNameFile(std::string& str)
{
  size_t startPos = 0;
  size_t finalPos = str.find(".txt");
  if (str.find_last_of('\\') != std::string::npos)
  {
    startPos = str.find_last_of('\\') + 1;
    finalPos -= 4;
  }
  return std::string(str.substr(startPos, finalPos));
}

void nikiforov::createDictionary(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out, std::string mkdir)
{
  std::string fileName = "";
  in >> fileName;
  if (!fileName.empty())
  {
    if (!mkdir.empty())
    {
      fileName = mkdir + "\\" + fileName;
    }
    std::ifstream input;
    input.open(fileName);

    if (input.is_open())
    {
      std::string name = cutNameFile(fileName);
      std::map< std::string, size_t > dictionary = nikiforov::getDictionary(input);
      mapDictionaries.emplace(name, dictionary);
      out << " The " << name << " dictionary has been added successfully\n";
    }
    else
    {
      out << " Invalid file name\n";
    }

    input.close();
  }
}

std::map<std::string, size_t> nikiforov::getDictionary(std::istream& in)
{
  std::map<std::string, size_t> dictionary;
  std::string word;

  while (!in.eof())
  {
    if (in >> word)
    {
      deleteDelimeters(word);
      if (checkAlpha(word))
      {
        auto search = dictionary.find(word);
        if (search == dictionary.end())
        {
          dictionary.emplace(word, 1);
        }
        else
        {
          dictionary.at(word) = search->second + 1;
        }
      }
    }
  }
  return std::map<std::string, size_t>(dictionary);
}

void nikiforov::deleteDelimeters(std::string& str)
{
  std::map< char, char > delimiters;
  {
    delimiters['"'] = '"';
    delimiters['\''] = '\'';
    delimiters['('] = ')';
    delimiters['['] = ']';
    delimiters['<'] = '>';
    delimiters['{'] = '}';
  }

  if ((str.back() == ',' || str.back() == '.' ||
    str.back() == ':' || str.back() == ';' ||
    str.back() == '!' || str.back() == '?'))
  {
    str.erase(str.end() - 1);
  }
  auto pairDelimetrs = delimiters.find(str.front());
  if (pairDelimetrs != delimiters.end())
  {
    if (str.back() == pairDelimetrs->second)
    {
      str.erase(str.end() - 1);
    }
    str.erase(str.begin());
  }
}

bool nikiforov::checkAlpha(std::string& str)
{
  for (size_t i = 0; i < str.size(); i++)
  {
    if (!isalpha(str.at(i)))
    {
      return false;
    }
  }
  return true;
}

void nikiforov::open(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string mkdir = "";
  in >> mkdir;
  std::string intermediateFile = "intermediateFileWithFiles.txt";
  std::string command = "dir " + mkdir + "\\*.txt /b > " + intermediateFile;
  if (!std::system(command.c_str()))
  {
    std::ifstream fin;
    fin.open(intermediateFile);
    while (!fin.eof())
    {
      createDictionary(mapDictionaries, fin, out, mkdir);
    }
    out << " The files in the folder have been successfully read\n";
  }
  else
  {
    out << " There is no folder with the specified name\n";
  }
}

void nikiforov::deleteDictionary(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string nameDictionaryToDel = "";
  in >> nameDictionaryToDel;

  if (mapDictionaries.erase(nameDictionaryToDel))
  {
    out << " The dictionary has been successfully deleted\n";
  }
  else
  {
    out << " The dictionary does not exist, or it has already been deleted\n";
  }
}

void nikiforov::printNamesDictionaries(const mapDictionaries_t& mapDictionaries, std::ostream& out)
{
  size_t count = 0;
  for (auto it = mapDictionaries.begin(); it != mapDictionaries.end(); ++it) {
    out << ++count << ". " << it->first << "\n";
  }
}

void nikiforov::add(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name1 = "";
  std::string name2 = "";

  in >> name1 >> name2;

  auto firstDictionary = mapDictionaries.find(name1);
  auto secondDictionary = mapDictionaries.find(name2);

  if (firstDictionary != mapDictionaries.end() && secondDictionary != mapDictionaries.end())
  {
    for (auto it = secondDictionary->second.begin(); it != secondDictionary->second.end(); ++it) {
      firstDictionary->second.emplace(it->first, it->second);
    }
    out << " Dictionary '" << name2 << "' successfully added to the dictionary '" << name1 << "'\n";
  }
  else
  {
    out << " Error: Adding a dictionary '" << name2 << "' to the dictionary '" << name1 << "'\n";
  }
}

void nikiforov::unite(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string newname = "";
  std::string name1 = "";
  std::string name2 = "";

  in >> newname >> name1 >> name2;

  if (newname != name1 && newname != name2)
  {
    auto firstDictionary = mapDictionaries.find(name1);
    auto secondDictionary = mapDictionaries.find(name2);

    if (firstDictionary != mapDictionaries.end() && secondDictionary != mapDictionaries.end())
    {
      std::map< std::string, size_t > newDictionary = firstDictionary->second;
      for (auto it = secondDictionary->second.begin(); it != secondDictionary->second.end(); ++it) {
        newDictionary.emplace(it->first, it->second);
      }
      mapDictionaries.emplace(newname, newDictionary);
      out << " Dictionary '" << name2 << "' successfully added to the dictionary '" << name1 << "'\n";
    }
    else
    {
      out << " Error: Dictionary merging '" << name1 << "' and '" << name2 << "' to the dictionary '" << newname << "'\n";
    }
  }
  else
  {
    out << " Error: Dictionary merging '" << name1 << "' and '" << name2 << "' to the dictionary '" << newname << "'\n";
  }
}

void nikiforov::rename(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name = "";
  std::string newname = "";

  in >> name >> newname;

  auto nameDictionary = mapDictionaries.find(name);
  if (nameDictionary != mapDictionaries.end())
  {
    auto newnameDictionary = mapDictionaries.find(newname);
    if (newnameDictionary == mapDictionaries.end())
    {
      mapDictionaries.emplace(newname, nameDictionary->second);
      mapDictionaries.erase(nameDictionary);
      out << " The '" << name << "' dictionary has been successfully renamed to '" << newname << "'\n";
    }
    else
    {
      out << " Error: The dictionary '" << newname << "' already exists, enter a different name" << "\n";
    }
  }
  else
  {
    out << " Error: There is no dictionary with the name '" << name << "'\n";
  }
}

void nikiforov::clear(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name1 = "";
  std::string name2 = "";

  in >> name1 >> name2;

  auto firstDictionary = mapDictionaries.find(name1);
  auto secondDictionary = mapDictionaries.find(name2);

  if (firstDictionary != mapDictionaries.end() && secondDictionary != mapDictionaries.end())
  {
    for (auto it = secondDictionary->second.begin(); it != secondDictionary->second.end(); ++it) {
      if (firstDictionary->second.find(it->first) != firstDictionary->second.end())
      {
        firstDictionary->second.erase(it->first);
      }
    }
    out << " All existing words in the '" << name2 << "' dictionary have been removed from the '" << name1 << "' dictionary\n";
  }
  else
  {
    out << " Error: One or both of the dictionaries do not exist\n";
  }
}

void nikiforov::save(const mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string nameMkdir = "";
  in >> nameMkdir;
  std::string commandCreateMkdir = "mkdir " + nameMkdir;

  std::ofstream fout;
  if (!std::system(commandCreateMkdir.c_str()))
  {
    writingDictionaries(mapDictionaries, nameMkdir, fout);
    out << " The data was successfully written to the folder" << nameMkdir << "\n";
  }
  else
  {
    out << " The folder already exists, do you want to overwrite it (yes/no)? \n";
    std::string consent = "";
    in >> consent;

    if (consent == "yes" || consent == "y")
    {
      writingDictionaries(mapDictionaries, nameMkdir, fout);
      out << " The data was successfully written to the folder" << nameMkdir << "\n";
    }
    else
    {
      out << "The data was not written to the folder " << nameMkdir << "\n";
    }
  }
}

void nikiforov::writingDictionaries(const mapDictionaries_t& mapDictionaries, std::string nameMkdir, std::ofstream& fout)
{
  for (auto dictionary : mapDictionaries)
  {
    fout.open(nameMkdir + "\\" + dictionary.first + ".txt");
    if (fout.is_open())
    {
      for (auto pairItems : dictionary.second)
      {
        printWordAndFrequency(pairItems, fout);
      }
    }
    fout.close();
  }
}

void nikiforov::ActionsOnTheDictionary::select(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string nameDictionary;
  in >> nameDictionary;
  auto SelectedDictionary = mapDictionaries.find(nameDictionary);

  if (SelectedDictionary != mapDictionaries.end())
  {
    nameSelectedDictionary = SelectedDictionary->first;
    out << " The dictionary '" << nameDictionary << "' has been successfully selected\n";
  }
  else
  {
    out << " Error: Dictionary with the name '" << nameDictionary << "' does not exist\n";
  }
}

void nikiforov::ActionsOnTheDictionary::print(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{

  if (isSelectedDictionary())
  {
    auto SelectedDictionary = mapDictionaries.find(nameSelectedDictionary);
    invertedMap_t invertedDictionary = nikiforov::invertedMap(SelectedDictionary->second);

    std::string option;
    if (in.get() != '\n' && in >> option)
    {
      if (option == "most")
      {
        printMost(invertedDictionary, in, out);
      }
      else if (option == "count")
      {
        out << " The dictionary '" << nameSelectedDictionary << "' contains " << invertedDictionary.size() << " words\n";
      }
      else
      {
        out << " Error: Invalid option\n";
      }
    }
    else
    {
      out << " The contents of the dictionary '" << nameSelectedDictionary << "':\n";
      for (auto iterPair = invertedDictionary.rbegin(); iterPair != invertedDictionary.rend(); ++iterPair) {
        printWordAndFrequency(iterPair, out);
      }
    }
  }
  else
  {
    out << " The dictionary is not selected\n";
    out << " Select a dictionary using the command 'select < name >'\n";
  }
}

void nikiforov::ActionsOnTheDictionary::printMost(invertedMap_t& invertDictionary, std::istream& in, std::ostream& out)
{
  size_t numOfTheMostFrequent = 0;
  in >> numOfTheMostFrequent;
  out << " The " << numOfTheMostFrequent << " most common words\n";

  size_t count = 0;
  for (auto iterPair = invertDictionary.rbegin(); iterPair != invertDictionary.rend(); ++iterPair) {
    if (numOfTheMostFrequent != count++)
    {
      out << count << ". ";
      printWordAndFrequency(iterPair, out);
    }
    else
    {
      break;
    }
  }
}

void nikiforov::ActionsOnTheDictionary::find(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  if (isSelectedDictionary())
  {
    auto SelectedDictionary = mapDictionaries.find(nameSelectedDictionary);
    std::string enteredWord = "";
    in >> enteredWord;

    auto iterPair = SelectedDictionary->second.find(enteredWord);
    if (iterPair != SelectedDictionary->second.end())
    {
      printWordAndFrequency(iterPair, out);
    }
    else
    {
      out << " Error: The word '" << enteredWord << "' was not found\n";
    }
  }
  else
  {
    out << " The dictionary is not selected\n";
    out << " Select a dictionary using the command 'select < name >'\n";
  }
}

void nikiforov::ActionsOnTheDictionary::erase(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  if (isSelectedDictionary())
  {
    auto SelectedDictionary = mapDictionaries.find(nameSelectedDictionary);
    std::string enteredWord = "";
    in >> enteredWord;

    auto deletedWord = SelectedDictionary->second.find(enteredWord);
    if (deletedWord != SelectedDictionary->second.end())
    {
      SelectedDictionary->second.erase(deletedWord);
      out << " The word '" << enteredWord << "' has been successfully deleted\n";
    }
    else
    {
      out << " Error: The word " << enteredWord << " was not found\n";
    }
  }
  else
  {
    out << " The dictionary is not selected\n";
    out << " Select a dictionary using the command 'select < name >'\n";
  }
}

bool nikiforov::ActionsOnTheDictionary::isSelectedDictionary()
{
  return nameSelectedDictionary.empty() ? false : true;
}

void nikiforov::printWordAndFrequency(std::map< std::string, size_t >::iterator iterPair, std::ostream& out)
{
  out << iterPair->first << " " << iterPair->second << "\n";
}

void nikiforov::printWordAndFrequency(std::reverse_iterator < std::map< size_t, std::string >::iterator> iterPair, std::ostream& out)
{
  out << iterPair->second << " " << iterPair->first << "\n";
}

void nikiforov::printWordAndFrequency(std::pair< std::string, size_t > pair, std::ostream& out)
{
  out << pair.first << " " << pair.second << "\n";
}
