#ifndef KALEIDO_GENERATOR_GENERATOR_H
#define KALEIDO_GENERATOR_GENERATOR_H
#include "LLVMGenerator.h"
#include "parser/ast/Literal.h"
#include "parser/ast/Variable.h"
#include "parser/ast/Addition.h"
#include "parser/ast/Division.h"
#include "parser/ast/Function.h"
#include "parser/ast/Invocation.h"
#include "parser/ast/Multiplication.h"
#include "parser/ast/Negation.h"
#include "parser/ast/Prototype.h"
#include "parser/ast/Subtraction.h"
#include <llvm/IR/Value.h>
using llvm::Value;
typedef lllvm::Function LLVMFunction;
using namespace kaleido::ast;
namespace kaleido::gen {
    // common interface to implement to write a generator given an AST
    class Generator {
    public:
        // factory method to get default implementation of generator
        static Generator *generator() {
            static LLVMGenerator theGenerator;
            return dynamic_cast<Generator *>(&theGenerator);
        }
        virtual Value *generate(const Literal &literal) = 0;
        virtual Value *generate(const Variable &variable) = 0;
        virtual Value *generate(const Addition &addition) = 0;
        virtual Value *generate(const Division &division) = 0;
        virtual LLVMFunction *generate(const Function &function) = 0;
        virtual LLVMFunction *generate(const Prototype &prototype) = 0;
        virtual Value *generate(const Invocation &invocation) = 0;
        virtual Value *generate(const Negation &negation) = 0;
        virtual Value *generate(const Subtraction &subtraction) = 0;
        virtual Value *generate(const Multiplication &multiplication) = 0;
    };
}
#endif //KALEIDO_GENERATOR_GENERATOR_H
