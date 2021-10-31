#include "Division.h"
#include <utility>
kaleido::ast::Division::Division(std::shared_ptr<TreeNode> leftChild, std::shared_ptr<TreeNode> rightChild)
    : BinaryExpression(std::move(leftChild), std::move(rightChild)) {
    mOpCode = '/';
}
