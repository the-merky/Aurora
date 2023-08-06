#include "position.h"
#include <cstddef>
#include <vector>
namespace Aurora {
struct Node {
  Position *Position;
  std::vector<Node> Children;
};
} // namespace Aurora
