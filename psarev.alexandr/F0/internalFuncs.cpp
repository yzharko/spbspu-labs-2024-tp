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
          resStorage.emplace(spType, words);
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
  for (char p : puncts)
  {
    if (word.back() == p)
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

  rusEnds["noun"] = { "а", "ев", "ов", "ье", "иями", "ями", "ами", "еи", "ии", "и", "ией" };
  std::vector< std::string > nSec = { "ем", "ам", "ом", "о", "у", "ах", "иях", "ях" };
  std::vector< std::string > nThi = { "я", "ок", "мва", "яна", "ровать", "ег", "ги" };
  std::vector< std::string > nFou = { "ий", "й", "иям", "ю", "ия", "ья", "ям", "ием" };
  std::vector< std::string > nFif = { "ы", "ь", "ию", "ью", "га", "сть", "сти", "ей", "ой" };
  rusEnds["noun"].insert(rusEnds["noun"].end(), nSec.begin(), nSec.end());
  rusEnds["noun"].insert(rusEnds["noun"].end(), nThi.begin(), nThi.end());
  rusEnds["noun"].insert(rusEnds["noun"].end(), nFou.begin(), nFou.end());
  rusEnds["noun"].insert(rusEnds["noun"].end(), nFif.begin(), nFif.end());

  rusEnds["verb"] = { "ила", "ыла", "ена", "ейте", "уйте", "ите", "или", "ыли", "ей", "уй" };
  std::vector< std::string > vSec = { "ено", "ят", "ует", "уют", "ит", "ыт", "ены", "ить" };
  std::vector< std::string > vThi = { "на", "ете", "йте", "ли", "й", "л", "ем", "н", "ло" };
  std::vector< std::string > vFou = { "им", "ым", "ен", "ило", "ыло", "ть", "ешь", "нно", "ет" };
  std::vector< std::string > vFif = { "ыть", "ишь", "ую", "ют", "ны", "ю", "ла", "ил", "ыл" };
  rusEnds["verb"].insert(rusEnds["verb"].end(), vSec.begin(), vSec.end());
  rusEnds["verb"].insert(rusEnds["verb"].end(), vThi.begin(), vThi.end());
  rusEnds["verb"].insert(rusEnds["verb"].end(), vFou.begin(), vFou.end());
  rusEnds["verb"].insert(rusEnds["verb"].end(), vFif.begin(), vFif.end());

  rusEnds["adjective"] = { "ее", "ие", "ые", "ое", "ими", "ыми", "ей", "ий", "ый", "ой" };
  std::vector< std::string > aSec = { "его", "ого", "ему", "ому", "их", "ых", "ую", "юю" };
  std::vector< std::string > aThi = { "ая", "яя", "ою", "ею", "ем", "им", "ым", "ом" };
  rusEnds["adjective"].insert(rusEnds["adjective"].end(), aSec.begin(), aSec.end());
  rusEnds["adjective"].insert(rusEnds["adjective"].end(), aThi.begin(), aThi.end());

  rusEnds["adverb"] = { "чно", "еко", "око", "имо", "мно", "жно", "жко", "ело", "тно" };
  std::vector< std::string > dSec = { "здо", "зко", "шо", "хо", "но", "льно" };
  rusEnds["adjective"].insert(rusEnds["adjective"].end(), dSec.begin(), dSec.end());

  rusEnds["numeric"] = { "много", "еро", "вое", "рое", "еро", "сти", "двух", "рех", "еми" };
  std::vector< std::string > uSec = { "дного", "сот", "сто", "ста", "тысяча", "тысячи" };
  std::vector< std::string > uThi = { "мью", "тью", "одним", "умя", "тью", "мя", "тью" };
  std::vector< std::string > uFou = { "три", "одна", "яти", "ьми", "ати", "две" };
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), uSec.begin(), uSec.end());
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), uThi.begin(), uThi.end());
  rusEnds["numeric"].insert(rusEnds["numeric"].end(), uFou.begin(), uFou.end());

  rusEnds["conjuct"] = { "более", "менее", "очень", "крайне", "когда", "однако", "если" };
  std::vector< std::string > cSec = { "зато", "что", "или", "потом", "это", "того", "тоже" };
  std::vector< std::string > cThi = { "и", "да", "кабы", "коли", "ничем", "чем", "также" };
  std::vector< std::string > cFou = { "словно", "ежели", "хотя", "как", "так", "чтоб" };
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cSec.begin(), cSec.end());
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cThi.begin(), cThi.end());
  rusEnds["conjuct"].insert(rusEnds["conjuct"].end(), cFou.begin(), cFou.end());

  rusEnds["prepos"] = { "в", "на", "slovo", "из", "за", "у", "от", "с", "об", "к", "перед" };
  std::vector< std::string > pSec = { "из-под", "для", "про", "до", "о", "вокруг", "при" };
  std::vector< std::string > pThi = { "возле", "из-за", "без", "между", "под", "около" };
  rusEnds["prepos"].insert(rusEnds["prepos"].end(), pSec.begin(), pSec.end());
  rusEnds["prepos"].insert(rusEnds["prepos"].end(), pThi.begin(), pThi.end());

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
    for (size_t i = 0; i <= 6; i++)
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

