
#include <iostream>
#include <windows.h> 

#include "DendyFoundation/Types.h"
#include "DendyFoundation/DebugTools/DebugStack.h"
#include "VolkPhetamine/WindowHandle/GLFWWindowHandle.h"
#include "VolkPhetamine/WindowHandle/WindowHandleInterface.h"


using namespace DendyEngine;
//using namespace DendyEngine::DendyFoundation::CustomTypes;

int main( int argc, char** argv ) {
   DENDYENGINE_CALLSTACK_ENTER;
      DENDYENGINE_LOG("ONE");
   DENDYENGINE_CALLSTACK_EXIT;

   DENDYENGINE_CALLSTACK_ENTER;
      DENDYENGINE_LOG("TWO");
      DENDYENGINE_CALLSTACK_ENTER;
         DENDYENGINE_LOG("THREE");
      //DENDYENGINE_CALLSTACK_EXIT;

   dyString myString = "Hello world";
   printf("%s\n", myString.asConstChar());

   //DENDYENGINE_CRITICAL_ERROR("This is an error");


   VolkPhetamine::WindowHandle::UGLFWWindowHandle* windowSystemManager = new VolkPhetamine::WindowHandle::UGLFWWindowHandle();
   VolkPhetamine::WindowHandle::UGLFWWindowHandle::SVulkanReadyWindow mainWindow;
   VolkPhetamine::WindowHandle::UGLFWWindowHandle::Configuration mainWindowConfig;
   mainWindowConfig.without_borders = true;
   mainWindowConfig.caption = "This is the main window";
   mainWindow = windowSystemManager->openWindow( );

   VolkPhetamine::WindowHandle::UGLFWWindowHandle::SVulkanReadyWindow secondWindow;
   secondWindow = windowSystemManager->openWindow( mainWindowConfig );

   VolkPhetamine::WindowHandle::UGLFWWindowHandle::SVulkanReadyWindow thirdWindow;
   thirdWindow = windowSystemManager->openWindow( mainWindowConfig );


   while (windowSystemManager->isCloseTriggered(mainWindow) == false) {
      windowSystemManager->gatherInputs();
   }

   windowSystemManager->closeWindow( mainWindow );

   //Sleep(30000);
   DENDYENGINE_CALLSTACK_EXIT;
   return EXIT_SUCCESS;
}
