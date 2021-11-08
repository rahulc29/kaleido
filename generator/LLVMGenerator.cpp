#include "LLVMGenerator.h"
#include <llvm/IR/Constants.h>
#include <iostream>
using llvm::ConstantFP;
Value *kaleido::gen::LLVMGenerator::generate(const Literal &literal) {
    return nullptr;
}
Value *kaleido::gen::LLVMGenerator::generate(const Variable &variable) {
    return nullptr;
}
Value *kaleido::gen::LLVMGenerator::generate(const Addition &addition) {
    return nullptr;
}
Value *kaleido::gen::LLVMGenerator::generate(const Division &division) {
    return nullptr;
}
Value *kaleido::gen::LLVMGenerator::generate(const kaleido::ast::Function &function) {
    return nullptr;
}
Value *kaleido::gen::LLVMGenerator::generate(const Invocation &invocation) {
    return nullptr;
}
Value *kaleido::gen::LLVMGenerator::generate(const Negation &negation) {
    return nullptr;
}
Value *kaleido::gen::LLVMGenerator::generate(const Subtraction &subtraction) {
    return nullptr;
}
kaleido::gen::LLVMGenerator::LLVMGenerator() : mContext(), mBuilder(mContext), mModule(), mNamedValues() {
}
