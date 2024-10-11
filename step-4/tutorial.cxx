/*
    A simple program that computes the square root of a number
*/

#include <iostream>

#include "TutorialConfig.h"

#ifdef USE_MYMATH
#  include "MathFunctions.h"
#else
#  include <cmath>
#endif

int main(int argc, char *argv[])
{
    // report version
    std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR << "."
              << Tutorial_VERSION_MINOR << std::endl;

    if (argc < 2)
    {
        // print usage
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
        return 1;
    }

    // const double inputValue = atof(argv[1]);
    const double inputValue = std::stod(argv[1]); // Specifying C++ standards

    // calculate square root
#ifdef USE_MYMATH
    using namespace mathfunctions;
    const double outputValue = mathfunctions::sqrt(inputValue);
#else
    const double outputValue = sqrt(inputValue);
#endif
    std::cout << "The square root of " << inputValue;
    std::cout << " is " << outputValue << std::endl;

    return 0;
}
