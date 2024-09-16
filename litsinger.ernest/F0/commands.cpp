#include "commands.hpp"
#include <fstream>

void litsinger::printCommands(std::ostream& out)
{
  out << " 1. help - выводит все доступные команды\n";
  out << " 2. create - создание словаря с именем name\n";
  out << " 3. add_word <word, name> - добавление слова в словарь с именем name\n";
  out << " 4. delete_word <word, name> - удаление слова из словаря с именем name\n";
  out << " 5. reset - очищает весь словарь name полностью\n";
  out << " 6. print - вывод всего словаря name в алфавитном порядке\n";
  out << " 7. add_line <word, name, line> - в случае, если слово уже есть в словаре c названием name, добавить номера строк, в которых это слово присутствует, если она не равна последнему лежащему значению\n";
  out << " 8. get_print <name, line> - вывод всех слов из словаря name, содержащихся на строке line\n";
  out << " 9. get_intersection <new_name, name> - создание словаря new_name со словами из словаря name\n";
  out << " 10. search_letter <letter, name> вывод слов, которые начинаются на букву letter в словаре name\n";
}

void litsinger::creatDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name = "";
  in >> name;
  std::map< std::string, std::vector< size_t > > dictionary;
  mapDictionaries.emplace(name, dictionary);
}

void litsinger::addWord(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string word = "";
  std::string name = "";

  in >> word >> name;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    auto wordInDict = dictIter->second.find(word);
    if (wordInDict == dictIter->second.end())
    {
      dictIter->second.emplace(word, 0);
      out << " Слово '" << word << "' успешно добавлено в словарь '" << name << "'\n";
    }
    else
    {
      out << " Слово '" << word << "' уже существует в словаре '" << name << "'\n";
    }
  }
  else
  {
    out << " Словаря с названием '" << name << "' не существует" << "\n";
  }
}

void litsinger::deleteWord(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string word = "";
  std::string name = "";

  in >> word >> name;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    if (dictIter->second.erase(word))
    {
      out << " Слово '" << word << "' успешно удалено" << "\n";
    }
    else
    {
      out << " Слова '" << word << "' не существует" << "\n";
    }
  }
  else
  {
    out << " Словаря с названием '" << name << "' не существует" << "\n";
  }
}

void litsinger::resetDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name = "";

  in >> name;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    dictIter->second.clear();
    out << " Словарь '" << name << "' успешно очищен" << "\n";
  }
  else
  {
    out << " Словаря с названием '" << name << "' не найден" << "\n";
  }
}

void litsinger::printDict(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name = "";

  in >> name;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    size_t count = 0;
    bool firstLine = false;
    for (auto it = dictIter->second.begin(); it != dictIter->second.end(); ++it) {
      out << ++count << ". " << it->first << " {";
      for (auto iter = it->second.begin(); iter != it->second.end(); ++iter)
      {
        if (firstLine)
        {
          out << ",";
        }
        else
        {
          firstLine = true;
        }
        out << *iter;
      }
      firstLine = false;
      out << "}\n";
    }
  }
  else
  {
    out << " Словаря с названием '" << name << "' не найден" << "\n";
  }
}

void litsinger::addLine(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string word = "";
  std::string name = "";
  std::size_t line = 0;

  in >> word >> name >> line;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    auto wordInDict = dictIter->second.find(word);
    if (wordInDict != dictIter->second.end())
    {
      auto it = wordInDict->second.begin();
      for (it; it != wordInDict->second.end(); ++it)
      {
        if (*it == line)
        {
          break;
        }
      }
      if (it == wordInDict->second.end())
      {
        wordInDict->second.push_back(line);
        out << " Номер строки успешно добавлен к слову '" << word << "'\n";
      }
      else
      {
        out << " Данный номер строки уже существует в слове '" << word << "'\n";
      }
    }
    else
    {
      out << " Слова '" << word << "' не существует в словаре '" << name << "'\n";
    }
  }
  else
  {
    out << " Словаря с названием '" << name << "' не существует" << "\n";
  }
}

void litsinger::getPrint(mapDictionaries_t& mapDictionaries, std::istream& in, std::ostream& out)
{
  std::string name = "";
  std::size_t line = 0;
  std::map< std::string, size_t > listOfWords;

  in >> name >> line;

  auto dictIter = mapDictionaries.find(name);
  if (dictIter != mapDictionaries.end())
  {
    for (auto iterWords = dictIter->second.begin(); iterWords != dictIter->second.end(); ++iterWords)
    {
      for (auto iterLines = iterWords->second.begin(); iterLines != iterWords->second.end(); ++iterLines)
      {
        if (*iterLines == line)
        {
          listOfWords.emplace(iterWords->first, 0);
        }
      }
    }
    size_t count = 0;
    for (auto it = listOfWords.begin(); it != listOfWords.end(); ++it)
    {
      out << ++count << ". " << it->first << "\n";
    }
  }
  else
  {
    out << " Словаря с названием '" << name << "' не существует" << "\n";
  }
}
