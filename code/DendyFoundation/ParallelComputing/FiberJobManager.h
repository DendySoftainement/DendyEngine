////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////   \file    FiberJobManager.h
////   \author  Daniel Huc aka Dendy
////   \date    January 2019
////   -----------------------------
////   \brief   Fiber manager (soft threads) for parallel job execution
////   ---------------------------------------------------------------------------------------------------------------------------------------------------------
////   \details 
////            - A Thread is the execution unit
////            - A Job executes within the context of a Fiber
////            - Atomic counters for synch
////            See Naughty dog engine (GDC talk 2015)
////            They have like 160 fibers (128 * 64Ko Stack && 32 * 512Ko Stack), all game logics and rendering buffer managing are executed in jobs...
//// -----------------------------------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

//// - Standard includes section - ////

//// - External includes section - ////

//// -Foundation includes section- ////
#include "DendyFoundation/Types.h"

//// - Internal includes section - ////
#include "DendyFoundation/ParallelComputing/ThreadManager.h"

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

      namespace ParallelComputing {

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Class CFiberJobManager
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

         class CFiberJobManager {

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Enum/Struct/Constants -----                                                                                                   ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         public:
         struct SJob { //tm_jobdecl_t
            void( *task )( void *data );
            void *data;
         };

         struct SAtomicCounter; //tm_atomic_counter_t

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Members -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
			

         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         //// ---- Methods -----                                                                                                                 ////
         ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         private:
         //// ---- Internal ---- ////
            

         public:
         //// ----  Object  ---- ////
            // struct tm_job_manager_i *tm_create_job_manager(struct tm_os_thread_i *thread_api, uint32_t num_worker_threads, uint32_t num_fibers, uint32_t fiber_stack_size);
            CFiberJobManager( dyUInt a_workingThreadCount, dyUInt a_fiberCount, dyUInt a_fiberStackSize );
            // void tm_destroy_job_manager(struct tm_os_thread_i *thread_api, struct tm_job_manager_i *job_manager);
            ~CFiberJobManager( );
			
		    //// ----  Static  ---- ////

         private:
         //// ----  Forbid  ---- ////
			
		 public:
         //// ----   Core   ---- ////
         // void (*run_jobs)(struct tm_jobdecl_t *jobs, uint32_t num_jobs, tm_atomic_counter_t **counter);
         void( *runAsParallelJobs )( struct SJob *a_jobs, dyUInt a_jobCount, SAtomicCounter **a_counter );
         // void (*wait_for_counter)(tm_atomic_counter_t *counter, uint32_t value);
         void( *waitForFinishedJobsCount )( SAtomicCounter *a_counter, dyUInt a_counterValue );

         // Use waitForAllJobsFinished when running jobs from a thread not part of the fiber system -- discuss: should this even be allowed?
         //void( *waitForAllJobsFinished )( SAtomicCounter *counter, dyUInt value );

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
