#include "commands.hpp"
#include <fstream>

std::string nikiforov::cutNameFile(std::string& str)
{
  return std::string(str.substr(0, str.find(".txt")));
}

void nikiforov::createDictionary(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string fileName = "";
  in >> fileName;
  std::ifstream input;
  input.open(fileName);

  if (input.is_open())
  {
    std::string name = cutNameFile(fileName);
    std::map< std::string, size_t > dictionary = nikiforov::getDictionary(input);
    mapDictionaries.emplace(name, dictionary);
  }
  else
  {
    throw std::out_of_range("");
  }

  input.close();
}

std::map<std::string, size_t> nikiforov::getDictionary(std::istream& in)
{
  std::map<std::string, size_t> dictionary;

  std::string word;
  size_t frequency = 0;

  while (!in.eof())
  {
    if (in >> word >> frequency)
    {
      auto search = dictionary.find(word);
      if (search == dictionary.end())
      {
        dictionary.emplace(word, frequency);
      }
    }
  }
  return std::map<std::string, size_t>(dictionary);
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

void nikiforov::printNamesDictionaries(const mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
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
      out << " The " << name << " dictionary has been successfully renamed to " << newname << "\n";
    }
    else
    {
      out << " Error: The dictionary " << newname << " already exists, enter a different name" << "\n";
    }
  }
  else
  {
    out << " Error: There is no dictionary with the name " << name << "\n";
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
    out << " All existing words in the " << name2 << " dictionary have been removed from the " << name1 << " dictionary\n";
  }
  else
  {
    out << " Error: One or both of the dictionaries do not exist\n";
  }
}
void nikiforov::ActionsOnTheDictionary::select(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string nameDictionary;
  in >> nameDictionary;
  auto SelectedDictionary = mapDictionaries.find(nameDictionary);

  if (SelectedDictionary != mapDictionaries.end())
  {
    nameSelectedDictionary = nameDictionary;
    out << " The dictionary " << nameSelectedDictionary << " has been successfully selected\n";
  }
  else
  {
    out << " Error: Dictionary with the name " << nameDictionary << " does not exist\n";
  }
}

void nikiforov::ActionsOnTheDictionary::print(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  if (isSelectedDictionary())
  {
    auto SelectedDictionary = mapDictionaries.find(nameSelectedDictionary);
    std::multimap<size_t, std::string> invertedDictionary = nikiforov::invertedMap(SelectedDictionary->second);

    std::string option;
    if (in.get() != '\n' && in >> option)
    {
      if (option == "most")
      {
        size_t numOfTheMostFrequent = 0;
        in >> numOfTheMostFrequent;
        out << " The " << numOfTheMostFrequent << " most common words\n";

        size_t count = 0;
        for (auto it = invertedDictionary.rbegin(); it != invertedDictionary.rend(); ++it) {
          if (numOfTheMostFrequent != count++)
          {
            out << count << ". " << it->second << " " << it->first << "\n";
          }
          else
          {
            break;
          }
        }
      }
      else if (option == "count")
      {
        size_t countWords = 0;
        for (auto word : invertedDictionary)
        {
          countWords++;
        }
        out << " The dictionary " << nameSelectedDictionary << " contains " << countWords << " words\n";
      }
      else
      {
        out << " Errorfdafsdfsfs\n";
      }
    }
    else
    {
      out << " The contents of the dictionary " << nameSelectedDictionary << "\n";
      for (auto it = invertedDictionary.rbegin(); it != invertedDictionary.rend(); ++it) {
        out << it->second << " " << it->first << "\n";
      }
    }
  }
  else
  {
    out << " Error\n";
  }
}

bool nikiforov::ActionsOnTheDictionary::isSelectedDictionary()
{
  return nameSelectedDictionary.empty() ? false : true;
}
