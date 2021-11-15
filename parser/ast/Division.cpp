#include "Division.h"
#include <utility>
kaleido::ast::Division::Division(std::unique_ptr<TreeNode> leftChild, std::unique_ptr<TreeNode> rightChild)
    : BinaryExpression(std::move(leftChild), std::move(rightChild)) {
    mOpCode = '/';
}
