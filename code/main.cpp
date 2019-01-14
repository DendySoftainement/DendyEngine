
#include <iostream>
#include <windows.h> 

#include "DendyFoundation/Types.h"
#include "DendyFoundation/DebugTools/DebugStack.h"
#include "VolkPhetamine/WindowHandle/GLFWWindowHandle.h"

using namespace DendyEngine;
//using namespace DendyEngine::DendyFoundation;

int main( int argc, char** argv ) {

   DENDYENGINE_CALLSTACK_ENTER;

   dyString myString = __FUNCTION__;

   DENDYENGINE_CALLSTACK_ENTER;

   std::cout << myString << std::endl;

   DENDYENGINE_CRITICAL_ERROR("This is an error");

//   Sleep(1000);

   VolkPhetamine::WindowHandle::UGLFWWindowHandle* windowSystemManager = new VolkPhetamine::WindowHandle::UGLFWWindowHandle();
   VolkPhetamine::WindowHandle::UGLFWWindowHandle::SVulkanReadyWindow mainWindow;
   mainWindow = windowSystemManager->openWindow( 800,600 );

   while (windowSystemManager->isCloseTriggered( mainWindow ) == false) {
      windowSystemManager->gatherInputs();
   }

   windowSystemManager->closeWindow( mainWindow );

   //Sleep(30000);

   return EXIT_SUCCESS;
}
