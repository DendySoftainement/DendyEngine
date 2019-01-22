#include "PixPhetamine/VulkanSystem/VolkInstance.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// - Standard includes section - ////

//// - External includes section - ////

//// -Foundation includes section- ////
#include "DendyFoundation/DebugTools/DebugStack.h"

//// - Internal includes section - ////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// ---- Namespaces ---- ////
namespace DendyEngine {

   namespace PixPhetamine {

      namespace VulkanSystem {

//// - Defines and macro section - ////

//// - Using namespace shortcuts - ////

//// - Static const init section - ////
   dyUInt CVolkInstance::instancesCount = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Class CVolkInstance
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Internal methods -----                                                                                                     ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//


   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Object oriented methods -----                                                                                              ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   CVolkInstance::CVolkInstance(dyVec<dyString> const& a_supportedExtensionsVec, dyString const& a_programName, dyUInt a_programVersionMajor, dyUInt a_programVersionMinor, dyUInt a_programVersionPatch) {
   DENDYENGINE_CALLSTACK_ENTER;

      m_supportedExtensionsVec = a_supportedExtensionsVec;

#if DENDYENGINE_MODE_DEBUG
      m_supportedExtensionsVec.append( VK_EXT_DEBUG_REPORT_EXTENSION_NAME );
#endif

      // Need vec<string> -> const char* const*
      dyVec<const char*> constCharSupportedExtensionsVec;
      for ( dyUInt i = 0; i < m_supportedExtensionsVec.len( ); ++i ) {
         constCharSupportedExtensionsVec.append( m_supportedExtensionsVec[i].asConstChar( ) );
      }


      VkApplicationInfo vkAppConfiguration = { };
      vkAppConfiguration.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
      vkAppConfiguration.pApplicationName = a_programName.asConstChar( );//"Dendy Engine - Dendy Softainement";
      vkAppConfiguration.applicationVersion = VK_MAKE_VERSION( DENDYENGINE_VERSION_MAJOR, DENDYENGINE_VERSION_MINOR, DENDYENGINE_VERSION_PATCH );
      vkAppConfiguration.pEngineName = "Dendy Engine";
      vkAppConfiguration.engineVersion = VK_MAKE_VERSION( DENDYENGINE_VERSION_MAJOR, DENDYENGINE_VERSION_MINOR, DENDYENGINE_VERSION_PATCH );
      vkAppConfiguration.apiVersion = VK_API_VERSION_1_0;


      VkInstanceCreateInfo vkInstanceConfiguration = { };
      vkInstanceConfiguration.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
      vkInstanceConfiguration.pApplicationInfo = &vkAppConfiguration;
      vkInstanceConfiguration.ppEnabledExtensionNames = constCharSupportedExtensionsVec.data( );
      vkInstanceConfiguration.enabledExtensionCount = static_cast<dyUInt32>( constCharSupportedExtensionsVec.len( ) );


      dyUInt layerProprietiesCount;
      vkEnumerateInstanceLayerProperties( &layerProprietiesCount, nullptr );
      dyVec<VkLayerProperties> layerProrietiesVec( layerProprietiesCount );
      vkEnumerateInstanceLayerProperties( &layerProprietiesCount, layerProrietiesVec.data() );

#if DENDYENGINE_MODE_DEBUG
      for each ( VkLayerProperties layerPropriety in layerProrietiesVec.asStdVector( ) ) {
         printf( "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );
         printf( "                                ACTIVE VULKAN LAYERS:\n" );
         printf( "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );
         
         m_validationLayersVec.append( layerPropriety.layerName );
         printf( " - Layer \"%s\"\n", layerPropriety.layerName );
         printf( "   %s\n", layerPropriety.description );

         printf( "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n" );
         m_validationLayersVec.append( "VK_LAYER_LUNARG_standard_validation" );
      }
#endif

      // Need vec<string> -> const char* const*
      dyVec<const char*> constCharValidationLayersVec;
      for ( dyUInt i = 0; i < m_validationLayersVec.len( ); ++i ) {
         constCharValidationLayersVec.append( m_validationLayersVec[i].asConstChar( ) );
      }

      vkInstanceConfiguration.ppEnabledLayerNames = constCharValidationLayersVec.data( );
      vkInstanceConfiguration.enabledLayerCount = static_cast<dyUInt32>( m_validationLayersVec.len( ) );


      VkResult result = vkCreateInstance( &vkInstanceConfiguration, nullptr, &m_vulkanInstance );

      if ( result != VK_SUCCESS ) {
         DENDYENGINE_CRITICAL_ERROR( "Failed to create a Vulkan instance" );
      }
      
   DENDYENGINE_CALLSTACK_EXIT;
   }
   
   
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Static methods -----                                                                                                       ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//


   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Core methods -----                                                                                                         ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                                                                                                                        ////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      }
   }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
