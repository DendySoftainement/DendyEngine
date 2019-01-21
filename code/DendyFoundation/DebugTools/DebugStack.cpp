#include "DendyFoundation/DebugTools/DebugStack.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// - Standard includes section - ////
#include <iostream>
#include <windows.h> 

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
   UDebugStack::SCodeLocation::SCodeLocation( std::string a_rawLocationStr ) {
      if (a_rawLocationStr == "") {
         return;
      }
      std::string infoStr = a_rawLocationStr;
      dyUInt64 pos = infoStr.find("\\code\\");
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
      std::stack<SDebugEvent> revertedStack;
      
      SDebugEvent item;
      while (!m_stack.empty()) {
         item = m_stack.top();
         m_stack.pop();
         revertedStack.push(item);
      }
      _flush( revertedStack );
      m_stack = backupStack;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void UDebugStack::_flush( std::stack<SDebugEvent> a_stackToFlush ) {
      SDebugEvent currentDebug;
      std::string callStackStr;

      dyUInt level = 0;

      // Drop context/messages for display (update backup stack)
      while (!a_stackToFlush.empty()) {
         currentDebug = a_stackToFlush.top();
         if (currentDebug.type == EEventType::DY_BEGIN) {
            level++;
            std::string levelStr = "";
            for (dyUInt i_level=0; i_level<level; i_level++) {
               levelStr += "  ";
            }
            SCodeLocation location = currentDebug.context;
            callStackStr += levelStr + ">> '" + location.functionStr + "' in file '" + location.fileStr + "'[" + location.lineStr + "]\n";
         }

         if (currentDebug.type == EEventType::DY_LOG) {
            std::string levelStr = "";
            for (dyUInt i_level = 0; i_level<level; i_level++) {
               levelStr += "  ";
            }
            SCodeLocation location = currentDebug.context;
            callStackStr += levelStr + "<LOG> In function '"+ location.functionStr +"' in file '" + location.fileStr + "'[" + location.lineStr + "]\n";
            callStackStr += levelStr + "|  " + currentDebug.messageStr + '\n';
         }

         if (currentDebug.type == EEventType::DY_CRITICAL_ERROR) {
            level++;
            std::string levelStr = "";
            for (dyUInt i_level=0; i_level<level; i_level++) {
               levelStr += "  ";
            }
            SCodeLocation location = currentDebug.context;
            callStackStr += levelStr + "<CRITICAL_ERROR> In function '" + location.functionStr + "' in file '" + location.fileStr + "'[" + location.lineStr + "]\n";
            callStackStr += levelStr + "|  " + currentDebug.messageStr + '\n';
         }
         
         a_stackToFlush.pop();
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
   void UDebugStack::enter( std::string a_locationStr ) {
      SDebugEvent debugEvent;
      debugEvent.type = EEventType::DY_BEGIN;
      debugEvent.messageStr = "";
      debugEvent.context = SCodeLocation( a_locationStr );
      m_stack.push( debugEvent );
   }

   void UDebugStack::log( std::string a_messageStr, std::string a_locationStr ) {
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

   void UDebugStack::error( std::string a_messageStr, std::string a_locationStr  ) {
      SDebugEvent debugEvent;
      debugEvent.type = EEventType::DY_ERROR;
      debugEvent.messageStr = a_messageStr;
      debugEvent.context = SCodeLocation( a_locationStr );
      m_stack.push( debugEvent );
   }

   void UDebugStack::criticalError( std::string a_messageStr, std::string a_locationStr  ) {
      SDebugEvent debugEvent;
      debugEvent.type = EEventType::DY_CRITICAL_ERROR;
      debugEvent.messageStr = a_messageStr;
      debugEvent.context = SCodeLocation( a_locationStr );
      m_stack.push( debugEvent );

      printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
      printf("                                CRITICAL ERROR!\n");
      printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
      printf( "%s\n", a_messageStr.c_str() );

      printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
      printf("                                CALL STACK:\n");
      printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
      _dump();
      printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
      printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");

      while ( true )
      {
         Sleep(1000);
      }

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
