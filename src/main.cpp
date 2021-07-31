#include <iostream>
#include "Console.h"


int main(int argc, char **argv)
{
    std::string command;

    while (true)
    {
        std::cout << "dataline$ ";
        std::cin >> command;

        if (command == "exit" || command == "EXIT")
        {
            break;
        }

        Console console;

        try
        {
            console.processCommand(command);
        }
        catch (std::runtime_error& err)
        {
            std::cout << "error: " << err.what() << '\n';
        }
    }

    return 0;
}
