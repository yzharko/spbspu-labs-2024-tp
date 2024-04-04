#include <iostream>
#include "data-types.hpp"
#include "separators.hpp"

namespace zheleznyakov
{
  std::istream &operator>>(std::istream &in, zheleznyakov::DoubleIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return in >> dest.ref >> SeparatorIO{'d'};
  }

  std::istream &operator>>(std::istream &in, zheleznyakov::RealIO &&dest)
  {
    using sep = SeparatorIO;
    using label = LabelIO;
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    in >> sep{'('} >> sep{':'} >> label{"N"};
    in >> dest.ref.first;
    in >> sep{':'} >> label{"D"};
    in >> dest.ref.second;
    in >> sep{':'} >> sep{')'};
    return in;
  }

  std::istream &operator>>(std::istream &in, zheleznyakov::StringIO &&dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    return std::getline(in >> SeparatorIO{'"'}, dest.ref, '"');
  }

  bool operator<(const real &leftReal, const real &rightReal)
  {
    const double val1 = static_cast<double>(leftReal.first) / leftReal.second;
    const double val2 = static_cast<double>(rightReal.first) / rightReal.second;
    return val1 < val2;
  }
}