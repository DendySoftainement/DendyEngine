#include "DendyFoundation/DebugTools/DebugStack.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// - Standard includes section - ////
#include <iostream>

//// - External includes section - ////

//// -Foundation includes section- ////
#include "DendyFoundation/Types.h"

//// - Internal includes section - ////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// ---- Namespaces ---- ////
namespace DendyEngine {

   namespace DendyFoundation {

      namespace DebugTools {

//// - Defines and macro section - ////

//// - Using namespace shortcuts - ////

//// - Static const init section - ////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// SCodeLocation
//{
   UDebugStack::SCodeLocation::SCodeLocation( dyString a_rawLocationStr ) {
      if (a_rawLocationStr == "") {
         return;
      }
      dyString infoStr = a_rawLocationStr;
      dyInt pos = infoStr.find("/code/");
      infoStr = infoStr.substr(pos+6);
      pos = infoStr.find("#");
      this->fileStr = infoStr.substr(0, pos);
      infoStr = infoStr.substr(pos+1);
      pos = infoStr.find("#");
      this->functionStr = infoStr.substr(0, pos);
      infoStr = infoStr.substr(pos+1);
      this->lineStr = infoStr;
   }
//}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                        ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// UDebugStack
//{
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Internal methods -----                                                                                                     ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void UDebugStack::_dump() {
      std::stack<SDebugEvent> backupStack = m_stack;
      _flush();
      m_stack = backupStack;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void UDebugStack::_flush() {
      SDebugEvent currentDebug;
      dyString callStackStr;

      dyUInt level = 0;

      SCodeLocation location = m_stack.top().context;
      callStackStr += "File: " + location.fileStr + " function: " + location.functionStr +  " line: " + location.lineStr + '\n';
      std::cout << callStackStr << std::endl;

      m_stack.pop();

      location = m_stack.top().context;
      callStackStr += "File: " + location.fileStr + " function: " + location.functionStr +  " line: " + location.lineStr + '\n';
      std::cout << callStackStr << std::endl;
      return;


      // Drop context/messages for display (update backup stack)
      while (!m_stack.empty()) {
         currentDebug = m_stack.top();
         if (currentDebug.type == EEventType::DY_BEGIN) {
            level++;
            dyString levelStr = "";
            for (dyUInt i_level=0; i_level<level; level++) {
               levelStr += '\t';
            }
            SCodeLocation location = m_stack.top().context;
            callStackStr += levelStr + ">>[" + location.fileStr + "]::(" + location.lineStr + ")::{" + location.functionStr + '\n';
         }
         if (currentDebug.type == EEventType::DY_CRITICAL_ERROR) {
            level++;
            dyString levelStr = "";
            for (dyUInt i_level=0; i_level<level; level++) {
               levelStr += '\t';
            }
            SCodeLocation location = m_stack.top().context;
            callStackStr += levelStr + ">>[" + location.fileStr + "]::(" + location.lineStr + ")::{" + location.functionStr + '\n';
         }
         m_stack.pop();
      }
      std::cout << callStackStr << std::endl;
   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Static methods -----                                                                                                       ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   // Singleton pattern stuff (unique creation only)
   //----------------------------------------------------------------------------------------------------------------------------------------//
   UDebugStack& UDebugStack::getInstance() {
      static UDebugStack* debugStack = nullptr;
      if (debugStack == nullptr) {
         debugStack = new UDebugStack();
      }
      return *debugStack;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   // Singleton pattern stuff (destruction)
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void UDebugStack::destroyInstance() {
      static UDebugStack* debugStack = &getInstance();
      if (debugStack != nullptr) {
         delete debugStack;
      }
   }


   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Core methods -----                                                                                                         ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void UDebugStack::enter( dyString a_locationStr ) {
      SDebugEvent debugEvent;
      debugEvent.type = EEventType::DY_BEGIN;
      debugEvent.messageStr = "";
      debugEvent.context = SCodeLocation( a_locationStr );
      m_stack.push( debugEvent );
   }

   void UDebugStack::log( dyString a_messageStr, dyString a_locationStr ) {
      SDebugEvent debugEvent;
      debugEvent.type = EEventType::DY_LOG;
      debugEvent.messageStr = a_messageStr;
      debugEvent.context = SCodeLocation( a_locationStr );
      m_stack.push( debugEvent );
   }

   void UDebugStack::exit() {
      while (!m_stack.empty() && m_stack.top().type != EEventType::DY_BEGIN) {
         m_stack.pop();
      }
      if (!m_stack.empty()) {
         m_stack.pop();
      }
   }

   void UDebugStack::error( dyString a_messageStr, dyString a_locationStr  ) {
      SDebugEvent debugEvent;
      debugEvent.type = EEventType::DY_ERROR;
      debugEvent.messageStr = a_messageStr;
      debugEvent.context = SCodeLocation( a_locationStr );
      m_stack.push( debugEvent );
   }

   void UDebugStack::criticalError( dyString a_messageStr, dyString a_locationStr  ) {
      SDebugEvent debugEvent;
      debugEvent.type = EEventType::DY_CRITICAL_ERROR;
      debugEvent.messageStr = a_messageStr;
      debugEvent.context = SCodeLocation( a_locationStr );
      m_stack.push( debugEvent );
      _dump();
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
