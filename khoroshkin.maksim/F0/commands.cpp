#include "commands.hpp"
#include <fstream>
#include "graph.hpp"

void khoroshkin::helpCmd(std::ostream & out)
{
  out << "Available commands:\n";
  out << "1) help - print list of available commands\n";
  out << "2) open < filename > - open file for read with passed filename\n";
  out << "3) input - activate user input mode, format of input: (1,2) (1,0) (2,0) (0,3), where";
  out << " edges listed in direction to right in brackets splitted by space\n";
  out << "4) print < format > - printing graph, available two options: matrix - print in format";
  out << " adjacency matrix, list - print in format adjacency list\n";
  out << "5) edge add < u, v > - adding edge between vertexes u and v\n";
  out << "6) edge delete < u, v > - deleting egde between vertexes u and v\n";
  out << "7) sort topological - printing vertexes of graph in order topological sort\n";
  out << "8) save < filename > - saving result of work in file with passed filename\n";
}

void khoroshkin::openCmd(Graph< int > & graph, std::istream & is, std::ostream & out)
{
  graph.clear();
  std::string inputFile;
  if (!(is >> inputFile))
  {
    throw std::invalid_argument("Error: wrong filename!\n");
  }

  std::ifstream input(inputFile);
  if (!(input >> graph))
  {
    out << "Error: wrong format in file!\n";
  }
  else
  {
    out << "Opened successfully!\n";
  }
}

void khoroshkin::inputCmd(Graph< int > & graph, std::istream & is, std::ostream & out)
{
  graph.clear();
  if (!(is >> graph))
  {
    out << "Error: wrong input! Your input should look like this: 3 (1,2) (1,3) (2,3)\n";
  }
  else
  {
    out << "Successful input!\n";
  }
}

void khoroshkin::printCmd(Graph< int > & graph, std::istream & is, std::ostream & out)
{
  std::string format;
  if (!(is >> format))
  {
    out << "Error: wrong input!\n";
  }

  if (format == "matrix")
  {
    graph.printAdjMatrix();
  }
  else if (format == "list")
  {
    graph.printAdjList();
  }
  else
  {
    out << "Error: unsupported format!\n";
  }
}

void khoroshkin::edgeCmd(Graph< int > & graph, std::istream & is, std::ostream & out)
{
  std::string cmd;
  if (!(is >> cmd))
  {
    out << "Error: wrong input!\n";
  }

  int vertexFirst, vertexSecond;
  if(!(is >> vertexFirst >> vertexSecond))
  {
    out << "Error: wrong input!\n";
    return;
  }

  if (cmd == "add")
  {
    graph.egdeAdd(vertexFirst, vertexSecond);
  }
  else if (cmd == "delete")
  {
    graph.egdeDelete(vertexFirst, vertexSecond);
  }
  else
  {
    out << "Error: unsupported command!\n";
  }
}

void khoroshkin::sortCmd(Graph< int > & graph, std::istream & is, std::ostream & out)
{
  std::string cmd;
  if (!(is >> cmd))
  {
    out << "Error: wrong input\n";
  }
  else
  {
    if (cmd == "topological")
    {
      graph.sortTopological();
    }
    else
    {
      out << "Error: available only topological!\n";
    }
  }
}

void khoroshkin::sortCmd(Graph< int > & graph, std::istream & is, std::ostream & out)
{
  std::string filename;
  if (!(is >> filename))
  {
    out << "Error: wrong output filename!\n";
  }
  std::ofstream outputFile(filename);
  outputFile << graph.sortTopological();
  out << "Saved successfully!\n";
}