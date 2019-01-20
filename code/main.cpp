
#include <iostream>
#include <windows.h> 

#include "DendyFoundation/Types.h"
#include "DendyFoundation/DebugTools/DebugStack.h"
#include "DendyFoundation/DebugTools/Timer.h"
#include "VolkPhetamine/WindowHandle/GLFWWindowHandle.h"
#include "VolkPhetamine/WindowHandle/WindowHandleInterface.h"


using namespace DendyEngine;
//using namespace DendyEngine::DendyFoundation::CustomTypes;

int main( int argc, char** argv ) {
   DENDYENGINE_CALLSTACK_ENTER;
   DENDYENGINE_LOG( "ONE" );
   DENDYENGINE_CALLSTACK_EXIT;

   DENDYENGINE_CALLSTACK_ENTER;
   DENDYENGINE_LOG( "TWO" );
   DENDYENGINE_CALLSTACK_ENTER;
   DENDYENGINE_LOG( "THREE" );
//DENDYENGINE_CALLSTACK_EXIT;

   DendyFoundation::DebugTools::CTimer performanceTimer;
   performanceTimer.reset( );

   dyString myString = "Hello world";
   printf( "%s\n", myString.asConstChar( ) );

   //DENDYENGINE_CRITICAL_ERROR("This is an error");

   printf( "Performance timer: elapsed nanoseconds: %llu, ms: %llu\n", performanceTimer.getElapsedNanoseconds( ), performanceTimer.getElapsedMiliseconds( ) );


   VolkPhetamine::WindowHandle::UGLFWWindowHandle* windowSystemManager = new VolkPhetamine::WindowHandle::UGLFWWindowHandle( );
   VolkPhetamine::WindowHandle::UGLFWWindowHandle::SVulkanReadyWindow mainWindow, secondWindow, thirdWindow;
   VolkPhetamine::WindowHandle::UGLFWWindowHandle::SConfiguration mainWindowConfig;
   mainWindowConfig.without_borders = true;
   mainWindowConfig.caption = "This is the main window";
   mainWindow = windowSystemManager->openWindow( );

   printf( "Performance timer: elapsed nanoseconds: %llu, ms: %llu\n", performanceTimer.getElapsedNanoseconds( ), performanceTimer.getElapsedMiliseconds( ) );

   secondWindow = windowSystemManager->openWindow( mainWindowConfig );
   thirdWindow = windowSystemManager->openWindow( mainWindowConfig );

   printf( "Performance timer: elapsed nanoseconds: %llu, ms: %llu\n", performanceTimer.getElapsedNanoseconds( ), performanceTimer.getElapsedMiliseconds( ) );

   dyUInt64 elapsedSecondsLastTime = 0;

   while ( windowSystemManager->isCloseTriggered( mainWindow ) == false ) {
      windowSystemManager->gatherInputs( );
      //Sleep( 1000 );
      
      if ( elapsedSecondsLastTime != performanceTimer.getElapsedSeconds( ) ) {
         elapsedSecondsLastTime = performanceTimer.getElapsedSeconds( );
         printf( "Performance timer: elapsed nanoseconds: %llu, ms: %llu\n", performanceTimer.getElapsedNanoseconds( ), performanceTimer.getElapsedMiliseconds( ) );
         printf( "Performance timer: elapsed nanoseconds: %llu, ms: %llu\n", performanceTimer.getElapsedNanoseconds( ), performanceTimer.getElapsedMiliseconds( ) );
      }
   }

   windowSystemManager->closeWindow( mainWindow );

   //Sleep(30000);
   DENDYENGINE_CALLSTACK_EXIT;
   return EXIT_SUCCESS;
}
