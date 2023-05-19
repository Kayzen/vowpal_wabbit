#include "vw.net.spanning_tree_clr.h"

API VW980::SpanningTree* CreateSpanningTree() { return new VW980::SpanningTree; }

API void DeleteSpanningTree(VW980::SpanningTree* tree) { delete tree; }

API short unsigned int GetSpanningTreeBoundPort(VW980::SpanningTree* tree) { return tree->BoundPort(); }

API void StartSpanningTree(VW980::SpanningTree* tree) { tree->Start(); }

API void RunSpanningTree(VW980::SpanningTree* tree) { tree->Run(); }

API void StopSpanningTree(VW980::SpanningTree* tree) { tree->Stop(); }
