#include "Addition.h"
#include <utility>
kaleido::ast::Addition::Addition(std::shared_ptr<TreeNode> leftChild, std::shared_ptr<TreeNode> rightChild)
    : BinaryExpression(std::move(leftChild), std::move(rightChild)) {
    mOpCode = '+';
}
