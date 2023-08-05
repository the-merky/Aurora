#include "node.h"
namespace Aurora {
class SearchTree {
public:
  Node *Root;
  SearchTree(Position *RootPosition) { Root->Position = RootPosition; }
};
}; // namespace Aurora
   // namespace Aurora
