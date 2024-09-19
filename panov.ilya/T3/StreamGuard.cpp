#include "StreamGuard.hpp"

panov::StreamGuard::StreamGuard(std::basic_ios< char >& stream) :
  stream_(stream),
  precision_(stream.precision()),
  flags_(stream.flags())
{}

panov::StreamGuard::~StreamGuard()
{
  stream_.precision(precision_);
  stream_.flags(flags_);
}
