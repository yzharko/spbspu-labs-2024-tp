#include "commands.hpp"
#include <iostream>

namespace sukacheva
{
  void help(std::ostream& out)
  {
    out << "help – displays all available commands with parameters\n"; // +
    out << "create <graph> <graphname> - creating an empty graph called graphname\n"; //+
    out << "work <graphname> - switching to working with a graphname\n";
    out << "add <node> <name> – creating a graph vertex called name\n"; //+
    out << "add < edge > < first_node, second_node, weight > - creating an edge between the vertices first_node and second_node with some weight\n"; //+
    out << "delete <node> <name> - deleting vertex name\n"; //+
    out << "delete < edge > < first_node, second_node > - deleting an edge between the vertices first_node and second_node\n"; //+
    out << "capacity <graphname> - displays the number of vertices in the graph graphname\n"; //+
    out << "weightTable <graphname> - displays the weight table of the graph graphname\n";
    out << "get <shortest_path> <name> - getting the shortest path to vertex name\n";
    out << "get < distance > < name > - getting the length of the shortest path to vertex name\n";
    out << "print <shortest path> <name> - prints the shortest path to vertex name\n";
    out << "print < distance > < name > - prints the length of the shortest path to vertex name\n";
    out << "open <filename> - open a file for reading with a given name\n";
    out << "save <filename> - open a file for output with the specified parameters\n";
    out << "list - display a list of graphs\n"; //+
    out << "graphname - displays the name of the graph being worked on\n"; //+
    out << "delete <graphname> - deleting graph graphname\n"; //+
    out << "clear <graphname> - deleting all vertices of the graph graphname\n";//+
  }

  void sukacheva::createGraph(GraphList graphList, std::string graphName)
  {
    Graph graph(graphName);
    Workspace actual(graph);
    graphList.graphList.insert({ graphName, actual });
  }

  void sukacheva::addVertex(GraphList graphList, std::string name)
  {
    graphList.findActiveWorkspace().addVertex(name);
  }

  void sukacheva::addEdge(GraphList graphList, std::string start, std::string end, size_t weight)
  {
    graphList.findActiveWorkspace().addEdge(start, end, weight);
  }

  void sukacheva::deleteVertex(GraphList graphList, std::string name)
  {
    graphList.findActiveWorkspace().deleteVertex(name);
  }

  void sukacheva::deleteEdge(GraphList graphList, std::string start, std::string end)
  {
    graphList.findActiveWorkspace().deleteEdge(start, end);
  }

  void sukacheva::capacity(std::ostream& out, GraphList graphList)
  {
    out << graphList.findActiveWorkspace().capacity();
  }

  void sukacheva::graphName(std::ostream& out, GraphList graphList)
  {
    out << graphList.findActiveWorkspace().GraphName;
  }

  void sukacheva::deleteGraph(GraphList graphList, std::string graphName)
  {
    graphList.graphList.erase(graphName);
  }

  void sukacheva::clearGraph(GraphList graphList)
  {
    graphList.findActiveWorkspace().clear();
  }

  void sukacheva::printGraphList(std::ostream& out, GraphList graphList)
  {
    for (auto it = graphList.graphList.begin(); it != graphList.graphList.end(); ++it)
    {
      out << it->first << "\n";
    }
  }
}
