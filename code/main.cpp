
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

   setvbuf( stdout, NULL, _IONBF, 0 );


   DendyFoundation::DebugTools::CTimer performanceTimer;
   performanceTimer.reset( );

   printf( dyString::allocFormatedConstChar("%s %s", "Heyyou", "out there on your own") );

   DENDYENGINE_LOG( "ONE" );
   DENDYENGINE_LOG( dyString::allocFormatedConstChar("%s", "IsThe lonliest number") );


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



   printf( "Sizeof dyUInt: %llu\n", sizeof( dyUInt ) );
   printf( "Sizeof dyUInt16: %llu\n", sizeof( dyUInt16 ) );
   printf( "Sizeof dyUInt64: %llu\n", sizeof( dyUInt64 ) );
   printf( "Sizeof dyInt: %llu\n", sizeof( dyInt ) );
   printf( "Sizeof dyInt16: %llu\n", sizeof( dyInt16 ) );
   printf( "Sizeof dyInt64: %llu\n", sizeof( dyInt64 ) );
   printf( "Sizeof dyFloat: %llu\n", sizeof( dyFloat ) );
   printf( "Sizeof dyFloat64: %llu\n", sizeof( dyFloat64 ) );

   struct SFakeStruct {
      dyInt one{ 34 };
      dyInt two{ 42 };
      dyInt three{ 42 };
   };

   struct SFATFakeStruct {
      dyFloat64 one[8000000];
   };


   printf( "Sizeof SFakeStruct: %llu\n", sizeof( SFakeStruct) );
   printf( "Sizeof pSFakeStruct: %llu\n", sizeof( SFakeStruct* ) );
   printf( "Sizeof SFATFakeStruct: %llu\n", sizeof( SFATFakeStruct ) );
   printf( "Sizeof SFATFakeStruct: %llu\n", sizeof( SFATFakeStruct* ) );





   




   while ( windowSystemManager->isCloseTriggered( mainWindow ) == false ) {
      windowSystemManager->gatherInputs( );
      //Sleep( 1000 );
   }

   windowSystemManager->closeWindow( mainWindow );

   //Sleep(30000);
   DENDYENGINE_CALLSTACK_EXIT;
   return EXIT_SUCCESS;
}
