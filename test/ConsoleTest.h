#include "gtest/gtest.h"
#include "Console.h"


TEST(nextCommand, unknown_command_no_throw)
{
    Console console;

    EXPECT_NO_THROW(console.processCommand("unknown_command"));
}
