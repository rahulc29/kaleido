#ifndef KALEIDO_GENERATOR_LLVMGENERATOR_H
#define KALEIDO_GENERATOR_LLVMGENERATOR_H
#include "Generator.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include "parser/ast/BinaryExpression.h"
#include <memory>
#include <parser/ast/Multiplication.h>
using llvm::LLVMContext;
using llvm::IRBuilder;
using llvm::Module;
namespace kaleido::gen {
    class LLVMGenerator : public Generator {
    public:
        LLVMGenerator();
        Value *generate(const Literal &literal) override;
        Value *generate(const Variable &variable) override;
        Value *generate(const Addition &addition) override;
        Value *generate(const Division &division) override;
        LLVMFunction *generate(const Function &function) override;
        LLVMFunction *generate(const Prototype &prototype) override;
        Value *generate(const Invocation &invocation) override;
        Value *generate(const Negation &negation) override;
        Value *generate(const Subtraction &subtraction) override;
        Value *generate(const Multiplication &multiplication) override;
    protected:
        LLVMContext mContext;
        IRBuilder<> mBuilder;
        std::unique_ptr<Module> mModule;
        std::unordered_map<std::string, Value *> mNamedValues;
        std::pair<Value *, Value *> generateBinarySides(const BinaryExpression &expression);
        static std::pair<Value *, Value *> EMPTY_PAIR = {};
    };
}
#endif //KALEIDO_GENERATOR_LLVMGENERATOR_H
