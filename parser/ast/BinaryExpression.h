#ifndef KALEIDO_PARSER_BINARYEXPRESSION_H
#define KALEIDO_PARSER_BINARYEXPRESSION_H
#include "TreeNode.h"
namespace kaleido::ast {
    class TreeNode;
    class BinaryExpression : public TreeNode {
    public:
        BinaryExpression(std::unique_ptr<TreeNode> leftChild, std::unique_ptr<TreeNode> rightChild);
        TreeNode &leftChild();
        const TreeNode &leftChild() const;
        TreeNode &rightChild();
        const TreeNode &rightChild() const;
        char opCode() const;
    protected:
        char mOpCode;
        std::unique_ptr<TreeNode> mLeftChild;
        std::unique_ptr<TreeNode> mRightChild;
    };
}
#endif //KALEIDO_PARSER_BINARYEXPRESSION_H
