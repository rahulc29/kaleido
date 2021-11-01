#ifndef KALEIDO_PARSER_SUBTRACTION_H
#define KALEIDO_PARSER_SUBTRACTION_H
#include "BinaryExpression.h"
namespace kaleido::ast {
    class Subtraction : public BinaryExpression {
    public:
        Subtraction(std::unique_ptr<TreeNode> leftChild, std::unique_ptr<TreeNode> rightChild);
    };
}
#endif //KALEIDO_PARSER_SUBTRACTION_H
