#ifndef OUTMESSAGE_HPP
#define OUTMESSAGE_HPP
#include <iostream>

void outDescription(std::ostream& out)
{
  out << "1)help - displays a list of commands\n";
  out << "2)create <graphname> - creates an empty graph\n";
  out << "3)create <count> <graphname> - creates an undirected graph\n";
  out << "4)lonely <graphname> <count> - creates a disjoint graph\n";
  out << "5)list - displays a list of graphs\n";
  out << "6)output <graphname> - outputs the graph\n";
  out << "7)delete < graphname > - deletes a graph\n";
  out << "8)work < graphname > -  starts working with the graph\n";
  out << "9)graphname - outputs the name of the graph\n";
  out << "10)add <namevertex>  <vertex> - creates a vertex\n";
  out << "11)add <count><vertex><namevertex> - adds and binds\n";
  out << "12)connect < num > < vertex1 > < vertex2 > - connects a vertex\n";
  out << "13)connect < vertex1 > < vertex2> - returns the number of links\n";
  out << "14)double < num > < vertex1 > < vertex2 > - binds mutually\n";
  out << "15)double < vertex1 > < vertex2 > - checks the mutual connection\n";
  out << "16)delete  < vertex > - deletes a vertex\n";
  out << "17)delete < num > < vertex1 > < vertex 2 > - deletes num links\n";
  out << "18)degree < vertex > - outputs the degree of the vertex\n";
  out << "19)weight < vertex > - displays the number of links with the rest\n";
  out << "20)own < vertex > - displays the number of links of all with this\n";
  out << "21)vertex - outputs the number of vertices\n";
  out << "22)edge - outputs the number of edges\n";
  out << "23)change < num >  < vertex1 > < vertex2 > - changes the orientation of the edges\n";
  out << "24)max - outputs the vertex with the maximum degree\n";
}

#endif
