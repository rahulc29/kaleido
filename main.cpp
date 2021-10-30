#include <gtest/gtest.h>

using testing::Eq;
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}