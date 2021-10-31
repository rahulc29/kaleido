#ifndef KALEIDO_PARSER_MULTIPLICATION_H
#define KALEIDO_PARSER_MULTIPLICATION_H
#include "BinaryExpression.h"
namespace kaleido::ast {
    class Multiplication : public BinaryExpression {
    public:
        Multiplication(std::shared_ptr<TreeNode> leftChild, std::shared_ptr<TreeNode> rightChild);
    };
}
#endif //KALEIDO_PARSER_MULTIPLICATION_H
