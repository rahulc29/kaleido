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
    const auto &functionName = invocation.toInvoke();
    auto toCall = mModule->getFunction(functionName);
    if (toCall == nullptr) {
        std::cerr << "No function " << functionName << " found\n";
        return nullptr;
    }
    auto expected = toCall->arg_size();
    auto actual = invocation.args().size();
    if (expected != actual) {
        std::cerr << "Incorrect no of arguments for function " << functionName << '\n';
        std::cerr << "Expected " << expected << " but got " << actual << '\n';
    }
    std::vector<Value *> argsForCall;
    for (const auto &arg: invocation.args()) {
        argsForCall.push_back(arg->generate(*this));
        if (argsForCall.back() == nullptr) {
            // previous argument added was null => something went wrong
            return nullptr;
        }
    }
    return mBuilder.CreateCall(toCall, argsForCall, "calltmp");
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
