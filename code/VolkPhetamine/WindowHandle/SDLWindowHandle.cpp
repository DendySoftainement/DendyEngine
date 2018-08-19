#include "VolkPhetamine/WindowHandle/SDLWindowHandle.h"
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

	namespace VolkPhetamine {

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
      if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		  DENDYENGINE_CRITICAL_ERROR("Unable to initialize SDL!");
      }
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
   USDLWindowHandle::SVulkanReadyWindow USDLWindowHandle::openWindow() {
   DENDYENGINE_CALLSTACK_ENTER;
      SVulkanReadyWindow windowBinding;

      // Create our windows centered
      windowBinding.window = SDL_CreateWindow("VolkPhetamine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
      if (windowBinding.window == nullptr) {
         DENDYENGINE_CRITICAL_ERROR("Unable to create the window!");
         exit(666);
      }

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