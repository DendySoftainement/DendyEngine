
#include <iostream>

#include "DendyFoundation/Types.h"
#include "DendyFoundation/DebugTools/DebugStack.h"

using namespace DendyEngine;
//using namespace DendyEngine::DendyFoundation;

int main( int argc, char** argv ) {

   DENDYENGINE_CALLSTACK_ENTER;

   dyString myString = "Hello world";

   std::cout << myString << std::endl;
   return EXIT_SUCCESS;
}
