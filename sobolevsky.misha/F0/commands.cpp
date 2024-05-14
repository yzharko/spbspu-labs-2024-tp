#include "commands.hpp"
#include <string>
#include <limits>
#include <algorithm>
#include <functional>

void sobolevsky::getCommands(std::istream & in, std::ostream & out)
{
  if (in.get() != '\n')
  {
    throw std::exception();
  }
  std::string listOfCommands = "Система команд:\n1. commands - вывод списка доступных пользователю команд\n2. loadAndCreate < filename > - загрузка текста из файла и создание частотного словаря(название словаря в системе- это название загруженного файла) !WRONG INPUT- если пользователь ввел название файла некоректно, то выводит ошибку\n3. delete < name > - удаление частотного словаря !WRONG INPUT- если словаря с таким именем не существует, то выводит ошибку\n4. allDicts - выводит имена всех словарей\n5. compareDicts < name1 > < name2 > - сравнение двух частотных словарей по по методу косинусного сходства, через построение векторов !WRONG INPUT- если пользователь ввел название хотя бы одного файла некоректно, то выводит ошибку\n6. rename < oldName > < newName > - переименование словаря !WRONG INPUT- если словаря со старым именем не существует или новое имя уже занято, то выводит ошибку\n7. select < name > - выбор словаря для дальнейшей работы конкретно только с ним одним(без предварительного выбора словаря и запуске всех ниже представленных команд, выводит ошибку) !WRONG INPUT- если словаря с таким именем не существует, то выводит ошибку\n7.1.1. holyTrinity - выводит три самых часто встречаемых слова в словаре(без кол-ва самих слов в тексте)\n7.1.2. holyTrinity -amount - выводит три самых часто встречаемых слова в словаре(с кол-вом самих слов в тексте)\n7.2.1. printDict -(n/all) - вывод отсортированного списка определенного кол-ва слов без их частоты(n-определенное число слов, all-сразу все)\n7.2.2. printDict -(n/all) -amount - вывод отсортированного списка определенного кол-ва слов c их частотой(n-определенное число слов, all-сразу все)\n7.3. unigueWords - выводит список уникальных слов без повторений\n7.4. wordCount - выводит кол-во слов в тексте(без повторений типо)\n7.5. save < filename > - сохраняет в файл txt весь отсортированный частотный словарь !WRONG INPUT- если файла с таким именем не существует, то выводит ошибку\n";
  out << listOfCommands;
}

