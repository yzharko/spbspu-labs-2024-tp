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
    std::cout << "Доступные команды:\n"
      << "help - вывод списка доступных команд\n"
      << "create < name > - создание словаря с названием name\n"
      << "remove < name > - удаление словаря с названием name\n"
      << "clear < name > - очищение словаря с именем name\n"
      << "print < name > - вывод словаря name\n"
      << "size < name > - подсчет слов в словаре с именем name\n"
      << "list - вывод списка всех словарей\n"
      << "unite < newName > < name1 > < name2 > - объединение словарей name1 и name2 в новый словарь newName\n"
      << "add < name1 > < name2 > - добавление словаря name1 в словарь name2\n"
      << "intersection < newName > < name1 > < name2 > - пересечение словарей name1 и name2 в новый словарь newName\n"
      << "insert < name > < key > < translation > - вставка элемента в словарь name\n"
      << "find < name > < key > - поиск перевода по ключу в словаре name\n"
      << "change < name > < key > < translation > - изменение перевода элемента в словаре name\n"
      << "findLetter < name > < letter > - поиск слов по первой букве в словаре name\n"
      << "delete < name > < key > - удаление элемента из словаря name\n";
  }

  void create(const std::string &name)
  {
    if (dictionaries.count(name))
    {
      std::cout << "словарь с таким именем уже существует. Выберите другое имя\n";
    }
    else
    {
      dictionaries[name] = Dictionary();
      std::cout << "словарь " << name << " создан\n";
    }
  }

  void remove(const std::string &name)
  {
    if (dictionaries.erase(name))
    {
      std::cout << "словарь " << name << " удален\n";
    }
    else
    {
      std::cout << "словаря с таким именем не существует\n";
    }
  }

  void clear(const std::string &name)
  {
    if (dictionaries.count(name))
    {
      dictionaries[name].clear();
      std::cout << "словарь " << name << " очищен\n";
    }
    else
    {
      std::cout << "словаря с таким именем не существует\n";
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
      std::cout << "словаря с таким именем не существует\n";
    }
  }

  void size(const std::string &name)
  {
    if (dictionaries.count(name))
    {
      std::cout << "размер словаря " << name << ": " << dictionaries[name].size() << '\n';
    }
    else
    {
      std::cout << "словаря с таким именем не существует\n";
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

  void unite(const std::string &newName, const std::string &name1, const std::string &name2)
  {
    if (!dictionaries.count(name1) || !dictionaries.count(name2))
    {
      std::cout << "словаря с таким именем не существует\n";
    }
    else
    {
      Dictionary newDict = dictionaries[name1];
      newDict.insert(dictionaries[name2].begin(), dictionaries[name2].end());
      dictionaries[newName] = newDict;
      std::cout << "словарь " << newName << " создан путем объединения " << name1 << " и " << name2 << '\n';
    }
  }

  void add(const std::string &name1, const std::string &name2)
  {
    if (!dictionaries.count(name1) || !dictionaries.count(name2))
    {
      std::cout << "словаря с таким именем не существует\n";
    }
    else
    {
      dictionaries[name2].insert(dictionaries[name1].begin(), dictionaries[name1].end());
      std::cout << "словарь " << name1 << " добавлен в словарь " << name2 << '\n';
    }
  }

  void intersection(const std::string &newName, const std::string &name1, const std::string &name2)
  {
    if (!dictionaries.count(name1) || !dictionaries.count(name2))
    {
      std::cout << "словаря с таким именем не существует\n";
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
        std::cout << "словарь " << newName << " создан путем пересечения " << name1 << " и " << name2 << '\n';
    }
  }

  void insert(const std::string &name, const std::string &key, const std::string &translation)
  {
    if (!dictionaries.count(name))
    {
      std::cout << "словаря с таким именем не существует\n";
    }
    else if (dictionaries[name].count(key))
    {
      std::cout << "элемент с введенным ключом в словаре " << name;
      std::cout << " уже существует, введите другой ключ для пополнения словаря\n";
    }
    else
    {
      dictionaries[name][key] = translation;
      std::cout << "элемент " << key << " добавлен в словарь " << name << '\n';
    }
  }

  void find(const std::string &name, const std::string &key)
  {
    if (!dictionaries.count(name))
    {
      std::cout << "словаря с таким именем не существует\n";
    }
    else if (!dictionaries[name].count(key))
    {
      std::cout << "в словаре " << name << " не существует элемента с введенным ключом " << key << '\n';
    }
    else
    {
      std::cout << key << " : " << dictionaries[name][key] << '\n';
    }
  }

  void change(const std::string &name, const std::string &key, const std::string &translation)
  {
    if (!dictionaries.count(name))
    {
      std::cout << "словаря с таким именем не существует\n";
    }
    else if (!dictionaries[name].count(key))
    {
      std::cout << "в словаре " << name << " не существует элемента с введенным ключом " << key << '\n';
    }
    else
    {
      dictionaries[name][key] = translation;
      std::cout << "элемент " << key << " в словаре " << name << " изменен на " << translation << '\n';
    }
  }

  void findLetter(const std::string &name, char letter)
  {
    if (!dictionaries.count(name))
    {
      std::cout << "словаря с таким именем не существует\n";
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
      std::cout << "словаря с таким именем не существует\n";
    }
    else if (!dictionaries[name].count(key))
    {
      std::cout << "в словаре " << name << " не существует элемента с введенным ключом " << key << '\n';
    }
    else
    {
      dictionaries[name].erase(key);
      std::cout << "элемент " << key << " удален из словаря " << name << '\n';
    }
  }

}
