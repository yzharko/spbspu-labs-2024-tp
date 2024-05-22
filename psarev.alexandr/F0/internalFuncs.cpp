#include "internalFuncs.hpp"
#include <cctype>
#include <vector>

std::ostream& psarev::outError(std::ostream& out, const std::string& errText)
{
  out << errText << '\n';
  return out;
}

storage_t psarev::readStorage(std::istream& in)
{
  storage_t resStorage;
  std::string word = "";
  while (!in.eof())
  {
    if (in >> word)
    {
      cleanUpWord(word);
      if (checkLiter(word))
      {
        std::string spType = getSpType(word);
        auto scanFor = resStorage.find(spType);
        if (scanFor == resStorage.end())
        {
          std::vector< std::string > words;
          words.push_back(word);
          resStorage.emplace(spType, word);
        }
        else
        {
          (resStorage.at(spType)).push_back(word);
        }
      }
    }
  }
  return resStorage;
}

void psarev::cleanUpWord(std::string& word)
{
  std::string puncts = ".,:;?!";
  char curPunct = word.back();
  for (char p : puncts )
  {
    if (word.back() == p )
    {
      word.pop_back();
    }
  }

  std::string extras = "(){}[]<>'";
  for (char ex : extras)
  {
    if (word.back() == ex)
    {
      word.pop_back();
    }
    if (word.front() == ex)
    {
      word.erase(word.begin());
    }
  }
}

bool psarev::checkLiter(const std::string& word)
{
  for (char c : word)
  {
    if (!isalpha(c))
    {
      return false;
    }
  }
  return true;
}

