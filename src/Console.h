#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <iostream>
#include "map"
#include "functional"
#include "vector"


class Console
{
public:
    Console();
    void processCommand(const std::string& command);

private:
    std::map<std::string, std::function<void(std::vector<std::string>)>> commands_;
};


#endif  // CONSOLE_H_
