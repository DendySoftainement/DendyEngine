#include "PixPhetamine/WindowHandle/SDLWindowHandle.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// - Standard includes section - ////

//// - External includes section - ////

//// -Foundation includes section- ////
#include "DendyFoundation/DebugTools/DebugStack.h"

//// - Internal includes section - ////

//// ---- Namespaces ---- ////
namespace DendyEngine {

	namespace PixPhetamine {

		namespace WindowHandle {

//// - Defines and macro section - ////


//// - Using namespace shortcuts - ////
//using namespace DendyEngine::DendyFoundation::Types;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// USDLWindowHandle
//{
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Internal methods -----                                                                                                     ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void USDLWindowHandle::_initVulkan() {
   DENDYENGINE_CALLSTACK_ENTER;
      
   DENDYENGINE_CALLSTACK_EXIT;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Object oriented methods -----                                                                                              ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   USDLWindowHandle::USDLWindowHandle() {
   DENDYENGINE_CALLSTACK_ENTER;
      // Initialize SDL's Video subsystem
      /*if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		  DY_CRITICAL_ERROR("Unable to initialize SDL!");
      }*/
	DENDYENGINE_CALLSTACK_EXIT;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   USDLWindowHandle::~USDLWindowHandle() {

   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Static methods -----                                                                                                       ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//


   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Acessor methods -----                                                                                                      ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//


   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Core methods -----                                                                                                         ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   USDLWindowHandle::SVulkanReadyWindow USDLWindowHandle::openWindow(dyUInt16 a_width=800, dyUInt16 a_height=600) {
   DENDYENGINE_CALLSTACK_ENTER;
      SVulkanReadyWindow windowBinding;

      // Create our windows centered
      /*windowBinding.window = SDL_CreateWindow("PixPhetamine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, a_width, a_height, SDL_WINDOW_SHOWN);
      if (windowBinding.window == nullptr) {
         DY_CRITICAL_ERROR("Unable to create the window!");
         exit(666);
      }*/

      return windowBinding;
   DENDYENGINE_CALLSTACK_EXIT;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void USDLWindowHandle::closeWindow(SVulkanReadyWindow a_window) {
      // TODO
   }

//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                        ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	  }
   }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////