std::string psarev::getSpType(std::string& word)
{
  std::string resType = "";

  storage_t rusEnds;

  rusEnds["noun"] = { "а", "ев", "ов", "ье", "иями", "ями", "ами", "еи", "ии", "и", "ией", "ей", "ой" };
  std::vector< std::string > nSec = { "ем", "ам", "ом", "о", "у", "ах", "иях", "ях", "ы", "ь", "ию", "ью" };
  std::vector< std::string > nThi = { "я", "ок", "мва", "яна", "ровать", "ег", "ги", "га", "сть", "сти" };
  std::vector< std::string > nFou = { "ий", "й", "иям", "ю", "ия", "ья", "ям", "ием" };
  rusEnds["noun"].insert(rusEnds["noun"].end(), std::make_move_iterator(nSec.begin()), std::make_move_iterator(nSec.end()));
  rusEnds["noun"].insert(rusEnds["noun"].end(), std::make_move_iterator(nThi.begin()), std::make_move_iterator(nThi.end()));
  rusEnds["noun"].insert(rusEnds["noun"].end(), std::make_move_iterator(nFou.begin()), std::make_move_iterator(nFou.end()));

  rusEnds["verb"] = { "ила", "ыла", "ена", "ейте", "уйте", "ите", "или", "ыли", "ей", "уй", "ил", "ыл" };
  std::vector< std::string > vSec = { "ено", "ят", "ует", "уют", "ит", "ыт", "ены", "ить", "ыть", "ишь", "ую" };
  std::vector< std::string > vThi = { "на", "ете", "йте", "ли", "й", "л", "ем", "н", "ло", "ет", "ют", "ны"};
  std::vector< std::string > vFou = { "им", "ым", "ен", "ило", "ыло", "ть", "ешь", "нно", "ю", "ла" };
  rusEnds["verb"].insert(rusEnds["verb"].end(), std::make_move_iterator(vSec.begin()), std::make_move_iterator(vSec.end()));
  rusEnds["verb"].insert(rusEnds["verb"].end(), std::make_move_iterator(vThi.begin()), std::make_move_iterator(vThi.end()));
  rusEnds["verb"].insert(rusEnds["verb"].end(), std::make_move_iterator(vFou.begin()), std::make_move_iterator(vFou.end()));

  rusEnds["adjective"] = { "ее", "ие", "ые", "ое", "ими", "ыми", "ей", "ий", "ый", "ой", "ем", "им", "ым", "ом" };
  std::vector< std::string > aSec = { "его", "ого", "ему", "ому", "их", "ых", "ую", "юю", "ая", "яя", "ою", "ею" };
  rusEnds["adjective"].insert(rusEnds["adjective"].end(), std::make_move_iterator(aSec.begin()), std::make_move_iterator(aSec.end()));

  rusEnds["adverb"] = { "чно", "еко", "око", "имо", "мно", "жно", "жко", "ело", "тно", "льно", "здо", "зко", "шо", "хо", "но" };

  rusEnds["numeric"] = { "много", "еро", "вое", "рое", "еро", "сти", "двух", "рех", "еми", "яти", "ьми", "ати" };
  std::vector< std::string > nSec = { "дного", "сот", "сто", "ста", "тысяча", "тысячи", "две", "три", "одна" };
  std::vector< std::string > nThi = { "мью", "тью", "одним", "умя", "тью", "мя", "тью" };
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), std::make_move_iterator(nSec.begin()), std::make_move_iterator(nSec.end()));
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), std::make_move_iterator(nThi.begin()), std::make_move_iterator(nThi.end()));

  rusEnds["conjuct"] = { "более", "менее", "очень", "крайне", "когда", "однако", "если", "чтоб", "хотя", "как", };
  std::vector< std::string > cSec = { "зато", "что", "или", "потом", "это", "того", "тоже", "словно", "ежели" };
  std::vector< std::string > cThi = { "и", "да", "кабы", "коли", "ничем", "чем", "также", "так" };
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), std::make_move_iterator(cSec.begin()), std::make_move_iterator(cSec.end()));
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), std::make_move_iterator(cThi.begin()), std::make_move_iterator(cThi.end()));

  rusEnds["prepos"] = { "в", "на", "по", "из", "за", "у", "от", "с", "об", "к", "перед", "между", "под", "около" };
  std::vector< std::string > pSec = { "из-под", "для", "про", "до", "о", "вокруг", "при", "возле", "из-за", "без" };
  rusEnds["prepos"].insert(rusEnds["prepos"].end(), std::make_move_iterator(pSec.begin()), std::make_move_iterator(pSec.end()));

  for (auto iter = rusEnds["prepos"].begin(); iter != rusEnds["prepos"].end(); ++iter)
  {
    if (word == *iter)
    {
      return "Prepos";
    }
  }
  for (auto iter = rusEnds["conjuct"].begin(); iter != rusEnds["conjuct"].end(); ++iter)
  {
    if (word == *iter)
    {
      return "Conjuct";
    }
  }
  for (auto iter = rusEnds["numeric"].begin(); iter != rusEnds["numeric"].end(); ++iter)
  {
    if (word == *iter)
    {
      return "Numeric";
    }
  }

  std::vector< std::string > spTypes = { "noun", "verb", "adjective", "adverb", "numeric" };
  for (auto iter = spTypes.begin(); iter != spTypes.end(); ++iter)
  {
    for (size_t i; i <= 6; i++)
    {
      if (checkType(word, i, rusEnds[*iter]))
      {
        return *iter;
      }
    }
  }

  return resType;
}

bool psarev::checkType(std::string& word, size_t& endSize, std::vector< std::string >& ends)
{
  std::string endL = word.substr(word.length() - endSize);
  for (auto iter = ends.begin(); iter != ends.end(); ++iter)
  {
    if (endL == *iter)
    {
      return true;
    }
  }
  return false;
}

void psarev::outDepot(std::string dest, std::ofstream& out, std::map< std::string, storage_t >& depot)
{
  for (auto storage : depot)
  {
    out.open(dest + "\\" + storage.first + ".txt");
    if (out.is_open())
    {
      for (auto iter : storage.second)
      {
        size_t len = (iter.second).size();
        for (size_t i = 0; i < len; i++)
        {
          out << iter.second[i] << " ";
        }
      }
    }
    out.close();
  }
}
