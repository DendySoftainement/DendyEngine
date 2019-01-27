////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////   \file    DyString.h
////   \author  Daniel Huc aka Dendy
////   \date    January 2019
////   -----------------------------
////   \brief   None
////   ---------------------------------------------------------------------------------------------------------------------------------------------------------
////   \details Largely inspired by fbstring 
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
#include <string>
#include <atomic>
#include <iosfwd>
#include <limits>
#include <stdexcept>
#include <type_traits>

#include <algorithm>
#include <cassert>
#include <cstring>
#include <utility>

//// - External includes section - ////

//// -Foundation includes section- ////

//// - Internal includes section - ////

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

   namespace DendyFoundation {

      namespace CustomTypes {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Class CMyClass                                                                                                                                       ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         class dyString {

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Enum/Struct/Constants -----                                                                                                   ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         public:


         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Members -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
            std::string m_memory;

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Methods -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
         //// ---- Internal ---- ////

         public:
         //// ----  Object  ---- ////
            dyString( );

            dyString( dyString const& a_string );
            dyString( const char* a_string );
            dyString( std::string a_string );

            void operator+=( dyString const& a_string );
            void operator+=( const char* a_string );
            void operator+=( int_fast32_t a_integer );
            void operator+=( float a_float );
            void operator+=( bool a_boolean );


            /*bool operator>( dyString const& a_string ) const;
            bool operator<( dyString const& a_string ) const;
            bool operator>=( dyString const& a_string ) const;
            bool operator<=( dyString const& a_string ) const;*/

            dyString& operator+( dyString const& a_string );
            dyString& operator+( const char* a_string );
            dyString& operator+( int_fast32_t a_integer );
            dyString& operator+( float a_float );
            dyString& operator+( bool a_boolean );

            bool operator==( dyString const& a_string );
            bool operator==( const char* a_string );
            operator bool( ) const;

         private:
         //// ----  Forbid  ---- ////

         public:
         //// ----  Static  ---- ////
            static const char* allocConstCharFancyPanel( dyString a_string );
            static const char* allocConstCharFancySeparationLine( );
            static const char* allocFormatedConstChar( const char* a_format, ... );

         //// ---- Accessor ---- ////

         //// ----   Core   ---- ////
            /// Like the c_str() method, returns char string data (ending with '\0')
            const char* asConstChar( ) const {
               return m_memory.data( );
            }

            /// Like the c_str() method, returns char string data (ending with '\0')
            const char* asAllocatedConstChar( ) const {
               char* allocatedResult = new char[m_memory.length( ) + 1];
               strcpy( allocatedResult, m_memory.c_str( ) ); // this puts a '\0' at the end ;)
               return allocatedResult;
            }

            /// Acces to the buffer pointer (WRITABLE)
            char* asCharMutablePtr( ) {
               return const_cast<char*>( m_memory.data( ) );
            }

            std::string asStdString( ) const { 
               return m_memory;
            }

            uint_fast16_t len( ) const { 
               return static_cast<uint_fast16_t>( m_memory.length( ) );
            }

            bool const& find( dyString const& a_toFind ) const;
            bool const& find( const char* a_toFind ) const;

            void replace( dyString const& a_toFind, dyString const& a_newValue );
            void replace( const char* a_toFind, const char* a_newValue );

            /// \brief Eis phokoowin scheit gonna work as a python substring too [2:-1]
            dyString substring( int_fast16_t a_begin, int_fast16_t a_end ) const;

            dyString split( dyString const& a_separator ) {
               /***/
            }

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

