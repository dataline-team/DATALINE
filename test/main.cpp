#include "gtest/gtest.h"
 #include "ConsoleTest.h"


int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}