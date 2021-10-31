#ifndef KALEIDO_PARSER_ADDITION_H
#define KALEIDO_PARSER_ADDITION_H
#include "BinaryExpression.h"
namespace kaleido::ast {
    class Addition : public BinaryExpression {
    public:
        Addition(std::shared_ptr<TreeNode> leftChild, std::shared_ptr<TreeNode> rightChild);
    };
}
#endif //KALEIDO_PARSER_ADDITION_H
