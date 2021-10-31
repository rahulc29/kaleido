#include "Subtraction.h"
#include <utility>
kaleido::ast::Subtraction::Subtraction(std::shared_ptr<TreeNode> leftChild, std::shared_ptr<TreeNode> rightChild)
    : BinaryExpression(std::move(leftChild), std::move(rightChild)) {
    mOpCode = '-';
}
