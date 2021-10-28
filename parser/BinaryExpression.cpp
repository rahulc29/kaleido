#include "BinaryExpression.h"
kaleido::ast::TreeNode &kaleido::ast::BinaryExpression::leftChild() {
    return *mLeftChild;
}
const kaleido::ast::TreeNode &kaleido::ast::BinaryExpression::leftChild() const {
    return *mLeftChild;
}
kaleido::ast::TreeNode &kaleido::ast::BinaryExpression::rightChild() {
    return *mRightChild;
}
const kaleido::ast::TreeNode &kaleido::ast::BinaryExpression::rightChild() const {
    return *mRightChild;
}
