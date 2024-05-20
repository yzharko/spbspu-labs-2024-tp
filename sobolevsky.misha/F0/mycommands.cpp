#include "mycommands.hpp"
#include <string>
#include <limits>
#include <algorithm>
#include <functional>
#include <cmath>
#include <cctype>

using mypair = std::pair< std::string, std::multimap< size_t, std::string > >;

void sobolevsky::getCommands(std::istream & in, std::ostream & out)
{
  if (in.get() != '\n')
  {
    throw std::exception();
  }
  out << "1.commands - output of the list of commands available to the user\n";
  out << "2.loadAndCreate < filename > - loading text from a file and creating a frequency dictionary\n";
  out << "3.delete < name > - frequency dictionary deletion\n";
  out << "4.allDicts - displays the names of all dictionaries\n";
  out << "5.compareDicts < name1 > < name2 > - comparison of two frequency dictionaries\n";
  out << "6.rename < oldName > < newName > - dictionary renaming\n";
  out << "7.select < name > - selecting a vocabulary for further work specifically with that vocabulary alone\n";
  out << "7.1.1.holyTrinity - outputs the three most frequently occurring words in the dictionary\n";
  out << "7.1.2.holyTrinity -amount - outputs the three most frequently occurring words in the dictionary\n";
  out << "7.2.1.printDict -(n/all) - output a sorted list of a certain number of words without their frequency\n";
  out << "7.2.2.printDict -(n/all) -amount - output a sorted list of a certain number of words with their frequency\n";
  out << "7.3.unigueWords - outputs a list of unique words with no repetitions\n";
  out << "7.4.wordCount - outputs the number of words in the text\n";
  out << "7.5.save < filename > - saves the entire sorted frequency dictionary to a file\n";
}

char sobolevsky::charCheck(char in)
{
  if (in <= 'Z' && in >= 'A')
  {
    return in - ('Z' - 'z');
  }
  else if (in <= 'z' && in >= 'a')
  {
    return in;
  }
  else
  {
    return 0;
  }
}

void sobolevsky::getLoadAndCreate(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in)
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
    std::transform(word.begin(), word.end(), word.begin(), charCheck);
    if (word[0] > 'z' || word[0] < 'a')
    {
      continue;
    }
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
  myVec->push_back(std::pair< std::string, std::multimap<size_t, std::string> >(file, myMultiMap));
}

bool sobolevsky::isNameHere(mypair &pair,
const std::string &name)
{
  return pair.first == name;
}

void sobolevsky::getDelete(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in)
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
  std::function< bool(mypair &) > bindIsNameHere
  = std::bind(isNameHere,std::placeholders::_1, name);
  if (std::find_if(myVec->begin(), myVec->end(), bindIsNameHere) == myVec->end())
  {
    throw std::invalid_argument("ERROR: NO DICT WITH SUCH NAME\n");
  }
  else
  {
    myVec->erase(std::find_if(myVec->begin(), myVec->end(), bindIsNameHere));
  }
}

