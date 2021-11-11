#include "LLVMGenerator.h"
#include <llvm/IR/Constants.h>
#include <iostream>
using llvm::ConstantFP;
Value *kaleido::gen::LLVMGenerator::generate(const Literal &literal) {
    return ConstantFP::get(mContext, llvm::APFloat(literal.value()));
}
Value *kaleido::gen::LLVMGenerator::generate(const Variable &variable) {
    auto toReturn = mNamedValues[variable.name()];
    if (toReturn == nullptr) {
        std::cerr << "Unknown variable " << variable.name() << std::endl;
        return nullptr;
    }
    return toReturn;
}
Value *kaleido::gen::LLVMGenerator::generate(const Addition &addition) {
    auto sides = generateBinarySides(addition);
    if (sides == EMPTY_PAIR) {
        return nullptr;
    }
    return mBuilder.CreateFAdd(sides.first, sides.second, "addtmp");
}
Value *kaleido::gen::LLVMGenerator::generate(const Division &division) {
    auto sides = generateBinarySides(division);
    if (sides == EMPTY_PAIR) {
        return nullptr;
    }
    return mBuilder.CreateFDiv(sides.first, sides.second, "divtmp");
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
    auto sides = generateBinarySides(subtraction);
    if (sides == EMPTY_PAIR) {
        return nullptr;
    }
    return mBuilder.CreateFSub(sides.first, sides.second, "subtmp");
}
kaleido::gen::LLVMGenerator::LLVMGenerator() : mContext(), mBuilder(mContext), mModule(), mNamedValues() {
}
std::pair<Value *, Value *> kaleido::gen::LLVMGenerator::generateBinarySides(const BinaryExpression &expression) {
    auto lhs = expression.leftChild().generate(*this);
    auto rhs = expression.rightChild().generate(*this);
    if (lhs == nullptr || rhs == nullptr) {
        return EMPTY_PAIR;
    }
    return {lhs, rhs};
}
Value *kaleido::gen::LLVMGenerator::generate(const Multiplication &multiplication) {
    auto sides = generateBinarySides(multiplication);
    if (sides == EMPTY_PAIR) {
        return nullptr;
    }
    return mBuilder.CreateFMul(sides.first, sides.second, "multmp");
}
