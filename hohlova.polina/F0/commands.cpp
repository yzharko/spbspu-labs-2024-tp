#include "commands.hpp"
#include <fstream>
#include <iterator>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>

namespace hohlova
{
  void help(std::ostream& stream)
  {
    stream << "List of available commands:\n";
    stream << "1. help - displays information about available commands(active now)\n";
    stream << "2. create < filename > - opening the filename file, if it does not exist,\n";
    stream << "then creating it and forming a dictionary with the same name from its data\n";
    stream << "3. edit < name > < word > < new frequency > - edit dictionary elements,\n";
    stream << "their names and frequencies\n";
    stream << "4. insert < name > < word > < frequency > - inserting a word-frequency pair\n";
    stream << "5. remove < name > < word > - deleting an item(s) from the dictionary\n";
    stream << "by word / frequency / word and frequency\n";
    stream << "6. rename < oldname > < newname > - renaming the dictionary from oldname to newname\n";
    stream << "7. find < name > < word > - output of element(s) by word\n";
    stream << "dictionary elements according to the specified sorting conditions\n";
    stream << "8. view - the output of the names of existing dictionaries\n";
    stream << "9. size < name > - print the size of the dictionary\n";
  }

  void create(DictOfDictionary& dictOfdict, std::istream& is)
  {
    std::string fileName;
    is >> fileName;
    if (fileName.empty())
    {
      printError("empty name");
      return;
    }

    std::ifstream file;
    file.open(fileName);

    if (!file.is_open())
    {
      printError("file not open");
      return;
    }
    Dictionary dictionary;
    std::string nameOfDict = fileName.substr(fileName.find_last_of("/") + 1, fileName.find(".txt"));
    while (!file.eof())
    {
      std::pair< std::string, std::string > pair;
      file >> pair.first;
      file >> pair.second;
      dictionary.emplace(pair);
    }
    dictOfdict.emplace(nameOfDict, dictionary);
    file.close();
  }

  void size(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out)
  {
    std::string name;
    is >> name;
    if (name.empty())
    {
      printError("Empty name of dictionary");
      return;
    }

    auto currDictionary = dictOfdict.begin();
    while (currDictionary != dictOfdict.end())
    {
      if ((*currDictionary).first == name)
      {
        break;
      }
      currDictionary++;
    }

    if (currDictionary != dictOfdict.end())
    {
      int count = 0;
      for (auto& it : (*currDictionary).second)
      {
        count++;
      }
      out << "The size of dictionary = " << count - 1 << '\n';
    }
    else
    {
      printError("This name dont contains in dictionary");
    }
  }

  void view(DictOfDictionary& dictOfdict, std::ostream& out)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (dictOfdict.empty())
    {
      out << "List of dictionaries is empty\n";
      return;
    }

    auto bg = dictOfdict.begin();
    while (bg != dictOfdict.end())
    {
      auto bgDict = (*bg).second.begin();
      out << "Dictionary: " << (*bg).first << '\n';
      size_t number = 0;
      while (bgDict != (*bg).second.end())
      {
        out << number++ << ". " << (*bgDict).first << " " << " : " << (*bgDict).second << '\n';
        bgDict++;
      }
      bg++;
    }
    out << '\n' << '\n';
  }

  void find(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string nameOfDict, word;
    is >> nameOfDict >> word;
    if (nameOfDict.empty() || word.empty())
    {
      printError("The name of dictionary is empty");
    }
    auto it = dictOfdict.find(nameOfDict);
    if (it != dictOfdict.end())
    {
      auto crrWord = (*it).second.find(word);
      out << "The word meets in dictionary : " << (*crrWord).second << '\n';
    }
  }

  void rename(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string currName;
    std::string newName;
    is >> currName >> newName;
    if (currName.empty() || newName.empty())
    {
      printError("The new or current name is empty");
      return;
    }

    auto currDictionary = dictOfdict.begin();

    while (currDictionary != dictOfdict.end())
    {
      if ((*currDictionary).first == currName)
      {
        break;
      }
      currDictionary++;
    }

    if (currDictionary != dictOfdict.end())
    {
      dictOfdict.emplace(newName, (*currDictionary).second);
      dictOfdict.erase(currName);
      out << "The dictionary rename success" << '\n';
    }
    else
    {
      printError("This name -" + currName + "contains in dictionary ");
    }
  }

  void edit(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string nameDict;
    std::string word;

    is >> nameDict >> word;

    if (nameDict.empty() || word.empty())
    {
      printError("The name or word is empty");
      return;
    }

    std::string translate;
    is >> translate;
    if (translate.empty())
    {
      printError("Invalid translate");
      return;
    }

    auto iter = dictOfdict.find(nameDict);
    auto iterWord = (*iter).second.find(word);
    std::pair< std::string, std::string > p = *iterWord;
    p.second = translate;
    (*iter).second.erase(p.first);
    (*iter).second.insert(p);
    out << "The edit complete" << '\n';
  }

  void insert(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string nameOfDict;
    is >> nameOfDict;
    if (nameOfDict.empty())
    {
      printError("Empty name of dictionary");
      return;
    }

    auto it = dictOfdict.find(nameOfDict);
    if (it != dictOfdict.end())
    {
      std::string word;
      is >> word;
      if (word.empty())
      {
        printError("Empty word");
        return;
      }

      auto found = std::find_if(it->second.begin(), it->second.end(),
        [&word](const std::pair<std::string, std::string>& pair)
      {
        return pair.first == word;
      });

      if (found != it->second.end())
      {
        printError("The word already exists in the dictionary");
        return;
      }

      std::string translate;
      is >> translate;
      if (translate.empty())
      {
        printError("Empty translation");
        return;
      }
      it->second.insert(std::make_pair(word, translate));
      out << "The word was successfully added" << '\n';
    }
    else
    {
      printError("Dictionary not found");
    }
  }

  void remove(DictOfDictionary& dictOfdict, std::istream& is, std::ostream& out)
  {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::string nameOfDict;
    is >> nameOfDict;
    if (nameOfDict.empty())
    {
      printError("Empty name of dictionary");
      return;
    }
    auto it = dictOfdict.find(nameOfDict);
    if (it != dictOfdict.end())
    {
      std::string word;
      is >> word;
      if (word.empty())
      {
        printError("Empty name");
        return;
      }
      auto rWord = (*it).second.find(word);
      if ((*it).second.find(word) != (*it).second.end())
      {
        (*it).second.erase(word);
        out << "The word successful remove" << '\n';
      }
      else
      {
        printError("The word not contains in dictionary");
      }
    }
    else
    {
      printError("Invalid name of dictionary");
    }
  }

  void printError(const std::string& err)
  {
    std::cout << err << '\n';
  }
}
