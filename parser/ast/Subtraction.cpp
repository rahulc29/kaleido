#include "Subtraction.h"
#include <utility>
kaleido::ast::Subtraction::Subtraction(std::unique_ptr<TreeNode> leftChild, std::unique_ptr<TreeNode> rightChild)
    : BinaryExpression(std::move(leftChild), std::move(rightChild)) {
    mOpCode = '-';
}
