#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <iostream>


class Console
{
public:
    Console() = default;
    ~Console() = default;

    static bool nextCommand(const std::string& command);
    static bool pathIsCorrect(const std::string& path);

    static void createDB();
    static bool uploadDB(const std::string& path);

private:

};


#endif  // CONSOLE_H_