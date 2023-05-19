#include "vw.net.multi_ex.h"

API VW980::multi_ex* CreateMultiEx() { return new VW980::multi_ex; }

API void DeleteMultiEx(VW980::multi_ex* multi_ex) { delete multi_ex; }

API void MultiExAddExample(VW980::multi_ex* multi_ex, VW980::example* ex) { multi_ex->push_back(ex); }
