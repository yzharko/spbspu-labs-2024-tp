#include "formatGuard.hpp"

tellez::FormatGuard::FormatGuard(std::basic_ios< char >& stream):
  stream_(stream),
  flags_(stream.flags()),
  precision_(stream.precision())
{}

tellez::FormatGuard::~FormatGuard()
{
  stream_.flags(flags_);
  stream_.precision(precision_);
}
