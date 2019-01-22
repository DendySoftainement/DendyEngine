////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////   \file    Types.h
////   \author  Daniel Huc aka Dendy
////   \date    December 2017
////   -----------------------------
////   \brief   Aliases for types
////   ---------------------------------------------------------------------------------------------------------------------------------------------------------
////   \details Using standard types may cause confusion in memory representation (depending on system) \n
////            Plus if some mathematical functions will be changed in the future, we want to avoid multiple modifications!
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// FIXME: -
////        -
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
//// TODO:  -
////        -
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//// - Standard includes section - ////
#include <memory>
#include <map>
#include "DendyFoundation/CustomTypes/DyString.h"
#include "DendyFoundation/CustomTypes/DyVec.h"
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Specific to 'WINDOWS' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#ifdef DENDYENGINE_PLATFORM_WINDOWS
   #include <stdint.h> ///< Using [basictype]_fast[minsize]_t
#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//// - External includes section - ////
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>

class DendyEngine::DendyFoundation::CustomTypes::dyString;

template <class T>//, class Allocator = std::allocator<T>>
class DendyEngine::DendyFoundation::CustomTypes::dyVec;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// ---- Namespaces ---- ////
namespace DendyEngine {

   /* Substitution Aliases */
   using dyBool = bool;             /// 1b boolean GL_TRUE or GL_FALSE
   using dyInt16 = int_fast16_t;    /// Signed 16b integer [-32 768,  32 767] at least! (can be more if faster on system)
   using dyUInt16 = uint_fast16_t;  /// Unsigned 16b integer [0,  65 535] at least! (can be more if faster on system)
   using dyInt = int_fast32_t;      /// Signed 32b integer [-2 147 483 648,  2 147 483 647] at least! (can be more if faster on system)
   using dyInt32 = int32_t;         /// Signed 32b integer [-2 147 483 648,  2 147 483 647] STRICT (usefull for third party libs)
   using dyUInt32 = uint32_t;       /// Unsigned 32b integer [0,  4 294 967 295] STRICT (usefull for third party libs)
   using dyUInt = uint_fast32_t;    /// Unsigned 32b integer [0,  4 294 967 295] at least! (can be more if faster on system)
   using dyInt64 = int_fast64_t;    /// Signed 64b integer [-9 223 372 036 854 775 808,  9 223 372 036 854 775 807] at least! (can be more if faster on system)
   using dyUInt64 = uint_fast64_t;  /// Unsigned 64b integer [0,  18 446 744 073 709 551 615] at least! (can be more if faster on system)
   using dyFloat = float;           /// Signed 32b floating-point
   using dyFloat64 = double;        /// Signed 64b floating-point

   using dyString = DendyEngine::DendyFoundation::CustomTypes::dyString;
   //typedef DendyEngine::DendyFoundation::CustomTypes::dyString dyString;

   template<class T, class U>
   using dyMap = std::map<T, U>;
   template<typename  T>
   using dyVec = DendyEngine::DendyFoundation::CustomTypes::dyVec<T>;
   //using dyVec = std::vector<T>;
   //typedef DendyEngine::DendyFoundation::CustomTypes::dyVec<T> dyVec;
   template<class T, class U>
   using dyPair = std::pair<T,U>;
   template<class T>
   using dyUniquePtr = std::unique_ptr<T>;
   template<class T>
   using dySharedPtr = std::shared_ptr<T>;

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Specific to 'LINUX' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#ifdef DENDYENGINE_PLATFORM_LINUX
   template<typename T, typename... Args>
   std::unique_ptr<T> createUniquePtr(Args&&... args) {
       return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
   }
#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Specific to 'WINDOWS' <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#ifdef DENDYENGINE_PLATFORM_WINDOWS
   template<typename T, typename... Args>
   std::unique_ptr<T> createUniquePtr(Args&&... args) {
       return std::make_unique<T>(std::forward<Args>(args)...);
   }
#endif
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
