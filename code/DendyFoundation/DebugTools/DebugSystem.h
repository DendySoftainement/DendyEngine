////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////   \file    DebugSystem.h
////   \author  Daniel Huc aka Dendy
////   \date    December 2017
////   -----------------------------
////   \brief   None
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

#ifdef DENDYENGINE_MODE_DEBUG

   //// - Standard includes section - ////
   #include <stack>

   //// - External includes section - ////

   //// -Foundation includes section- ////
   #include "DendyFoundation/Types.h"
   #include "DendyFoundation/DesignPatterns/SingletonPattern.h"
   #include "DendyFoundation/InputOutput/OutputStreamInterface.h"

   //// - Internal includes section - ////
   #include "DendyFoundation/DebugTools/CallStack.h"

   //// - Defines and macro section - ////
   #ifndef _DENDYENGINE_DEFINEGUARD_DEBUG_SYSTEM

      // Double macro to display the number of the line instead of "__LINE__"
      #define _DENDYENGINE_DISPLAY_VALUE_HELPER_SECOND_PASS(value) #value
      #define _DENDYENGINE_DISPLAY_VALUE_HELPER(value) _DENDYENGINE_DISPLAY_VALUE_HELPER_SECOND_PASS(value)

      // Define _DENDYENGINE_CURRENT_FUNCTION macro to call __func__ define for c++11 gcc or __FUNCTION__ defined for MSVC!
   //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Specific to 'WINDOWS/LINUX' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      #ifdef DENDYENGINE_PLATFORM_WINDOWS
         #define _DENDYENGINE_CURRENT_FUNCTION __FUNCTION__
      #endif
      #ifdef DENDYENGINE_PLATFORM_LINUX
         #define _DENDYENGINE_CURRENT_FUNCTION _DENDYENGINE_DISPLAY_VALUE_HELPER(__func__)
      #endif
   //>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

      // Stack display message (file:function:line)
      #define _DENDYENGINE_LOCATION ( __FILE__ ":" _DENDYENGINE_CURRENT_FUNCTION ":" _DENDYENGINE_DISPLAY_VALUE_HELPER(__LINE__) )

      ////////////////////////////////////////////////////////////
      // The actually public interface for the Debug system !!! //
      ////////////////////////////////////////////////////////////
      #define DENDYENGINE_CALLSTACK_ENTER         (&DendyEngine::DendyFoundation::DebugTools::UDebugSystem::getInstance())->enter(_DENDYENGINE_LOCATION)
      #define DENDYENGINE_CALLSTACK_EXIT          (&DendyEngine::DendyFoundation::DebugTools::UDebugSystem::getInstance())->exit()
      #define DENDYENGINE_LOG(message)            (&DendyEngine::DendyFoundation::DebugTools::UDebugSystem::getInstance())->log(message,_DENDYENGINE_LOCATION)
      #define DENDYENGINE_ERROR(message)          (&DendyEngine::DendyFoundation::DebugTools::UDebugSystem::getInstance())->error(message)
      #define DENDYENGINE_CRITICAL_ERROR(message) (&DendyEngine::DendyFoundation::DebugTools::UDebugSystem::getInstance())->criticalError(message)
      ////////////////////////////////////////////////////////////

      #define _DENDYENGINE_DEFINEGUARD_DEBUG_SYSTEM
   #endif

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //// ---- Namespaces ---- ////
   namespace DendyEngine {

      namespace DendyFoundation {

         namespace DebugTools {

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////   Class CDebugMessage                                                                                                                               ////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            class UDebugSystem : public ASingleton {

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //// ---- Enum/Struct/Constants -----                                                                                                   ////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            private:
               enum EEventType {
                  LOCATION,
                  LOG,
                  ERROR,
                  CRITICAL_ERROR
               }

               struct SCodeLocation {
                  dyString fileStr;
                  dyString functionStr;
                  dyString lineStr;
                  void parseRawMacroLocationString( dyString rawLocationStr );
               }

               struct SDebugEvent {
                  EEventType    type;
                  dyString      messageStr;
                  SCodeLocation context;
               }

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //// ---- Members -----                                                                                                                 ////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            private:
               std::stack<EMessageType>

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //// ---- Methods -----                                                                                                                 ////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            private:
            //// ---- Internal ---- ////
               void _doStuff();

            public:
            //// ----  Object  ---- ////
               CDebugMessage();
               ~CDebugMessage();

            //// ----  Static  ---- ////

            //// ---- Accessor ---- ////

            //// ----   Core   ---- ////
               // \brief     None
               // \details   None
               #define DENDYENGINE_CALLSTACK_ENTER         (&DendyEngine::DendyFoundation::DebugTools::UDebugSystem::getInstance())->enter(__CONTEXT__)
               #define DENDYENGINE_LOG(message)            (&DendyEngine::DendyFoundation::DebugTools::UDebugSystem::getInstance())->log(message,__CONTEXT__)
               #define DENDYENGINE_CALLSTACK_EXIT          (&DendyEngine::DendyFoundation::DebugTools::UDebugSystem::getInstance())->exit()
               #define DENDYENGINE_CRITICAL_ERROR(message) (&DendyEngine::DendyFoundation::DebugTools::UDebugSystem::getInstance())->criticalError(message)
               #define DENDYENGINE_ERROR(message)          (&DendyEngine::DendyFoundation::DebugTools::UDebugSystem::getInstance())->error(message)

            };

   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////                                                                                                                                                     ////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         }
      }
   }
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#endif