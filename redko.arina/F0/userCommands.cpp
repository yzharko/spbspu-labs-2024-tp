#include "userCommands.hpp"
#include <fstream>
#include <iterator>
#include <limits>
#include "processingFunctions.hpp"

void redko::help(const std::string & descr)
{
  if (descr.empty())
  { 
    std::cout << "help\n";
    std::cout << "      see list of commands\n";
    std::cout << "code\n";
    std::cout << "      encode text from input\n";
    std::cout << "      finish text input by typing <end> on a new line\n";
    std::cout << "code <filename>\n";
    std::cout << "      encode text from the file\n";
    std::cout << "decode\n";
    std::cout << "      decode text from input\n";
    std::cout << "      enter the encoded text first, then the alphabet encoding\n";
    std::cout << "      finish the alphabet encoding input by typing <end> on a new line\n";
    std::cout << "decode <filename>\n";
    std::cout << "      decode text from the file\n";
    std::cout << "      the first part of the file must contain encoded text\n";
    std::cout << "      the second part of the file must contain the alphabet encoding\n";
    std::cout << "recode <filename1> <filename2>\n";
    std::cout << "      unite and encode the text from both files\n";
    std::cout << "      the first part of the file must contain encoded text\n";
    std::cout << "      the second part of the file must contain the alphabet encoding\n";
    std::cout << "print\n";
    std::cout << "      display result on the screen\n";
    std::cout << "save <filename>\n";
    std::cout << "      save result to the file\n";
    std::cout << "quit\n";
    std::cout << "      exit the result processing mode\n";
    std::cout << "      exit the program when there is nothing to work with\n";
    std::cout << "compare <filename1> <filename2>\n";
    std::cout << "      compare encodings of identical characters in files\n";
  }
  else
  {
    redko::printMessage(std::cout, "<invalid command>");
  }
}

void redko::code(const std::string & descr)
{
  std::string str = "";
  std::string res = "";

  if (descr.empty())
  {
    while (std::getline(std::cin, str) && str != "end")
    {
      res += str;
      res += '\n';
    }
  }
  else
  {
    std::ifstream input(descr);
    if (!input)
    {
      throw std::logic_error("<unable to open the file>");
    }
    std::getline(input, res);
    while (std::getline(input, str))
    {
      res += '\n';
      res += str;
    }
  }
  if (res.empty())
  {
    throw std::logic_error("<empty input>");
  }
  HuffmanCode obj(res);
  obj.encode();

  redko::printMessage(std::cout, "<succesfully encoded>");

  std::string description = "";
  while (std::getline(std::cin, description) && description != "quit")
  {
    if (description == "print")
    {
      print("code", obj);
    }
    else if (cutName(description) == "save")
    {
      save("code", description, obj);
    }
    else
    {
      redko::printMessage(std::cout, "<invalid command>");
    }
  }
}

void redko::decode(const std::string & descr)
{
  HuffmanCode obj;

  if (descr.empty())
  {
    if (!(std::cin >> obj))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      throw std::logic_error("<invalid Huffman format>");
    }
  }
  else
  {
    std::ifstream input(descr);
    if (!input)
    {
      throw std::logic_error("<unable to open the file>");
    }
    if (!(input >> obj) && !input.eof())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
      throw std::logic_error("<invalid Huffman format>");
    }
  }

  obj.decode();

  redko::printMessage(std::cout, "<succesfully decoded>");

  std::string description = "";
  while (std::getline(std::cin, description) && description != "quit")
  {
    if (description == "print")
    {
      print("decode", obj);
    }
    else if (cutName(description) == "save")
    {
      save("decode", description, obj);
    }
    else
    {
      redko::printMessage(std::cout, "<invalid command>");
    }
  }
}

void redko::recode(const std::string & descr)
{
  std::string d = descr;
  std::fstream firstInput(cutName(d));
  std::fstream secondInput(cutName(d));

  if (!firstInput || !secondInput)
  {
    throw std::logic_error("<unable to open the file>");
  }

  HuffmanCode firstObj;
  if (!(firstInput >> firstObj) && !firstInput.eof())
  {
    firstInput.clear();
    firstInput.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    throw std::logic_error("<invalid Huffman format>");
  }
  firstObj.decode();
  
  HuffmanCode secondObj;
  if (!(secondInput >> secondObj) && !secondInput.eof())
  {
    secondInput.clear();
    secondInput.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    throw std::logic_error("<invalid Huffman format>");
  }
  secondObj.decode();

  std::string united = firstObj.getDecoded() + secondObj.getDecoded();
  HuffmanCode result(united);
  result.encode();

  redko::printMessage(std::cout, "<succesfully recoded>");

  std::string description = "";
  while (std::getline(std::cin, description) && description != "quit")
  {
    if (description == "print")
    {
      print("code", result);
    }
    else if (cutName(description) == "save")
    {
      save("code", description, result);
    }
    else
    {
      redko::printMessage(std::cout, "<invalid command>");
    }
  }
}

void redko::print(const std::string & command, HuffmanCode obj)
{
  if (command == "code")
  {
    std::cout << obj.getEncoded() << '\n';
  }
  else
  {
    std::cout << obj.getDecoded() << '\n';
  }
}

void redko::save(const std::string & command, const std::string & descr, HuffmanCode obj)
{
  std::ofstream output(descr);
  if (!output)
  {
    redko::printMessage(std::cout, "invalid command");
  }
  if (command == "code")
  {
    output << obj.getEncoded();
    auto encoding = obj.getEncoding();
    for (auto i : encoding)
    {
      output << '\n' << i.second << " :" << i.first;
    }
  }
  else
  {
    output << obj.getDecoded();
  }
}

void redko::compare(const std::string & descr)
{
  std::string d = descr;
  std::fstream firstInput(cutName(d));
  std::fstream secondInput(cutName(d));

  if (!firstInput || !secondInput)
  {
    throw std::logic_error("<unable to open the file>");
  }

  HuffmanCode firstObj;
  if (!(firstInput >> firstObj) && !firstInput.eof())
  {
    firstInput.clear();
    firstInput.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    throw std::logic_error("<invalid Huffman format>");
  }
  auto firstEncoding = firstObj.getEncoding();
  
  HuffmanCode secondObj;
  if (!(secondInput >> secondObj) && !secondInput.eof())
  {
    secondInput.clear();
    secondInput.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    throw std::logic_error("<invalid Huffman format>");
  }
  auto secondEncoding = secondObj.getEncoding();
  size_t count = 0;
  for (auto curr = firstEncoding.begin(); curr != firstEncoding.end(); ++curr)
  {
    auto it = secondEncoding.find(curr->first);
    if (it != secondEncoding.end())
    {
      ++count;
      std::cout << curr->first << ": " << curr->second << ' ' << it->second << '\n';
    }
  }
  if (count == 0)
  {
    redko::printMessage(std::cout, "<no matching symbols>");
  }
}
