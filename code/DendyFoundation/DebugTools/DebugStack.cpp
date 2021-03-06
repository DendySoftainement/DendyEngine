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
   TheDebugStack::SCodeLocation::SCodeLocation( std::string a_rawLocationStr ) {
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

// TheDebugStack
//{
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Internal methods -----                                                                                                     ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void TheDebugStack::_dump() {
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
   void TheDebugStack::_flush( std::stack<SDebugEvent> a_stackToFlush ) {
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
            callStackStr += levelStr + ">> '" + location.functionStr + "'\n";
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
   TheDebugStack& TheDebugStack::getInstance() {
      static TheDebugStack* debugStack = nullptr;
      if (debugStack == nullptr) {
         debugStack = new TheDebugStack();
      }
      return *debugStack;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   // Singleton pattern stuff (destruction)
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void TheDebugStack::destroyInstance() {
      static TheDebugStack* debugStack = &getInstance();
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
   void TheDebugStack::enter( std::string a_locationStr ) {
      SDebugEvent debugEvent;
      debugEvent.type = EEventType::DY_BEGIN;
      debugEvent.messageStr = "";
      debugEvent.context = SCodeLocation( a_locationStr );
      m_stack.push( debugEvent );
   }

   void TheDebugStack::exit() {
      while (!m_stack.empty() && m_stack.top().type != EEventType::DY_BEGIN) {
         m_stack.pop();
      }
      if (!m_stack.empty()) {
         m_stack.pop();
      }
   }

   void TheDebugStack::criticalError( std::string a_messageStr, std::string a_locationStr  ) {
      SDebugEvent debugEvent;
      debugEvent.type = EEventType::DY_CRITICAL_ERROR;
      debugEvent.messageStr = a_messageStr;
      debugEvent.context = SCodeLocation( a_locationStr );
      m_stack.push( debugEvent );

      printf( "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n-=-=-=   CRITICAL ERROR\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );


      printf( "%s\n", a_messageStr.c_str() );

      printf( "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );
      
      printf( "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n-=-=-=   CALLSTACK\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );

      _dump();

      printf( "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );

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
