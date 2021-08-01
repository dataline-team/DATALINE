#include "gtest/gtest.h"
#include <vector>
#include "Lexer.h"


TEST(getTokens, simple_command)
{
    std::string input = "tables";
    Lexer lexer(input);
    
    EXPECT_EQ(*lexer.getTokens().begin(), input);
}


TEST(getTokens, complex_command)
{
    std::string input = " next       test command ";
    std::vector<std::string> tokens = {"next", "test", "command"};

    Lexer lexer(input);

    EXPECT_EQ(lexer.getTokens(), tokens);
}


TEST(setInput, use_setter)
{
    std::string input = "one more command";
    std::vector<std::string> tokens = {"one", "more", "command"};

    Lexer lexer;
    lexer.setInput(input);

    EXPECT_EQ(lexer.getTokens(), tokens);
}