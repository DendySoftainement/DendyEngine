////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////   \file    AllocatorInterface.h
////   \author  Daniel Huc aka Dendy from Tiago Costa
////   \date    January 2019
////   -----------------------------
////   \brief   None
////   ---------------------------------------------------------------------------------------------------------------------------------------------------------
////   \details All custom allocators must implement this interface, tho memory will be malloced and dispatched by the Memory Manager ;)
////            https://www.gamedev.net/articles/programming/general-and-gameplay-programming/c-custom-memory-allocation-r3010
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//// - Standard includes section - ////
#include <new>
#include <functional>

//// - External includes section - ////

//// -Foundation includes section- ////
#include "DendyFoundation/Types.h"

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

      namespace MemoryManagment {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Class IAllocator
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         class IAllocator {

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Enum/Struct/Constants -----                                                                                                   ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         public:
            static const dyUInt8 DEFAULT_ALIGNEMENT{ 8 };

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Members -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         protected:
            size_t m_size{ 0 };
            size_t m_allocatedSize{ 0 };
            size_t m_allocationsCount{ 0 };

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Methods -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
         //// ---- Internal ---- ////
            

         public:
         //// ----  Object  ---- ////
            IAllocator( size_t a_size ): m_size( a_size ) { /***/ };
            virtual ~IAllocator( ) { /***/ };
			
		   //// ----  Static  ---- ////

         protected:
         //// ----  Forbid  ---- ////
            IAllocator( IAllocator const& );
            IAllocator& operator=( IAllocator& );

		   public:
         //// ----   Core   ---- ////
            virtual void* alloc( size_t a_size, dyUInt8 a_alignement = DEFAULT_ALIGNEMENT ) = 0;
            virtual void free( void* a_pointer ) = 0;

            size_t getSize( ) const { return m_size; }
            size_t getAllocatedSize( ) const { return m_allocatedSize; }
            size_t getNbAllocations( ) const { return m_allocationsCount; }

         };

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                        ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         //// Helpful functions:
         template <class T, class... Args>
         T* dyNew( IAllocator& a_allocator, Args&&... args );

         template<class T>
         void dyDelete( IAllocator& a_allocator, T* object );

         template<class T>
         T* dyNewArray( IAllocator& a_allocator, size_t length );

         template<class T>
         T* dyNewArrayWithoutConstructor( IAllocator& a_allocator, size_t length );

         template<class T>
         void dyDeleteArray( IAllocator& a_allocator, T* array );

         template<class T>
         void dyDeleteArrayWithoutDestructor( IAllocator& a_allocator, T* array );

#include "AllocatorInterface.inl"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                        ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      }
   }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
