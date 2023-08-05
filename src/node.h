#include "node-id.h"
#include "position.h"
#include <vector>
namespace Aurora {
struct Node {
  Position *Position;
  std::vector<Node> children;
  Id Id;
  void addPosition(class Position Position) { *this->Position = Position; }
};
} // namespace Aurora
