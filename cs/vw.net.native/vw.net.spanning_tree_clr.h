#pragma once

#include "vw.net.native.h"
#include "vw/spanning_tree/spanning_tree.h"

extern "C"
{
  API VW980::SpanningTree* CreateSpanningTree();
  API void DeleteSpanningTree(VW980::SpanningTree* tree);

  API short unsigned int GetSpanningTreeBoundPort(VW980::SpanningTree* tree);
  API void StartSpanningTree(VW980::SpanningTree* tree);
  API void RunSpanningTree(VW980::SpanningTree* tree);
  API void StopSpanningTree(VW980::SpanningTree* tree);
}
