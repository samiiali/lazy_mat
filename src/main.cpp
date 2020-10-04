#include <iostream>
#include "matrix.hpp"

int main (int argc, char* argv[])
{
    std::vector<double> a1(5,1.0);
    std::vector<double> a2(10,1.0);
    a1 = a2;
    std::cout << a1.size() << std::endl;

    (void) argc;
    (void) argv;
    return 0;
}
