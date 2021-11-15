#ifndef KALEIDO_PARSER_TREENODE_H
#define KALEIDO_PARSER_TREENODE_H
#include "generator/Generator.h"
#include <vector>
#include <memory>
#include <llvm/IR/Value.h>
namespace kaleido::ast {
    // superclass of all tree nodes
    // purely virtual non-instantiable class
    class TreeNode {
    public:
        virtual llvm::Value *generate(kaleido::gen::Generator &generator);
    };
}
#endif //KALEIDO_PARSER_TREENODE_H
