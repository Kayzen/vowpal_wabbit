#include "vw/common/vw_exception.h"
#include "vw/config/options_cli.h"
#include "vw/core/memory.h"
#include "vw/core/vw.h"

#include <memory>

int main(int argc, char** argv)
{
  try
  {
    auto vw = VW980::initialize(VW980::make_unique<VW980::config::options_cli>(std::vector<std::string>(argv + 1, argv + argc)));
  }
  catch (...)
  {
    std::exit(1);
  }
  return 0;
}
