#ifndef LEXER_H_
#define LEXER_H_

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>


class Lexer
{
public:
    Lexer() {}
    Lexer(const std::string& input) : input_(input) {}

    void setInput(const std::string& input) { input_ = input; }

    const std::vector<std::string>& getTokens();
private:
    std::string input_;
    std::vector<std::string> tokens_;

};


#endif  // LEXER_H_