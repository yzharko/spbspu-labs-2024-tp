#include "cmdTree.hpp"
#include "InpOutTypes.hpp"

zasulsky::CmdTree::CmdTree()
{
  cmdsOne["AREA EVEN"] = printEvAr;
  cmdsOne["AREA ODD"] = printOdAr;
  cmdsOne["AREA MEAN"] = printMeanAr;
  cmdsOne["MAX AREA"] = printMaxAr;
  cmdsOne["MIN AREA"] = printMinAr;
  cmdsOne["MAX VERTEXES"] = printMaxVert;
  cmdsOne["MIN VERTEXES"] = printMinVert;
  cmdsOne["COUNT EVEN"] = printEvCount;
  cmdsOne["COUNT ODD"] = printOdCount;
  cmdsOne["RECTS"] = printRectsCount;

  cmdsTwo["COUNT"] = printNSizeCount;
  cmdsTwo["AREA"] = printNSizeAr;

  cmdsThree["MAXSEQ"] = printMaxSEQCount;
}

void zasulsky::CmdTree::doCommand(const std::string& cmd,
  const polygons& data,
  std::ostream& out) const
{
  typeF function = cmdsOne.at(cmd);
  function(data, out);
}

void zasulsky::CmdTree::doCommand(const std::string& cmd,
  const polygons& data,
  int num,
  std::ostream& out) const
{
  typeS function = cmdsTwo.at(cmd);
  function(data, num, out);
}

void zasulsky::CmdTree::doCommand(const std::string& cmd,
  const polygons& data,
  const Polygon& pol,
  std::ostream& out) const
{
  typeT function = cmdsThree.at(cmd);
  function(data, out, pol);
}

bool zasulsky::isSimpleCmd(std::string name)
{
  return name == "MAX" || name == "MIN" || name == "AREA" || name == "COUNT";
}

std::ostream& zasulsky::printInvCmd(std::ostream& out)
{
  return out << "<INVALID COMMAND>";
}

zasulsky::Polygon stringToPolygon(const std::string& inputString)
{
  zasulsky::Polygon polygon;
  size_t pos = 0;
  size_t spacePos = inputString.find(' ');
  if (spacePos == std::string::npos)
  {
    return polygon;
  }
  int numVertices = std::stoi(inputString.substr(0, spacePos));
  pos = spacePos + 1;
  for (int i = 0; i < numVertices; ++i)
  {
    size_t openParenthesis = inputString.find('(', pos);
    size_t closeParenthesis = inputString.find(')', openParenthesis);
    if (openParenthesis == std::string::npos || closeParenthesis == std::string::npos)
    {
      return polygon;
    }
    std::string pointStr = inputString.substr(openParenthesis + 1, closeParenthesis - openParenthesis - 1);
    size_t semicolonPos = pointStr.find(';');
    if (semicolonPos == std::string::npos)
    {
      return polygon;
    }
    zasulsky::Point point;
    point.x = std::stoi(pointStr.substr(0, semicolonPos));
    point.y = std::stoi(pointStr.substr(semicolonPos + 1));
    polygon.points.push_back(point);
    pos = closeParenthesis + 1;
  }
  return polygon;
}


