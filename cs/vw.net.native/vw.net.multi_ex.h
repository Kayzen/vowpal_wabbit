#pragma once

#include "vw.net.native.h"
#include "vw/core/vw.h"

extern "C"
{
  API VW980::multi_ex* CreateMultiEx();
  API void DeleteMultiEx(VW980::multi_ex* multi_ex);

  API void MultiExAddExample(VW980::multi_ex* multi_ex, VW980::example* ex);
}
