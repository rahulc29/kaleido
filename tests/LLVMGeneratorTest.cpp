#include "generator/LLVMGenerator.h"
#include <gtest/gtest.h>
#include <llvm/Support/raw_ostream.h>
using namespace kaleido::gen;
using namespace kaleido::ast;
TEST(LLVMGeneratorTest, BinaryExpressionTest) {
    auto generator = Generator::generator();
    auto function = std::make_unique<Function>(
        std::make_unique<Prototype>(
            "",
            std::vector<std::string>()
        ),
        std::make_unique<Addition>(
            std::make_unique<Literal>(-1), std::make_unique<Literal>(1)
        ));
    auto irFunc = function->generate(*generator);
    // output to stdout
    irFunc->print(llvm::outs());
    std::cout << std::endl;
}