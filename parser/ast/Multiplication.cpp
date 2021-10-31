#include "Multiplication.h"
#include <utility>
kaleido::ast::Multiplication::Multiplication(std::shared_ptr<TreeNode> leftChild,
                                             std::shared_ptr<TreeNode> rightChild) :
    BinaryExpression(std::move(leftChild), std::move(rightChild)) {
    mOpCode = '*';
}
