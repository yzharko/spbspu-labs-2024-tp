#include "accessoryFunctions.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>

std::string ponomarev::cutType(std::string & line)
{
  std::string type = line.substr(0, line.find(" "));
  if (line.find(" ") == std::string::npos)
  {
    line = "";
  }
  else
  {
    line = line.substr(line.find(" ") + 1);
  }
  return type;
}

bool ponomarev::isNum(const std::string & elem)
{
  return (elem.find_first_not_of("0123456789") == std::string::npos) && (elem.size() != 0);
}

void ponomarev::getText(std::istream & input, HuffmanCode & data)
{
  std::string str = "";
  std::string text = "";
  std::getline(input, str);

  while (!input.eof() && str != "end")
  {
    text += str;
    text += '\n';
    std::getline(input, str);
  }

  data.text = text;
}

void ponomarev::cutTextInFile(long long n, long long k, HuffmanCode & data, std::istream & input)
{
  std::string str = "";
  std::string text = "";

  while (std::getline(input, str))
  {
    text += str;
    text += '\n';
  }

  if (n > k)
  {
    throw std::logic_error("error: wrong parameters");
  }
  else
  {
    text = text.substr(n, (k - n));
    data.text = text;
  }
}

void ponomarev::deleteFile(const std::string parameter)
{
  if (std::remove(parameter.c_str()) == 0)
  {
    std::cout << "File delete successfully\n";
  }
}

void ponomarev::deleteTextInFile(long long n, long long k, const std::string parameter)
{
  std::string str = "";
  std::string text = "";
  std::ifstream input(parameter);

  while (std::getline(input, str))
  {
    text += str;
    text += '\n';
  }

  if (n > k)
  {
    throw std::logic_error("error: wrong parameters");
  }

  std::string firstPart = text.substr(0, n);
  std::string secondPart = text.substr(k);
  std::string res = firstPart + secondPart;

  deleteFile(parameter);
  std::ofstream out(parameter);
  out << res << "\n";
}

std::ostream & ponomarev::printInvalidCommandMessage(std::ostream & out)
{
  out << "<INVALID COMMAND>" << "\n";
  return out;
}

std::ostream & ponomarev::printWelcomeMessage(std::ostream & out)
{
  out << "-----Start working-----" << "\n";
  out << "Hello, dear user! You can write 'help' for more information about commands" << "\n";
  return out;
}

std::ostream & ponomarev::printInvalidEncodeMessage(std::ostream & out)
{
  out << "Error, nothing to decode" << "\n";
  return out;
}

std::ostream & ponomarev::printSuccessfullyEncodeMessage(std::ostream & out)
{
  out << "Great! The encoding was completed successfully" << "\n";
  return out;
}

std::ostream & ponomarev::printSuccessfullyInputMessage(std::ostream & out)
{
  out << "The data was entered successfully\n";
  return out;
}

std::ostream & ponomarev::printSuccessfullyWriteMessage(std::ostream & out)
{
  out << "The data was successfully wrote into file\n";
  return out;
}

std::ostream & ponomarev::printSuccessfullyFrequenceInput(std::ostream & out)
{
  out << "Frequence successfully completed\n";
  return out;
}