int psarev::letToSound(int let, char letType, bool& softFact)
{
  std::string softMakers = "ёйеячищюь";
  std::string notSoftMakers = "цукнгшзхъфывапролджэсмтб";
  for (int l : softMakers)
  {
    if (l == let)
    {
      softFact = true;
      if (l == -11887)
      {
        return 'о';
      }
      else if (l == -12103)
      {
        return 'й';
      }
      else if (l == 'я')
      {
        return 'а';
      }
      else if (l == 'ч')
      {
        return 'ч';
      }
      else if (l == 'и')
      {
        return 'и';
      }
      else if (l == 'щ')
      {
        return 'щ';
      }
      else if (l == 'ю')
      {
        return 'у';
      }
    }
  }

  for (int l : notSoftMakers)
  {
    if (l == let)
    {
      softFact = false;
      if (l == 'ц')
      {
        return 'ц';
      }
      else if (l == 'у')
      {
        return 'у';
      }
      else if (l == 'к')
      {
        return 'к';
      }
      else if (l == 'н')
      {
        return 'н';
      }
      else if (l == 'г')
      {
        return 'к';
      }
      else if (l == 'ш')
      {
        return 'ш';
      }
      else if (l == 'з')
      {
        return 'с';
      }
      else if (l == 'х')
      {
        return 'х';
      }
      else if (l == 'ф')
      {
        return 'ф';
      }
      else if (l == 'ы')
      {
        return 'ы';
      }
      else if (l == 'в')
      {
        return 'ф';
      }
      else if (l == 'а')
      {
        return 'а';
      }
      else if (l == 'п')
      {
        return 'п';
      }
      else if (l == 'р')
      {
        return 'р';
      }
      else if (l == 'о')
      {
        return 'о';
      }
      else if (l == 'л')
      {
        return 'л';
      }
      else if (l == 'д')
      {
        return 'т';
      }
      else if (l == 'ж')
      {
        return 'ш';
      }
      else if (l == 'э')
      {
        return 'э';
      }
      else if (l == 'с')
      {
        return 'с';
      }
      else if (l == 'м')
      {
        return 'м';
      }
      else if (l == 'т')
      {
        return 'т';
      }
      else if (l == 'б')
      {
        return 'п';
      }
    }
  }
  return ' ';
}

bool psarev::printSound(std::ostream& out, int sound, bool softFact)
{
  std::string vowel = "уыаоэи";
  for (int l : vowel)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - гласный";
      if (l == 'o' && softFact)
      {
        out << " ,ударный";
      }
      out << '\n';
      return true;
    }
  }

  std::string deafNPair = "хцчщ";
  std::string deafPair = "кшфпст";
  std::string voicedNPair = "йнрмл";
  std::string voicedPair = "гзвдж";
  for (int l : deafNPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, глухой непарный";
      if ((softFact && l == 'х') || (l != 'х'))
      {
        out << " ,мягкий";
        if (l == 'х')
        {
          out << " парный";
        }
        else
        {
          out << " непарный";
        }
      }
      else if (!softFact && l == 'х')
      {
        out << " ,твердый парный";
      }
      out << '\n';
      return false;
    }
  }

  for (int l : deafPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, глухой парный";
      if (softFact && l != 'ш')
      {
        out << " ,мягкий";
        if (l == 'ш')
        {
          out << " непарный";
        }
        else
        {
          out << " парный";
        }
      }
      else
      {
        if (l == 'ш')
        {
          out << " ,твердый непарный";
        }
        else
        {
          out << " ,твердый парный";
        }
      }
      out << '\n';
      return false;
    }
  }

  for (int l : voicedNPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, звонкий непарный";
      if (l == 'й')
      {
        out << " ,мягкий непарный";
      }
      else if (softFact)
      {
        out << " ,мягкий парный";
      }
      else
      {
        out << " ,твердый парный";
      }
      out << '\n';
      return false;
    }
  }

  for (int l : voicedPair)
  {
    if (l == sound)
    {
      out << "[ " << sound << " ] - согласный, звонкий парный";
      if (softFact)
      {
        out << " ,мягкий парный";
      }
      else
      {
        out << " ,твердый парный";
      }
      out << '\n';
      return false;
    }
  }

  return false;
}
