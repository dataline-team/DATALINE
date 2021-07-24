#include <iostream>
#include "boost/array.hpp"

int main() 
{
    boost::array<std::string, 2> a {"Hello,", " world!"};  // test boost library

    for (std::string &i: a) {
        std::cout << i;
    }

    std::cout << std::endl;

    return 0;
}
