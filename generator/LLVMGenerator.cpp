#include "LLVMGenerator.h"
#include <llvm/IR/Constants.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Verifier.h>
#include <iostream>
using llvm::ConstantFP;
using llvm::Type;
using llvm::BasicBlock;
using llvm::FunctionType;
Value *kaleido::gen::LLVMGenerator::generate(const Literal &literal) {
    // get value from LLVM's constant pool
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
LLVMFunction *kaleido::gen::LLVMGenerator::generate(const Prototype &prototype) {
    // a vector of the types of the function's parameters
    // def foo(a b c) 
    // params = [typeof(a), typeof(b), typeof(c)]
    // => params = [double, double, double]
    std::vector<Type *> params(prototype.args().size(), Type::getDoubleTy(mContext));
    // typeof(foo) = {
    //    "returnType": double,
    //    "params": params,
    //    "vararg": false
    // }
    auto funcType = FunctionType::get(Type::getDoubleTy(mContext), params, false);
    auto function = LLVMFunction::Create(
        funcType, LLVMFunction::ExternalLinkage, prototype.name(), mModule.get());
    auto i = 0;
    const auto &args = prototype.args();
    for (auto &arg: function->args()) {
        arg.setName(args[i++]);
    }
    return function;
}
LLVMFunction *kaleido::gen::LLVMGenerator::generate(const Function &function) {
    // check if function is already declared
    auto func = mModule->getFunction(function.prototype().name());
    if (func == nullptr) {
        func = function.prototype().generate(*this);
    }
    if (func == nullptr) {
        return nullptr;
    }
    // if function is already declared and defined
    if (!func->empty()) {
        std::cerr << "Cannot redefine function " << function.prototype().name() << '\n';
        return nullptr;
    }
    // only one block right now
    // will need more after the addition of control flow
    auto block = BasicBlock::Create(mContext, "entry", func);
    mBuilder.SetInsertPoint(block);
    mNamedValues.clear();
    for (auto &arg: func->args()) {
        mNamedValues[arg.getName()] = &arg;
    }
    auto body = function.body().generate(*this);
    if (body != nullptr) {
        mBuilder.CreateRet(body);
        llvm::verifyFunction(*func);
        return func;
    }
    // if body could not be formed; remove function from module
    func->eraseFromParent();
    return nullptr;
}
Value *kaleido::gen::LLVMGenerator::generate(const Invocation &invocation) {
    const auto &functionName = invocation.toInvoke();
    auto toCall = mModule->getFunction(functionName);
    if (toCall == nullptr) {
        std::cerr << "No function " << functionName << " found\n";
        return nullptr;
    }
    // argument list size should be same
    auto expected = toCall->arg_size();
    auto actual = invocation.args().size();
    if (expected != actual) {
        std::cerr << "Incorrect no of arguments for function " << functionName << '\n';
        std::cerr << "Expected " << expected << " but got " << actual << '\n';
    }
    // the actual arguments to pass to the function
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
    // To be implemented
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
// Utility function to generate both sides of a binary expression
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