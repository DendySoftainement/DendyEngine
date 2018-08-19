////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////   \file    SceneRender.h
////   \author  Daniel Huc aka Dendy
////   \date    August 2018
////   -----------------------------
////   \brief   How the scene rendering is done
////   ---------------------------------------------------------------------------------------------------------------------------------------------------------
////   \details None
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// FIXME: -
////        -
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
//// TODO:  - FINISH
////        - TEST
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//// - Standard includes section - ////

//// - External includes section - ////
#define GLFW_INCLUDE_VULKAN
#include <glfw3.h>
//// -Foundation includes section- ////
#include "DendyFoundation/Types.h"

//// - Internal includes section - ////
#include "VolkPhetamine/WindowHandle/WindowHandleInterface.h"

//// - Defines and macro section - ////

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Specific to 'WINDOWS/LINUX' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#ifdef DENDYENGINE_PLATFORM_WINDOWS

#endif
#ifdef DENDYENGINE_PLATFORM_LINUX

#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// ---- Namespaces ---- ////
namespace DendyEngine {

   namespace VolkPhetamine {

      namespace SceneRendering {

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ////   Class CMyClass                                                                                                                                       ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         class __declspec(dllexport) CSceneRender {

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //// ---- Enum/Struct/Constants -----                                                                                                   ////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         public:


            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //// ---- Members -----                                                                                                                 ////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
            VkSurfaceKHR m_frame;


            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //// ---- Methods -----                                                                                                                 ////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
            //// ---- Internal ---- ////
            void _initVulkan();

         public:
            //// ----  Object  ---- ////
            UGLFWWindowHandle();
            ~UGLFWWindowHandle();

         private:
            //// ----  Forbid  ---- ////

         public:
            //// ----  Static  ---- ////

            //// ---- Accessor ---- ////

            //// ----   Core   ---- ////
            // \brief     None
            // \details   None
            SVulkanReadyWindow openWindow();
            void closeWindow(SVulkanReadyWindow window);

         };

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         ////                                                                                                                                                        ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      }
   }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
