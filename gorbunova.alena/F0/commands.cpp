#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include "commands.hpp"

namespace gorbunova
{

  std::map< std::string, Dictionary > dictionaries;

  void help()
  {
    std::cout << "Available commands:\n"
      << "help - display the list of available commands\n"
      << "create <name> - create a dictionary with the name <name>\n"
      << "remove <name> - delete the dictionary with the name <name>\n"
      << "clear <name> - clear the dictionary with the name <name>\n"
      << "print <name> - display the contents of the dictionary <name>\n"
      << "size <name> - count the number of words in the dictionary <name>\n"
      << "list - display the list of all dictionaries\n"
      << "unite <newName> <name1> <name2> - merge dictionaries <name1> and <name2>"
      << "into a new dictionary <newName>\n"
      << "add <name1> <name2> - add dictionary <name1> to dictionary <name2>\n"
      << "intersection <newName> <name1> <name2> - intersect dictionaries <name1> and <name2>"
      << "into a new dictionary <newName>\n"
      << "insert <name> <key> <translation> - insert an element into dictionary <name>\n"
      << "find <name> <key> - find the translation of the key in dictionary <name>\n"
      << "change <name> <key> <translation> - modify the translation of an element in dictionary <name>\n"
      << "findLetter <name> <letter> - find words by the first letter in dictionary <name>\n"
      << "delete <name> <key> - remove the element with the key from dictionary <name>\n"
      << "exit - exit the program\n";
  }

  void create(const std::string &name)
  {
    if (dictionaries.count(name))
    {
      std::cout << "A dictionary with this name already exists. Choose another name\n";
    }
    else
    {
      dictionaries[name] = Dictionary();
      std::cout << "Dictionary " << name << " created\n";
    }
  }

  void remove(const std::string &name)
  {
    if (dictionaries.erase(name))
    {
      std::cout << "Dictionary " << name << " removed\n";
    }
    else
    {
      std::cout << "No dictionary with this name exists\n";
    }
  }

  void clear(const std::string &name)
  {
    if (dictionaries.count(name))
    {
      dictionaries[name].clear();
      std::cout << "Dictionary " << name << " cleared\n";
    }
    else
    {
      std::cout << "No dictionary with this name exists\n";
    }
  }

  void print(const std::string &name)
  {
    if (dictionaries.count(name))
    {
      std::for_each(dictionaries[name].begin(), dictionaries[name].end(),
        [](const auto &pair)
        {
          std::cout << pair.first << " : " << pair.second << '\n';
        });
    }
    else
    {
      std::cout << "No dictionary with this name exists\n";
    }
  }

  void size(const std::string &name)
  {
    if (dictionaries.count(name))
    {
      std::cout << "Size of dictionary " << name
        << ": " << dictionaries[name].size() << '\n';
    }
    else
    {
      std::cout << "No dictionary with this name exists\n";
    }
  }

  void list()
  {
    std::for_each(dictionaries.begin(), dictionaries.end(),
      [](const auto &pair)
      {
        std::cout << pair.first << '\n';
      });
  }

  void unite(const std::string &newName,
             const std::string &name1, const std::string &name2)
  {
    if (!dictionaries.count(name1) || !dictionaries.count(name2))
    {
      std::cout << "No dictionary with this name exists\n";
    }
    else
    {
      Dictionary newDict = dictionaries[name1];
      newDict.insert(dictionaries[name2].begin(), dictionaries[name2].end());
      dictionaries[newName] = newDict;
      std::cout << "Dictionary " << newName
        << " created by merging " << name1 << " and " << name2 << '\n';
    }
  }

  void add(const std::string &name1, const std::string &name2)
  {
    if (!dictionaries.count(name1) || !dictionaries.count(name2))
    {
      std::cout << "No dictionary with this name exists\n";
    }
    else
    {
      dictionaries[name2].insert(dictionaries[name1].begin(),
        dictionaries[name1].end());
      std::cout << "Dictionary " << name1 << " added to dictionary " << name2 << '\n';
    }
  }

  void intersection(const std::string &newName,
                    const std::string &name1, const std::string &name2)
  {
    if (!dictionaries.count(name1) || !dictionaries.count(name2))
    {
      std::cout << "No dictionary with this name exists\n";
    }
    else
    {
      Dictionary newDict;
      std::copy_if(dictionaries[name1].begin(), dictionaries[name1].end(),
        std::inserter(newDict, newDict.end()),
        [&name2](const auto &pair)
        {
          return dictionaries[name2].count(pair.first);
        });
        dictionaries[newName] = newDict;
        std::cout << "Dictionary " << newName
          << " created by intersecting " << name1 << " and " << name2 << '\n';
    }
  }

  void insert(const std::string &name, const std::string &key,
              const std::string &translation)
  {
    if (!dictionaries.count(name))
    {
      std::cout << "No dictionary with this name exists\n";
    }
    else if (dictionaries[name].count(key))
    {
      std::cout << "An element with the entered key already exists in dictionary " << name
        << ", enter another key to add to the dictionary\n";
    }
    else
    {
      dictionaries[name][key] = translation;
      std::cout << "Element " << key << " added to dictionary " << name << '\n';
    }
  }

  void find(const std::string &name, const std::string &key)
  {
    if (!dictionaries.count(name))
    {
      std::cout << "No dictionary with this name exists\n";
    }
    else if (!dictionaries[name].count(key))
    {
      std::cout << "There is no element with the entered key in dictionary " << name << '\n';
    }
    else
    {
      std::cout << key << " : " << dictionaries[name][key] << '\n';
    }
  }

  void change(const std::string &name, const std::string &key,
              const std::string &translation)
  {
    if (!dictionaries.count(name))
    {
      std::cout << "No dictionary with this name exists\n";
    }
    else if (!dictionaries[name].count(key))
    {
      std::cout << "There is no element with the entered key in dictionary " << name << '\n';
    }
    else
    {
      dictionaries[name][key] = translation;
      std::cout << "Element " << key << " in dictionary "
        << name << " changed to " << translation << '\n';
    }
  }

  void findLetter(const std::string &name, char letter)
  {
    if (!dictionaries.count(name))
    {
      std::cout << "No dictionary with this name exists\n";
    }
    else
    {
      std::for_each(dictionaries[name].begin(), dictionaries[name].end(),
        [letter](const auto &pair)
        {
          if (pair.first[0] == letter)
          {
            std::cout << pair.first << " : " << pair.second << '\n';
          }
        });
    }
  }

  void deleteElem(const std::string &name, const std::string &key)
  {
    if (!dictionaries.count(name))
    {
      std::cout << "No dictionary with this name exists\n";
    }
    else if (!dictionaries[name].count(key))
    {
      std::cout << "There is no element with the entered key in dictionary " << name << '\n';
    }
    else
    {
      dictionaries[name].erase(key);
      std::cout << "Element " << key << " removed from dictionary "
        << name << '\n';
    }
  }

}
