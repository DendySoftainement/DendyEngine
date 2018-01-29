
#include <iostream>

#include "DendyFoundation/Types.h"
#include "DendyFoundation/DebugTools/DebugStack.h"

using namespace DendyEngine;
//using namespace DendyEngine::DendyFoundation;

int main( int argc, char** argv ) {

   DENDYENGINE_CALLSTACK_ENTER;

   dyString myString = __FUNCTION__;

   DENDYENGINE_CALLSTACK_ENTER;

   std::cout << myString << std::endl;

   DENDYENGINE_CRITICAL_ERROR("This sis an error");

   return EXIT_SUCCESS;
}
