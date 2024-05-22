#include "commands.hpp"
#include <iostream>
#include <functional>
#include <algorithm>
#include <fstream>
#include <limits>
#include <iterator>

namespace sukacheva
{
  void help(std::ostream& out)
  {
    out << "help - displays all available commands with parameters\n";
    out << "create <graph> <graphname> - creating an empty graph called graphname\n";
    out << "work <graphname> - switching to working with a graphname\n";
    out << "add <vertex> <name> – creating a graph vertex called name\n";
    out << "add < edge > < first_node, second_node, weight > - ";
    out << "creating an edge between the vertices first_node and second_node with some weight\n";
    out << "delete <vertex> <name> - deleting vertex name\n";
    out << "delete < edge > < first, second > - deleting an edge between the vertices first and second\n";
    out << "capacity <graphname> - displays the number of vertices in the graph graphname\n";
    out << "weightTable <graphname> - displays the weight table of the graph graphname\n";
    out << "print <path> <name> - prints the shortest paths from the top name to the rest.\n";
    out << "print <distance> <name> - prints the lengths of the shortest paths from the vertex name to the rest.\n";
    out << "open <filename> - open a file for reading with a given name\n";
    out << "save <filename> - open a file for output with a given name\n";
    out << "list - display a list of graphs\n";
    out << "graphname - displays the name of the graph being worked on\n";
    out << "delete <graph> <graphname> - deleting graph graphname\n";
    out << "clear - deleting all vertices of the actual graph\n";
  }

  void createGraph(GraphList& graphList, std::string& graphName)
  {
    Graph graph(graphName);
    Workspace actual(graph);
    graphList.graphList.insert({ graphName, actual });
    graph = graphList.switchActualGraph(graphName);
  }

  void addVertex(GraphList& graphList, std::string& name)
  {
    graphList.findActiveWorkspace().addVertex(name);
  }

  void addEdge(GraphList& graphList, std::string& start, std::string& end, size_t weight)
  {
    graphList.findActiveWorkspace().addEdge(start, end, weight);
  }

  void deleteVertex(GraphList& graphList, std::string& name)
  {
    graphList.findActiveWorkspace().deleteVertex(name);
  }

  void deleteEdge(GraphList& graphList, std::string& start, std::string& end)
  {
    graphList.findActiveWorkspace().deleteEdge(start, end);
  }

  void capacity(GraphList& graphList, std::istream& in, std::ostream& out)
  {
    std::string graphName;
    in >> graphName;
    out << graphName << " capacity: ";
    out << graphList.findGraphName(graphName).capacity() << "\n";
  }

  void graphName(GraphList& graphList, std::ostream& out)
  {
    out << graphList.findActiveWorkspace().GraphName << "\n";
  }

  void deleteGraph(GraphList& graphList, std::string& graphName)
  {
    graphList.graphList.erase(graphName);
  }

  void clearGraph(GraphList& graphList, std::ostream& out)
  {
    graphList.findActiveWorkspace().clear();
    out << "Actual graph has 0 vertexes.\n";
  }

  void printGraphList(std::ostream& out, GraphList graphList)
  {
    for (auto it = graphList.graphList.begin(); it != graphList.graphList.end(); ++it)
    {
      out << it->first << "\n";
    }
  }

  std::pair< std::map< size_t, size_t >, std::map< size_t, size_t > > getDistances(GraphList& graphList, std::string& name)
  {
    return graphList.findActiveWorkspace().dijkstraDistances(name);
  }

  std::vector< std::string > getPath(GraphList& graphList, std::string& start, std::string& end)
  {
    return graphList.findActiveWorkspace().dijkstraPath(graphList.findActiveWorkspace().dijkstraDistances(start).second, start, end);
  }

  std::map< size_t, std::vector< std::string > > getPathes(GraphList& graphList, std::string& name)
  {
    size_t capacity = graphList.findActiveWorkspace().capacity();
    std::map< size_t, std::vector< std::string > > result;
    for (size_t i = 0; i != capacity; i++)
    {
      result[i] = getPath(graphList, name, graphList.findActiveWorkspace().VertexesList[i]);
    }
    return result;
  }

  void printPath(std::vector< std::string > path, std::ostream& out)
  {
    size_t capacity = path.size();
    for (size_t i = 0; i != capacity; i++)
    {
      out << path[i];
      if (i != capacity - 1)
      {
        out << " ";
      }
    }
  }

  void printPathes(GraphList& graphList, std::string& name, std::ostream& out)
  {
    std::map< size_t, std::vector< std::string > > pathesList = getPathes(graphList, name);
    size_t capacity = graphList.findActiveWorkspace().capacity();
    for (size_t i = 0; i != capacity; i++)
    {
      out << "Shortest path to " << graphList.findActiveWorkspace().VertexesList[i] << ": ";
      printPath(pathesList[i], out);
      out << "\n";
    }
  }

