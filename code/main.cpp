
#include <iostream>

#include "DendyFoundation/Types.h"
#include "DendyFoundation/DebugTools/DebugSystem.h"

using namespace DendyEngine;

int main( int argc, char** argv ) {

   dyString myString = "Hello world";

   std::cout << myString << std::endl;
   return EXIT_SUCCESS;
}
