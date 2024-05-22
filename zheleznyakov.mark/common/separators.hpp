#ifndef SEPARATORS_HPP
#define SEPARATORS_HPP
#include <iomanip>
namespace zheleznyakov
{
  struct SeparatorIO
  {
    char exp;
  };

  struct LabelIO
  {
    std::string exp;
  };

  std::istream &operator>>(std::istream &in, SeparatorIO &&dest);
  std::istream &operator>>(std::istream &in, LabelIO &&dest);
}
#endif
