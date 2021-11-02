#include "Addition.h"
#include <utility>
kaleido::ast::Addition::Addition(std::unique_ptr<TreeNode> leftChild, std::unique_ptr<TreeNode> rightChild)
    : BinaryExpression(std::move(leftChild), std::move(rightChild)) {
    mOpCode = '+';
}