  void printDistances(GraphList& graphList, std::string& name, std::ostream& out)
  {
    std::pair< std::map< size_t, size_t >, std::map< size_t, size_t > > result = getDistances(graphList, name);
    std::map< size_t, size_t > distances = result.first;

    Graph activeWorkspace = graphList.findActiveWorkspace();

    std::vector< std::string > outputLines;
    outputLines.reserve(distances.size());

    std::transform(
      distances.begin(),
      distances.end(),
      std::back_inserter(outputLines),
      [&name, &activeWorkspace](const auto& distancePair) {
        return "Distance from " + name + " to " + activeWorkspace.VertexesList[distancePair.first]
          + " : " + std::to_string(distancePair.second) + "\n"; }
    );

    std::copy(outputLines.begin(), outputLines.end(), std::ostream_iterator<std::string>(out));
  }

  void commandCreateGraph(GraphList& graphList, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    std::map< std::string, std::function< void(GraphList& graphList, std::string& graphName) > > commandKey;
    commandKey["graph"] = std::bind(createGraph, _1, _2);
    std::string command;
    std::string graphName;
    in >> command >> graphName;
    try
    {
      createGraph(graphList, graphName);
      out << "Graph " << graphName << " is created.\n";
    }
    catch (const std::out_of_range& e)
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }

  void commandAdd(GraphList& graphList, std::istream& in, std::ostream& out)
  {
    std::string command;
    std::string start;
    std::string end;
    size_t weight;
    in >> command >> start;
    if (command.empty() || start.empty())
    {
      out << "<INVALID COMMAND>\n";
      in.clear();
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return;
    }
    try
    {
      if (command == "vertex")
      {
        std::string extra;
        in >> extra;
        if (!extra.empty())
        {
          out << "<INVALID COMMAND>\n";
          in.clear();
          in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          return;
        }
        addVertex(graphList, start);
        out << "Vertex " << start << " is added.\n";
      }
      else if (command == "edge")
      {
        in >> end >> weight;
        if (in.fail() || end.empty())
        {
          in.clear();
          in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          throw std::logic_error("<INVALID COMMAND>\n");
        }
        addEdge(graphList, start, end, weight);
        out << "Edge between " << start << " and " << end << " with weight " << weight << " is added.\n";
      }
    }
    catch (const std::exception& e)
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }

  void commandPrint(GraphList& graphList, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    std::map< std::string, std::function< void(GraphList& graphList, std::string& name, std::ostream& out) > > commandKey;
    commandKey["path"] = std::bind(printPathes, _1, _2, _3);
    commandKey["distance"] = std::bind(printDistances, _1, _2, _3);
    std::string command;
    std::string name;
    in >> command >> name;
    try
    {
      commandKey.at(command)(graphList, name, out);
    }
    catch (const std::out_of_range& e)
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }

  void commandDelete(GraphList& graphList, std::istream& in, std::ostream& out)
  {
    using namespace std::placeholders;
    std::map< std::string, std::function< void(GraphList& graphList, std::string& name) > > commandKey;
    commandKey["vertex"] = std::bind(deleteVertex, _1, _2);
    commandKey["graph"] = std::bind(deleteGraph, _1, _2);
    std::string command;
    std::string name;
    std::string end;
    in >> command >> name;
    try
    {
      commandKey.at(command)(graphList, name);
      out << "Struct " << command << " " << name << " was deleted.\n";
    }
    catch (const std::out_of_range& e)
    {
      if (command == "edge")
      {
        in >> end;
        deleteEdge(graphList, name, end);
        out << "Edge between " << name << " and " << end << " deleted.\n";
      }
      else
      {
        throw std::logic_error("<INVALID COMMAND>\n");
      }
    }
  }

  void commandSwitch(GraphList& graphList, std::istream& in, std::ostream& out)
  {
    std::string name;
    in >> name;
    try
    {
      graphList.switchActualGraph(name);
      out << "Now work is being done on the graph " << name << "\n";
    }
    catch (const std::exception& e)
    {
      throw std::logic_error("<INVALID COMMAND>\n");
    }
  }

  void printMatrix(GraphList& graphList, std::ostream& out)
  {
    std::vector< std::vector< size_t > > weightTable = graphList.findActiveWorkspace().weightTable();
    size_t rows = weightTable.size();
    for (size_t i = 0; i < rows; i++)
    {
      for (size_t j = 0; j < rows; j++)
      {
        if (weightTable[i][j] == std::numeric_limits<size_t>::max())
        {
          out << "inf ";
        }
        else
        {
          out << weightTable[i][j] << " ";
        }
      }
      out << "\n";
    }
  }

  void commandOpen(GraphList& graphList, std::istream& in, std::ostream& out)
  {
    Graph graph;
    std::string filename;
    in >> filename;
    std::ifstream input(filename);
    if (!input)
    {
      throw std::logic_error("There is no such file.\n");
    }
    input >> graph;
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    else
    {
      Workspace actual(graph);
      graphList.graphList.insert({ graph.GraphName, actual });
      graph = graphList.switchActualGraph(graph.GraphName);
      out << "Work with graph " << graph.GraphName << " that was read from a file " << filename << ".\n";
    }
  }

  void commandSave(GraphList& graphList, std::istream& in, std::ostream& out)
  {
    std::string filename;
    in >> filename;
    std::ofstream output;
    output.open(filename, std::ios::app);
    if (!output)
    {
      throw std::logic_error("There is no such file.\n");
    }
    printMatrix(graphList, output);
    out << "Graph was saved to file " << filename << ".\n";
  }
}
