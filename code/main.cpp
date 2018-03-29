
#include <iostream>
#include <windows.h> 

#include "DendyFoundation/Types.h"
#include "DendyFoundation/DebugTools/DebugStack.h"
#include "VolkPhetamine/WindowHandle/SDLWindowHandle.h"

using namespace DendyEngine;
//using namespace DendyEngine::DendyFoundation;

int main( int argc, char** argv ) {

   DENDYENGINE_CALLSTACK_ENTER;

   dyString myString = __FUNCTION__;

   DENDYENGINE_CALLSTACK_ENTER;

   std::cout << myString << std::endl;

   DENDYENGINE_CRITICAL_ERROR("This sis an error");

   Sleep(3000);

   VolkPhetamine::WindowHandle::USDLWindowHandle* windowSystemManager = new VolkPhetamine::WindowHandle::USDLWindowHandle();
   windowSystemManager->openWindow();

   Sleep(3000);

   return EXIT_SUCCESS;
}
