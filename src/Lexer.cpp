#include "Lexer.h"


const std::vector<std::string>& Lexer::getTokens()
{
    std::istringstream iss(input_);
    copy(std::istream_iterator<std::string>(iss),
         std::istream_iterator<std::string>(),
         std::back_inserter(tokens_));

    return tokens_;
}