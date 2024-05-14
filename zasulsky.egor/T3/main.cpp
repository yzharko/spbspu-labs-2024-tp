#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "InpOutTypes.hpp"
#include "cmdTree.hpp"

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "few parameters\n";
    return 1;
  }
  std::ifstream file(argv[1]);
  if (!file.is_open())
  {
    std::cout << "file isn't open!\n";
    return 2;
  }
  std::vector< zasulsky::Polygon > polygons;
  while (!file.eof())
  {
    std::copy(std::istream_iterator< zasulsky::Polygon >(file),
      std::istream_iterator< zasulsky::Polygon >(),
      std::back_inserter(polygons));
    if (file.fail())
    {
      file.clear();
      zasulsky::skipUntilNewLine(file);
    }
  }
  zasulsky::CmdTree cmd;
  while (!std::cin.eof())
  {
    std::string str;
    zasulsky::Polygon pol;
    std::string command;
    int num = 0;
    std::string secondWord = "";
    std::string firstWord = "";
    std::cin >> firstWord;
    std::getline(std::cin, secondWord);
    secondWord.erase(0, 1);
    command = firstWord;
    command += " " + secondWord;
    bool isTwoWordInCommandName = false;

    try
    {
      if (std::cin.eof())
      {
        break;
      }

      if (cmd.checkCommand(command))
      {
        isTwoWordInCommandName = true;
      }
      else if (cmd.checkCommand(firstWord))
      {
        command = firstWord;
      }
      else
      {
        throw std::invalid_argument("no command");
      }

      if (cmd.cmdsOne.count(command))
      {
        cmd.doCommand(command, polygons, std::cout);
        std::cout << '\n';
      }

      if (cmd.cmdsTwo.count(command))
      {
        if (isTwoWordInCommandName)
        {
          std::cin >> num;
        }
        else
        {
          num = stoi(secondWord);
        }
        cmd.doCommand(command, polygons, num, std::cout);
        std::cout << '\n';
      }

      if (cmd.cmdsThree.count(command))
      {
        if (isTwoWordInCommandName)
        {
          std::cin >> pol >> zasulsky::DelimiterIO{ '\n' };
          if (!std::cin)
          {
            zasulsky::printInvCmd(std::cout);
            std::cin.clear();
            zasulsky::skipUntilNewLine(std::cin);
          }
        }
        else
        {
          pol = stringToPolygon(secondWord);
        }
        cmd.doCommand(command, polygons, pol, std::cout);
        std::cout << '\n';
      }
    }
    catch (...)
    {
      zasulsky::printInvCmd(std::cout);
      std::cout << '\n';
    }
  }
  return 0;
}
