/*
    A simple program that computes the square root of a number
*/

#include <cmath>
#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    const double inputValue = atof(argv[1]);

    // calculate square root
    const double outputValue = sqrt(inputValue);
    std::cout << "The square root of " << inputValue;
    std::cout << " is " << outputValue << std::endl;

    return 0;
}
