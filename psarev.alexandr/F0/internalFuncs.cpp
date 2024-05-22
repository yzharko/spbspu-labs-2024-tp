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
  rusEnds["noun"] = { "а", "ев", "ов", "ье", "иями", "ями", "ами", "еи", "ии", "и", "ией", "ей", "ой", "ий",
    "й", "иям", "ям", "ием", "ем", "ам", "ом", "о", "у", "ах", "иях", "ях", "ы", "ь", "ию", "ью", "ю", "ия", "ья",
    "я", "ок", "мва", "яна", "ровать", "ег", "ги", "га", "сть", "сти" };
  rusEnds["verb"] = { "ила", "ыла", "ена", "ейте", "уйте", "ите", "или", "ыли", "ей", "уй", "ил", "ыл", "им",
    "ым", "ен", "ило", "ыло", "ено", "ят", "ует", "уют", "ит", "ыт", "ены", "ить", "ыть", "ишь", "ую", "ю", "ла",
    "на", "ете", "йте", "ли", "й", "л", "ем", "н", "ло", "ет", "ют", "ны", "ть", "ешь", "нно" };
  rusEnds["adjective"] = { "ее", "ие", "ые", "ое", "ими", "ыми", "ей", "ий", "ый", "ой", "ем", "им", "ым", "ом",
    "его", "ого", "ему", "ому", "их", "ых", "ую", "юю", "ая", "яя", "ою", "ею" };
  rusEnds["adverb"] = { "чно", "еко", "соко", "боко", "роко", "имо", "мно", "жно", "жко", "ело", "тно", "льно",
    "здо", "зко", "шо", "хо", "но" };
  rusEnds["numeric"] = { "чуть", "много", "мало", "еро", "вое", "рое", "еро", "сти", "одной", "двух", "рех",
    "еми", "яти", "ьми", "ати", "дного", "сот", "сто", "ста", "тысяча", "тысячи", "две", "три", "одна", "умя", "тью",
    "мя", "тью", "мью", "тью", "одним"};
  rusEnds["conjuct"] = { "более", "менее", "очень", "крайне",
    "когда", "однако", "если", "чтоб", "хотя", "смотря", "как", "также", "так", "зато", "что", "или", "потом",
    "это", "того", "тоже", "словно", "ежели", "кабы", "коли", "ничем", "чем", "и", "да"};
  rusEnds["prepos"] = { "в", "на", "по", "из", "за", "у", "от", "с", "об", "к", "перед", "между", "под", "без",
    "около", "из-за", "из-под", "для", "про", "до", "о", "вокруг", "при", "возле" };

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
