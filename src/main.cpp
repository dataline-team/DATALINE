#include <iostream>
#include <algorithm>
#include "Console.h"
#include "boost/program_options.hpp"



namespace po = boost::program_options;

int main(int argc, char **argv)
{
    // process arguments
    po::options_description opt_desc("Allowed options");
    opt_desc.add_options()
            ("help", "produce help message")
            ("create", "create new database")
            ("upload", po::value<std::string>(), "set database path");

    po::variables_map var_map;
    po::store(po::parse_command_line(argc, argv, opt_desc), var_map);

    if (var_map.count("help"))
    {
        std::cout << opt_desc << '\n';
        return 1;
    }

    if (var_map.count("create"))
    {
        Console::createDB();
    }

    if (var_map.count("upload"))
    {
        const std::string& path = var_map["upload"].as<std::string>();
        if (Console::pathIsCorrect(path))
        {
            Console::uploadDB(path);
            std::cout << "Info: Database path was set to " << path << ".\n";
        }
        else
        {
            std::cout << "Error! Database was not found.\n";
            return -1;
        }
    }


    // process command
    std::string command;
    while (true)
    {
        std::cout << "dataline$ ";
        std::cin >> command;

        std::transform(command.begin(), command.end(), command.begin(),
                       [](unsigned char c){ return std::tolower(c);});

        if (command == "exit")
        {
            break;
        }

        Console::nextCommand(command);
    }


    return 0;
}