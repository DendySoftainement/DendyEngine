
#include <iostream>
#include <windows.h> 

#include "DendyFoundation/Types.h"
#include "DendyFoundation/DebugTools/DebugStack.h"
#include "DendyFoundation/DebugTools/Timer.h"
#include "PixPhetamine/WindowHandle/GLFWWindowHandle.h"
#include "PixPhetamine/WindowHandle/WindowHandleInterface.h"


using namespace DendyEngine;
//using namespace DendyEngine::DendyFoundation::CustomTypes;

int main( int argc, char** argv ) {

   setbuf( stdout, NULL );


   DendyFoundation::DebugTools::CTimer performanceTimer;
   performanceTimer.reset( );


   printf( "Performance timer: elapsed nanoseconds: %llu, ms: %llu\n", performanceTimer.getElapsedNanoseconds( ), performanceTimer.getElapsedMiliseconds( ) );


   PixPhetamine::WindowHandle::UGLFWWindowHandle* windowSystemManager = new PixPhetamine::WindowHandle::UGLFWWindowHandle( );
   PixPhetamine::WindowHandle::UGLFWWindowHandle::SVulkanReadyWindow mainWindow, secondWindow, thirdWindow;
   PixPhetamine::WindowHandle::UGLFWWindowHandle::SConfiguration mainWindowConfig;
   mainWindowConfig.without_borders = true;
   mainWindowConfig.caption = "This is the main window";
   mainWindow = windowSystemManager->openWindow( );


   secondWindow = windowSystemManager->openWindow( mainWindowConfig );
   thirdWindow = windowSystemManager->openWindow( mainWindowConfig );

   dyUInt64 elapsedSecondsLastTime = 0;

   while ( windowSystemManager->isCloseTriggered( mainWindow ) == false ) {
      windowSystemManager->gatherInputs( );
      //Sleep( 1000 );
   }

   windowSystemManager->closeWindow( mainWindow );

   //Sleep(30000);
   DENDYENGINE_CALLSTACK_EXIT;
   return EXIT_SUCCESS;
}