void sobolevsky::getLoadAndCreate(std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > > myVec, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  std::string file;
  in >> file;
  std::ifstream text(file);
  if (!text)
  {
    throw std::invalid_argument("ERROR: CANT FIND/OPEN FILE\n");
  }
  if (in.get() != '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }

  std::map< std::string, size_t > myMap;
  while (!text.eof())
  {
    if (text.fail())
    {
      text.clear();
      text.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

    std::string word;
    text >> word;
    if (myMap.find(word) == myMap.end())
    {
      myMap.emplace(word, 1);
    }
    else
    {
      myMap.find(word)->second++;
    }
  }

  std::multimap< size_t, std::string > myMultiMap;
  for (std::pair< std::string, size_t > const &pair : myMap)
  {
    myMultiMap.emplace(pair.second, pair.first);
  }
  myVec->push_back(std::pair(file, myMultiMap));
}

bool sobolevsky::isNameHere(std::pair< std::string, std::multimap< size_t, std::string > > &pair, const std::string &name)
{
  return pair.first == name;
}

void sobolevsky::getDelete(std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > > myVec, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  std::string name;
  in >> name;
  if (in.get() != '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  std::function< bool(std::pair< std::string, std::multimap< size_t, std::string > > &) > bindIsNameHere = std::bind(isNameHere,std::placeholders::_1, name);
  if (std::find_if(myVec->begin(), myVec->end(), bindIsNameHere) == myVec->end())
  {
    throw std::invalid_argument("ERROR: NO DICT WITH SUCH NAME\n");
  }
  else
  {
    myVec->erase(std::find_if(myVec->begin(), myVec->end(), bindIsNameHere));
  }
}

void sobolevsky::getAllDicts(std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > > myVec, std::istream & in, std::ostream & out)
{
  if (myVec->size() == 0)
  {
    throw std::invalid_argument("ERROR: ZERO DICTS\n");
  }

  if (in.get() != '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }

  for (std::pair< std::string, std::multimap< size_t, std::string > > &pair : *myVec)
  {
    out << pair.first << "\n";
  }
}

void sobolevsky::getRename(std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > > myVec, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  std::string oldName, newName;
  in >> oldName >> newName;
  std::function< bool(std::pair< std::string, std::multimap< size_t, std::string > > &) > bindOldName = std::bind(isNameHere,std::placeholders::_1, oldName);
  std::function< bool(std::pair< std::string, std::multimap< size_t, std::string > > &) > bindNewName = std::bind(isNameHere,std::placeholders::_1, newName);
  if(std::find_if(myVec->begin(), myVec->end(), bindOldName) != myVec->end() && std::find_if(myVec->begin(), myVec->end(), bindNewName) == myVec->end())
  {
    std::find_if(myVec->begin(), myVec->end(), bindOldName)->first = newName;
  }
  else
  {
    throw std::invalid_argument("ERROR: CANT FIND DICT WITH OLDNAME OR DICT WITH NEWNAME EXIST\n");
  }
  if (in.get() != '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
}

void sobolevsky::dictOutput(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::ostream & out, size_t n, bool mode)
{
  size_t i = 0;
  for (std::multimap< size_t, std::string >::reverse_iterator pair = myPair.second.rbegin(); pair != myPair.second.rend(); ++pair)
    {
      i++;
      out << pair->second;
      if (mode)
      {
        out << " " << pair->first;
      }
      out << "\n";
      if (i == n)
      {
        break;
      }
    }
}

void sobolevsky::holyTrinity(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    dictOutput(myPair, out, 3, false);
  }
  else
  {
    std::string mode;
    in >> mode;
    if (mode == "-amount")
    {
      dictOutput(myPair, out, 3, true);
    }
    if (in.get() != '\n')
    {
      throw std::invalid_argument("ERROR: INVALID COMMAND\n");
    }
  }
}

void sobolevsky::printDict(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  char mode;
  in >> mode;
  if (mode == '-')
  {
    std::string mode2;
    in >> mode2;
    size_t numOfWords;
    if (mode2 == "all")
    {
      numOfWords = myPair.second.size();
    }
    else
    {
      numOfWords = std::stoull(mode2);
      if (numOfWords < 1 || numOfWords > myPair.second.size())
      {
        throw std::invalid_argument("ERROR: WRONG NUMBER\n");
      }
    }
    if (in.get() == '\n')
    {
      dictOutput(myPair, out, numOfWords, false);
    }
    else
    {
      std::string mode;
      in >> mode;
      if (mode == "-amount")
      {
        dictOutput(myPair, out, numOfWords, true);
      }
      if (in.get() != '\n')
      {
        throw std::invalid_argument("ERROR: INVALID COMMAND\n");
      }
    }
  }
}

void sobolevsky::uniqeWords(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::istream & in, std::ostream & out)
{
  if (in.get() != '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  for (std::pair< size_t, std::string > const &pair : myPair.second)
  {
    if (pair.first > 1)
    {
      break;
    }
    out << pair.second << "\n";
  }
}

void sobolevsky::wordCount(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::istream & in, std::ostream & out)
{
  if (in.get() != '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  out << myPair.second.size() << "\n";
}

void sobolevsky::save(std::pair< std::string, std::multimap< size_t, std::string > > &myPair, std::istream &in)
{
  if (in.get() == '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  std::string fileName;
  in >> fileName;
  std::ofstream file(fileName);
  if (!file)
  {
    throw std::invalid_argument("ERROR: CANT FIND/OPEN FILE\n");
  }
  if (in.get() != '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  dictOutput(myPair, file, myPair.second.size(), true);
}

void sobolevsky::getSelect(std::shared_ptr< std::vector< std::pair< std::string, std::multimap< size_t, std::string > > > > myVec, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  std::string name;
  in >> name;
  std::function< bool(std::pair< std::string, std::multimap< size_t, std::string > > &) > bindIsNameHere = std::bind(isNameHere,std::placeholders::_1, name);
  if (std::find_if(myVec->begin(), myVec->end(), bindIsNameHere) == myVec->end())
  {
    throw std::invalid_argument("ERROR: NO DICT WITH SUCH NAME\n");
  }
  std::pair< std::string, std::multimap< size_t, std::string > > currPair(*std::find_if(myVec->begin(), myVec->end(), bindIsNameHere));
  std::map< std::string, std::function< void(std::pair< std::string, std::multimap< size_t, std::string > > &, std::istream &, std::ostream &) > > commands;
  commands["holyTrinity"] = holyTrinity;
  commands["printDict"] = printDict;
  commands["uniqueWords"] = uniqeWords;
  commands["wordCount"] = wordCount;
  commands["save"] = std::bind(save, std::placeholders::_1, std::placeholders::_2);
  std::string cmd;
  while (in >> cmd)
  {
    try
    {
      commands.at(cmd)(currPair, in, out);
    }
    catch(const std::out_of_range & e)
    {
      sobolevsky::error(out, "ERROR: INVALID COMMAND\n");
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch(const std::invalid_argument & e)
    {
      sobolevsky::error(out, e.what());
      in.clear();
      in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}

void sobolevsky::error(std::ostream & out, const std::string &text)
{
  out << text;
}
