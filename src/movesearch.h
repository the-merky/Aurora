#include "eval.h"
namespace Aurora {
namespace MoveSearch {
inline void search(int depth, int currentDepth, Node Node) {
  if (currentDepth > depth) {
    return;
  }
  MoveGen::updateAttackedSquares(&Node.position);
  MoveGen::generate(&Node.position);
  for (int i = 0; i < Node.position.moves.size();) {
    Node.children.push_back({});
    makeMove(Node.position.moves[i], Node.position,
             Node.children.back().position);
    search(depth, currentDepth + 1, Node.children[Node.children.size() - 1]);
    std::cout << Node.children.size() << std::endl;
    i++;
  }
}
} // namespace MoveSearch
} // namespace Aurora
