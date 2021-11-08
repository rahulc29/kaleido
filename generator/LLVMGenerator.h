#ifndef KALEIDO_GENERATOR_LLVMGENERATOR_H
#define KALEIDO_GENERATOR_LLVMGENERATOR_H
#include "Generator.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Module.h>
#include <memory>
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
        Value *generate(const Function &function) override;
        Value *generate(const Invocation &invocation) override;
        Value *generate(const Negation &negation) override;
        Value *generate(const Subtraction &subtraction) override;
    protected:
        LLVMContext mContext;
        IRBuilder mBuilder;
        std::unique_ptr<Module> mModule;
        std::map<std::string, Value *> mNamedValues;
    };
}
#endif //KALEIDO_GENERATOR_LLVMGENERATOR_H
