#include <iostream>
#include "Console.h"


int main(int argc, char **argv)
{
    Console console;
    std::string command;

    while (true)
    {
        std::cout << "dataline$ ";
        std::cin >> command;

        if (command == "exit" || command == "EXIT")
        {
            break;
        }

        console.processCommand(command);
    }

    return 0;
}
