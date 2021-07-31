#include "gtest/gtest.h"
#include "Console.h"


TEST(processCommand, unknown_command_throw)
{
    Console console;

    EXPECT_THROW(console.processCommand("unknown_command"), std::runtime_error);
}
