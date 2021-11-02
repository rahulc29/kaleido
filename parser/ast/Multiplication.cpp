#include "Multiplication.h"
#include <utility>
kaleido::ast::Multiplication::Multiplication(std::unique_ptr<TreeNode> leftChild,
                                             std::unique_ptr<TreeNode> rightChild) :
    BinaryExpression(std::move(leftChild), std::move(rightChild)) {
    mOpCode = '*';
}
