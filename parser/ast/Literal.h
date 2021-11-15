#ifndef KALEIDO_PARSER_AST_LITERAL_H
#define KALEIDO_PARSER_AST_LITERAL_H
#include "TreeNode.h"
namespace kaleido::ast {
    class Literal : public TreeNode {
    public:
        explicit Literal(double value = 0);
        const double &value() const;
    private:
        double mValue;
    };
}
#endif //KALEIDO_PARSER_AST_LITERAL_H
