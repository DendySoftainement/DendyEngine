////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////   \file    DebugStack.h
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

//// - Standard includes section - ////
#include <stack>

//// - External includes section - ////

//// -Foundation includes section- ////
#include "DendyFoundation/Types.h"
#include "DendyFoundation/InputOutput/OutputStreamInterface.h"

//// - Internal includes section - ////
#include "DendyFoundation/ExportDLL.h"
//#include "DendyFoundation/DebugTools/CallStack.h"

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
      #define _DENDYENGINE_CURRENT_FUNCTION _DENDYENGINE_DISPLAY_VALUE_HELPER(__PRETTY_FUNCTION__)
   #endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

   // Stack display message (file:function:line)
   #define _DENDYENGINE_LOCATION ( __FILE__ "#" _DENDYENGINE_CURRENT_FUNCTION "#" _DENDYENGINE_DISPLAY_VALUE_HELPER(__LINE__) )

   ////////////////////////////////////////////////////////////
   // The actually public interface for the Debug system !!! //
   ////////////////////////////////////////////////////////////
   #ifdef DENDYENGINE_MODE_DEBUG
      #define DENDYENGINE_CALLSTACK_ENTER         (&DendyEngine::DendyFoundation::DebugTools::UDebugStack::getInstance())->enter(_DENDYENGINE_LOCATION)
      #define DENDYENGINE_CALLSTACK_EXIT          (&DendyEngine::DendyFoundation::DebugTools::UDebugStack::getInstance())->exit()
      #define DENDYENGINE_LOG(message)            (&DendyEngine::DendyFoundation::DebugTools::UDebugStack::getInstance())->log(message,_DENDYENGINE_LOCATION)
      #define DENDYENGINE_ERROR(message)          (&DendyEngine::DendyFoundation::DebugTools::UDebugStack::getInstance())->error(message,_DENDYENGINE_LOCATION)
      #define DENDYENGINE_CRITICAL_ERROR(message) (&DendyEngine::DendyFoundation::DebugTools::UDebugStack::getInstance())->criticalError(message,_DENDYENGINE_LOCATION)
   #else
      #define DENDYENGINE_CALLSTACK_ENTER         (/***/)
      #define DENDYENGINE_CALLSTACK_EXIT          (/***/)
      #define DENDYENGINE_LOG(message)            (/***/)
      #define DENDYENGINE_ERROR(message)          (/***/)
      #define DENDYENGINE_CRITICAL_ERROR(message) (/***/)
   #endif
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

         class API_DLL UDebugStack {

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Enum/Struct/Constants -----                                                                                                   ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
            enum class EEventType {
               BEGIN,
               END,
               LOG,
               ERROR,
               CRITICAL_ERROR
            };

            struct SCodeLocation {
               dyString fileStr;
               dyString functionStr;
               dyString lineStr;
               SCodeLocation( dyString rawLocationStr = "" );
            };

            struct SDebugEvent {
               EEventType    type;
               dyString      messageStr;
               SCodeLocation context;
               SDebugEvent():
                  type( EEventType::LOG ),
                  messageStr( "" ),
                  context( "" )
                     {/***/};
            };

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Members -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
            std::stack<SDebugEvent> m_stack;
            dyInt m_currentLevel;

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Methods -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
         //// ---- Internal ---- ////
            void _dump();
            void _flush();

         public:
         //// ----  Object  ---- ////

         //// ----  Static  ---- ////
            static UDebugStack& getInstance();
            static void destroyInstance();

         //// ---- Accessor ---- ////

         //// ----   Core   ---- ////
            void enter( dyString locationStr );
            void log( dyString messageStr, dyString locationStr );
            void exit();
            void error( dyString messageStr, dyString locationStr );
            void criticalError( dyString messageStr, dyString locationStr );

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
