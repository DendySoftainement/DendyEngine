////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////   \file    Timer.h
////   \author  Daniel Huc aka Dendy
////   \date    January 2019
////   -----------------------------
////   \brief   None
////   ---------------------------------------------------------------------------------------------------------------------------------------------------------
////   \details None
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//// - Standard includes section - ////
#include <chrono>

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

      namespace DebugTools {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Class CTimer
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         class CTimer {

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Enum/Struct/Constants -----                                                                                                   ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         public:
			

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Members -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
            std::chrono::time_point<std::chrono::steady_clock> m_startTicks; ///< Initial ticks
            std::chrono::duration<double> m_elapsedTicks; ///< Cumuled ticks between starts and pauses
            dyBool m_isPaused{ false }; ///< Status in pause
            dyBool m_isHighPerformanceClockIsSteady{ false }; ///< Depending on the platform, use highest precision clock if it is consistent or basic consistent clock

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Methods -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
         //// ---- Internal ---- ////
            
            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Updates the elapsed ticks: adds to the elapsed ticksthe duration between now and previous ticks using the consistent clock. 
            /// And updates the start tick value.
            //----------------------------------------------------------------------------------------------------------------------------------------//
            void _updateElapsedTicks( );
            
            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Sets start ticks to current tick value using the consistent clock.
            //----------------------------------------------------------------------------------------------------------------------------------------//
            void _updateStartTicks( );

         public:
         //// ----  Object  ---- ////
            CTimer( ): m_isHighPerformanceClockIsSteady( std::chrono::high_resolution_clock::is_steady ) { reset( ); }
						
         //// ----   Core   ---- ////
			   
            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Returns the elapsed time in microseconds since last Timer() OR Timer.reset().
            /// Takes into account Timer.pause() and Timer.resume() -> elapsed time ;)
            /// If the timer is in pause: returns the elapsed time since it was paused!
            //----------------------------------------------------------------------------------------------------------------------------------------//
            dyUInt64 getElapsedMicroseconds( );
            
            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Returns the elapsed time in nanoseconds since last Timer() OR Timer.reset().
            /// Takes into account Timer.pause() and Timer.resume() -> elapsed time ;)
            /// If the timer is in pause: returns the elapsed time since it was paused!
            //----------------------------------------------------------------------------------------------------------------------------------------//
            dyUInt64 getElapsedNanoseconds( );
            
            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Returns the elapsed time in milliseconds since last Timer() OR Timer.reset().
            /// Takes into account Timer.pause() and Timer.resume() -> elapsed time ;)
            /// If the timer is in pause: returns the elapsed time since it was paused!
            //----------------------------------------------------------------------------------------------------------------------------------------//
            dyUInt64 getElapsedMiliseconds( );
            
            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Returns the elapsed time in seconds since last Timer() OR Timer.reset().
            /// Takes into account Timer.pause() and Timer.resume() -> elapsed time ;)
            /// If the timer is in pause: returns the elapsed time since it was paused!
            //----------------------------------------------------------------------------------------------------------------------------------------//
            dyUInt64 getElapsedSeconds( );
            
            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Returns the elapsed time in minutes since last Timer() OR Timer.reset().
            /// Takes into account Timer.pause() and Timer.resume() -> elapsed time ;)
            /// If the timer is in pause: returns the elapsed time since it was paused!
            //----------------------------------------------------------------------------------------------------------------------------------------//
            dyUInt64 getElapsedMinutes( );
            
            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Returns the elapsed time in hours since last Timer() OR Timer.reset().
            /// Takes into account Timer.pause() and Timer.resume() -> elapsed time ;)
            /// If the timer is in pause: returns the elapsed time since it was paused!
            //----------------------------------------------------------------------------------------------------------------------------------------//
            dyUInt64 getElapsedHours( );

            dyBool isPaused( ) const { return m_isPaused; }

            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Resets the timer (elapsed time -> near 0) and starts it if it was paused!
            //----------------------------------------------------------------------------------------------------------------------------------------//
            void reset( );
            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Resume the timer if it was paused!
            //----------------------------------------------------------------------------------------------------------------------------------------//
            void resume( );
            //----------------------------------------------------------------------------------------------------------------------------------------//
            /// Pauses the timer. This means that the elapsed time will not be updated: to unpause call Timer.resume() or Timer.reset()
            //----------------------------------------------------------------------------------------------------------------------------------------//
            void pause( );
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