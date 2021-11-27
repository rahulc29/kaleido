#ifndef KALEIDO_PARSER_AST_FUNCTION_H
#define KALEIDO_PARSER_AST_FUNCTION_H
#include "TreeNode.h"
#include "Prototype.h"
namespace kaleido::ast {
    class Function : public TreeNode {
    public:
        Function(std::unique_ptr<Prototype> prototype, std::unique_ptr<TreeNode> body);
        const Prototype &prototype() const;
        const TreeNode &body() const;
        LLVMFunction *generate(Generator &generator) {
            return generator.generate(*this);
        }
    private:
        std::unique_ptr<Prototype> mPrototype;
        // only one expression function bodies for now 😤
        std::unique_ptr<TreeNode> mBody;
    };
}
#endif //KALEIDO_PARSER_AST_FUNCTION_H
