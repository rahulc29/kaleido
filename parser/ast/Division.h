#ifndef KALEIDO_PARSER_DIVISION_H
#define KALEIDO_PARSER_DIVISION_H
#include "BinaryExpression.h"
namespace kaleido::ast {
    class Division : public BinaryExpression {
    public:
        Division(std::shared_ptr<TreeNode> leftChild, std::shared_ptr<TreeNode> rightChild);
    };
}
#endif //KALEIDO_PARSER_DIVISION_H
