#include "gtest/gtest.h"
// #include "sometest.cpp"


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}