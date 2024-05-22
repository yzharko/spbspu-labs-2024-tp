#include "accessoryFunctions.hpp"

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
  return elem.find_first_not_of("0123456789") == std::string::npos && elem.size() != 0;
}

void ponomarev::getText(std::istream & input, HuffmanCode & data)
{
  std::string str = "";
  std::string text = "";

  while (std::getline(input, str))
  {
    text += str;
    text += '\n';
  }
  data.putText(text);
}

void ponomarev::cutTextInFile(long long n, long long k, HuffmanCode & data, input)
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
    text = line.substr(n, (k - n));
    data.putText(text);
  }
}

std::ostream & ponomarev::printInvalidCommandMessage(std::ostream & out)
{
  std::string message = "<INVALID COMMAND>";
  out << message << "\n";
  return out;
}

std::ostream & ponomarev::printWelcomeMessage(std::ostream & out)
{
  std::string startMessage = "-----Start working-----";
  std::string helpfulMessage = "Hello, dear user! You can write 'help' for more information about commands";
  out << startMessage << "\n";
  out << helpfulMessage << "\n";
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
