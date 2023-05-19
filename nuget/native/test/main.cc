#include "vw/config/options_cli.h"
#include "vw/core/memory.h"
#include "vw/core/vw.h"

int main()
{
  auto workspace = VW980::initialize(VW980::make_unique<VW980::config::options_cli>(std::vector<std::string>{"--quiet"}));
  workspace->finish();
}
