#include "ErrorMessage.hpp"
#include "StreamGuard.hpp"

namespace sukacheva
{
  void ErrorMessage(std::ostream& out)
  {
    StreamGuard StreamGuard(out);
    out << "<INVALID COMMAND>\n";
  }
}