void sobolevsky::getAllDicts(std::shared_ptr< std::vector< mypair > > myVec,std::istream & in, std::ostream & out)
{
  if (myVec->size() == 0)
  {
    throw std::invalid_argument("ERROR: ZERO DICTS\n");
  }

  if (in.get() != '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }

  for (mypair &pair : *myVec)
  {
    out << pair.first << "\n";
  }
}

void sobolevsky::getRename(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in)
{
  if (in.get() == '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  std::string oldName, newName;
  in >> oldName >> newName;
  std::function< bool(mypair &) > bindOldName = std::bind(isNameHere, std::placeholders::_1, oldName);
  std::function< bool(mypair &) > bindNewName = std::bind(isNameHere, std::placeholders::_1, newName);
  if(std::find_if(myVec->begin(), myVec->end(), bindOldName) != myVec->end() &&
  std::find_if(myVec->begin(), myVec->end(), bindNewName) == myVec->end())
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

void sobolevsky::getCompareDicts(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  if (myVec->size() < 2)
  {
    throw std::invalid_argument("ERROR: YOU DONT HAVE ENOUGH DICTS\n");
  }
  std::string name1, name2;
  in >> name1 >> name2;
  std::function< bool(mypair &) > bindName1 = std::bind(isNameHere, std::placeholders::_1, name1);
  std::function< bool(mypair &) > bindName2 = std::bind(isNameHere, std::placeholders::_1, name2);
  if(std::find_if(myVec->begin(), myVec->end(), bindName1) != myVec->end() &&
  std::find_if(myVec->begin(), myVec->end(), bindName2) != myVec->end())
  {
    mypair pair1(*std::find_if(myVec->begin(), myVec->end(), bindName1));
    mypair pair2(*std::find_if(myVec->begin(), myVec->end(), bindName2));
    std::map< std::string, size_t > allwords;
    for (std::pair< size_t, std::string > const &pair : pair1.second)
    {
      allwords.emplace(pair.second, 0);
    }
    for (std::pair< size_t, std::string > const &pair : pair2.second)
    {
      allwords.emplace(pair.second, 0);
    }
    std::map< std::string, size_t > vec1(allwords);
    std::map< std::string, size_t > vec2(allwords);
    for (std::pair< size_t, std::string > const &pair : pair1.second)
    {
      vec1.find(pair.second)->second++;
    }
    for (std::pair< size_t, std::string > const &pair : pair2.second)
    {
      vec2.find(pair.second)->second++;
    }
    size_t vecProizv = 0;
    size_t dlinaVec1 = 0;
    size_t dlinaVec2 = 0;
    for (std::pair< std::string, size_t > const &pair : allwords)
    {
      vecProizv += (vec1.at(pair.first) * vec2.at(pair.first));
      dlinaVec1 += vec1.at(pair.first) * vec1.at(pair.first);
      dlinaVec2 += vec2.at(pair.first) * vec2.at(pair.first);
    }
    out << "similarity coefficient of two dictionaries: " << vecProizv/(std::sqrt(dlinaVec1) * std::sqrt(dlinaVec2)) << "\n";
  }
  else
  {
    throw std::invalid_argument("ERROR: CANT FIND DICTs WITH SUCH NAMES\n");
  }
  if (in.get() != '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
}


void sobolevsky::dictOutput(mypair &myPair, std::ostream & out, size_t n, bool mode)
{
  size_t i = 0;
  for (std::multimap< size_t, std::string >::reverse_iterator pair = myPair.second.rbegin();
  pair != myPair.second.rend(); ++pair)
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

void sobolevsky::holyTrinity(mypair &myPair, std::istream & in, std::ostream & out)
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

void sobolevsky::printDict(mypair &myPair, std::istream & in, std::ostream & out)
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

void sobolevsky::uniqeWords(mypair &myPair, std::istream & in, std::ostream & out)
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

void sobolevsky::wordCount(mypair &myPair, std::istream & in, std::ostream & out)
{
  if (in.get() != '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  out << myPair.second.size() << "\n";
}

void sobolevsky::save(mypair &myPair, std::istream &in)
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

void sobolevsky::getSelect(std::shared_ptr< std::vector< mypair > > myVec, std::istream & in, std::ostream & out)
{
  if (in.get() == '\n')
  {
    throw std::invalid_argument("ERROR: INVALID COMMAND\n");
  }
  std::string name;
  in >> name;
  std::function< bool(mypair &) > bindIsNameHere = std::bind(isNameHere, std::placeholders::_1, name);
  if (std::find_if(myVec->begin(), myVec->end(), bindIsNameHere) == myVec->end())
  {
    throw std::invalid_argument("ERROR: NO DICT WITH SUCH NAME\n");
  }
  mypair currPair(*std::find_if(myVec->begin(), myVec->end(), bindIsNameHere));
  std::map< std::string, std::function< void(mypair &, std::istream &, std::ostream &) > > commands;
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
