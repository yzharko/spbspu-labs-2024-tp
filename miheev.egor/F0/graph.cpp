#include "graph.hpp"
#include <delimiters.hpp>

miheev::Edge::Edge():
  weight_(0),
  dest_(nullptr)
{}

miheev::Edge::Edge(Node* nodePtr, size_t weight):
  weight_(weight),
  dest_(nodePtr)
{}

bool miheev::Edge::operator==(const miheev::Edge& rhs) const
{
  return dest_ == rhs.dest_ and rhs.weight_ == weight_;
}

size_t miheev::Edge::HashFunction::operator()(const Edge& rhs) const
{
  size_t ptrHash = std::hash< Node* >()(rhs.dest_);
  size_t weightHash = std::hash< size_t >()(rhs.weight_) << 1;
  return ptrHash ^ weightHash;
}

miheev::Node::Node(int name):
  name_(name)
{}

// void miheev::Node::addEdge(const miheev::Edge& edge)
// {
//   edges_.insert(edge);
// }

// int miheev::Node::name() const noexcept
// {
//   return name_;
// }
