#include "gtest/gtest.h"
#include "Console.h"


TEST(nextCommand, unknown_command_return)
{
EXPECT_EQ(Console::nextCommand("unknown_command"), false);
}