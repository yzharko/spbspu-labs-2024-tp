#include "commands.hpp"
#include <iostream>
#include <fstream>
#include "accessoryFunctions.hpp"

void ponomarev::outputInfoAboutCommands(const std::string & parameters, ponomarev::HuffmanCode &)
{
  if (parameters.empty())
  {
    std::cout << "ATTENTION all commands with parameters must have one space as delimiters\n";
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "1) 'help' - output information about commands\n";
    std::cout << "2) 'input' - start working with standart input from user\n";
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "3) 'encode' - encoding of text entered from standard input\n";
    std::cout << "4) 'encode <filename>' - encoding of text in the filename\n";
    std::cout << "5) 'encode <n> <k> <filename>' - encoding of text in the filename from the n character to the k\n";
    std::cout << "6) 'write <filename>' - write the text entered from the standard input in filename\n";
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "7) 'set decode <filename>' - set the frequency table for decoding the file\n";
    std::cout << "8) 'combine <filename1> <filename2> <filename3> ' - merge data from filename1 and filename2 into filename3\n";
    std::cout << "9) 'decode <filename1> <filename2>' - decode the text contained in filename1 ";
    std::cout << "using the frequency table specified in filename2\n";
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "10) 'delete <n> <k> <filename> ' - deleting characters n through k in filename\n";
    std::cout << "11) 'delete <filename> ' - delete a file\n";
    std::cout << "12) 'clean' - delete all files\n";
    std::cout << "13) 'clean <filename>' - clear the contents of the file\n";
    std::cout << "------------------------------------------------------------------------\n";
    std::cout << "14) 'table' - output of the character encoding table for the encoding result\n";
    std::cout << "15) 'save <filename>' - saving the result of the work to a new txt file filename\n";
  }
  else
  {
    throw std::logic_error("error: wrong parameters");
  }
}

void ponomarev::makeInput(std::string & parameters, ponomarev::HuffmanCode & data)
{
  if (parameters.empty())
  {
    ponomarev::getText(std::cin, data);
  }
}

void ponomarev::chooseEncode(std::string & parameters, HuffmanCode & data)
{
  if (parameters.empty())
  {
    ponomarev::makeEncode(data);
  }
  else
  {
    std::string parameter = cutType(parameters);
    if (!isNum(parameter))
    {
      std::ifstream input(parameter);
      if (!input)
      {
        throw std::logic_error("can't open the file");
      }

      ponomarev::getText(input, data);
      ponomarev::makeEncode(data);
    }
    else
    {
      long long n = std::stoll(parameter);
      long long k = 0;
      parameter = cutType(parameters);
      if (!isNum(parameter))
      {
        throw std::logic_error("error: wrong parameters");
      }
      else
      {
        k = std::stoll(parameter);
        parameter = cutType(parameters);
        if (parameters.empty())
        {
          std::ifstream input(parameter);
          ponomarev::cutTextInFile(n, k, data, input);
          ponomarev::makeEncode(data);
        }
        else
        {
          throw std::logic_error("error: wrong parameters");
        }
      }
    }
  }
}

