#include <iostream>
#include <fstream>
#include <limits>
#include <map>
#include <string>
// #include <vector>
#include "functions.hpp"
#include "mapOfCommands.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Not enough input parameters...";
    return 1;
  }
  std::ifstream inputFile(argv[1]);
  if (!inputFile.is_open())
  {
    std::cerr << "The file cannot be opened\n";
    return 2;
  }
  using namespace mihalchenko;
  std::vector<Polygon> polygons;
  using del = DelimiterIO;
  while (!inputFile.eof())
  {
    std::copy(std::istream_iterator<Polygon>(inputFile),
              std::istream_iterator<Polygon>(),
              std::back_inserter(polygons));
    if (inputFile.fail())
    {
      inputFile.clear();
      inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::map<std::string, std::function<void(const std::vector<Polygon> &vec,
                                           std::istream &in, std::ostream &out)>>
      cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(printArea, _1, _2, _3);
  }
  mihalchenko::Polygon polygon;
  std::string command = "";
  // int n = 0;
  /*std::string firstPartOfCmd = "";
  std::string secondPartOfCmd = "";
  std::cin >> firstPartOfCmd;
  command = firstPartOfCmd;*/

  // std::getline(std::cin, secondPartOfCmd);
  // secondPartOfCmd.erase(0, 1);
  // command = firstPartOfCmd + " " + secondPartOfCmd;
  // std::cout << command << "\n";
  // bool isCmdWithTwoWords = false;
  /*try
  {
    if (names::cmdWithStrings.count(command))
    {
      doCmdWithStrings(command, polygons, std::cout << '\n');
      // std::cout << '\n';
    }
    if (names::cmdwithStringAndDigit.count(command))
    {
      n = std::stoi(secondPartOfCmd);
      doCmdWithStringAndDigit(command, polygons, n, std::cout << '\n');
      // std::cout << '\n';
    }
    if (names::cmdwithPolygon.count(command))
    {
      if (isCmdWithTwoWords)
      {
        std::cin >> polygon >> del{'\n'};
        if (!std::cin)
        {
          std::cout << "<INVALID COMMAND>";
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }
      else
      {
        // polygon = stringToPolygon(secondPartOfCmd);
      }
      doCmdWithDigitAndPolygon(command, polygons, polygon, std::cout << '\n');
      // std::cout << '\n';
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << "<INVALID COMMAND>" << '\n';
  }*/
  while (std::cin >> command)
  {
    try
    {
      cmds.at(command)(polygons, std::cin, std::cout);
    }
    catch (const std::exception &)
    {
      std::cerr << "<INVALID COMMAND>" << '\n';
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  return 0;
}
