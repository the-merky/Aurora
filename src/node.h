#include "position.h"
#include <cstddef>
#include <vector>
namespace Aurora {
struct Node {
  Position position;
  std::vector<Node> children;
};
} // namespace Aurora
