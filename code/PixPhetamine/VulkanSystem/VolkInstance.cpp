#include "PixPhetamine/VulkanSystem/VolkInstance.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//// - Standard includes section - ////

//// - External includes section - ////

//// -Foundation includes section- ////
#include "DendyFoundation/DebugTools/DebugStack.h"
#include "DendyFoundation/DebugTools/Logger.h"
#include "PixPhetamine/VulkanDebug/VolkDebug.h"

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
   void CVolkInstance::_startGlfw( ) {
   DENDYENGINE_CALLSTACK_ENTER;

      //// glfwInit
      if ( glfwInit( ) == false )
         DY_CRITICAL_ERROR( "Failed to initialize GLFW" );
      DY_LOG( "GLFW System Initialised [ OK ]" );

      //// check is Vulkan is supported
      if ( glfwVulkanSupported( ) == false )
         DY_CRITICAL_ERROR( "This version of GLFW on this machine doesn't support Vulkan" );
      DY_LOG( "GLFW Vulkan support [ OK ]" );

   DENDYENGINE_CALLSTACK_EXIT;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   dyVec<const char*> CVolkInstance::_retrieveSupportedExtensions( ) {
   DENDYENGINE_CALLSTACK_ENTER;

      //// Phase 1 Retrieve supported:

      dyUInt32 supportedExtensionCount;
      // Apparently don't need to free this thing, since glfw will do it ;) ((seems logical after all))
      const char** pSupportedExtensionsConstChar = glfwGetRequiredInstanceExtensions( &supportedExtensionCount );


      // Display fancy sign with supported extensions
      DY_LOG_SIGN( "SUPPORTED VULKAN EXTENSIONS" );
      for ( dyUInt i = 0; i < supportedExtensionCount; i++ ) {
         m_supportedExtensionNamesVec.append( pSupportedExtensionsConstChar[i] );
         dyString LogMessage = dyString::format( "//// - Extension '%s'", pSupportedExtensionsConstChar[i] );
         DY_LOG( LogMessage );
      }
      DY_LOG_SEPARATION_LINE( );
      

      //// Phase 2 Verify and remove not supoorted (and crash if required):
      //// PS: for the moment all are required!!!

      dyVec<const char*> actuallyActiveNamesVec;

      for ( dyString& extensionToActivate : m_activeExtensionNamesVec.asIterable( ) ) {
         if ( m_supportedExtensionNamesVec.find( extensionToActivate ) == false ) {
            dyString ErrorMessage = dyString::format( "Extension '%s' for Vulkan unavailable on this support!", extensionToActivate.asConstChar( ) );
            DY_CRITICAL_ERROR( ErrorMessage );
         }
         actuallyActiveNamesVec.append( extensionToActivate.asConstChar( ) );
      }

   DENDYENGINE_CALLSTACK_EXIT;
      return actuallyActiveNamesVec;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   dyVec<const char*> CVolkInstance::_retrieveSupportedValidationLayers( ) {
   DENDYENGINE_CALLSTACK_ENTER;
      
      //// Phase 1 Retrieve supported:

      // Get supported validation layers on the current system
      dyUInt layerProprietiesCount;
      vkEnumerateInstanceLayerProperties( &layerProprietiesCount, nullptr );
      dyVec<VkLayerProperties> layerProrietiesVec( layerProprietiesCount );
      vkEnumerateInstanceLayerProperties( &layerProprietiesCount, layerProrietiesVec.data( ) );
         
      // Display fancy sign with layers
      DY_LOG_SIGN( "ENABLED VULKAN LAYERS" );
      for each ( VkLayerProperties layerPropriety in layerProrietiesVec.asIterable( ) ) {
         m_supportedValidationLayerNamesVec.append( layerPropriety.layerName );
         dyString LogMessage = dyString::format( "//// - Layer '%s'", layerPropriety.layerName );
         DY_LOG( LogMessage );
         LogMessage = dyString::format( "////    -> %s", layerPropriety.description );
         DY_LOG( LogMessage );
      }
      DY_LOG_SEPARATION_LINE( );

      //for ( int i = 0; i < 10000000; i++ )
      //   dyString::allocFormatedConstChar( "%s\n", dyString::allocConstCharFancySeparationLine( ) );

      //// Phase 2 Verify and remove not supoorted (and crash if required):
      //// PS: for the moment all are required!!!

      dyVec<const char*> actuallyActiveNamesVec;

      for ( dyString& layerToActivate : m_activeValidationLayerNamesVec.asIterable( ) ) {
         if ( m_supportedValidationLayerNamesVec.find( layerToActivate ) == false ) {
            dyString ErrorMessage = dyString::format( "Layer '%s' for Vulkan unavailable on this support!", layerToActivate.asConstChar( ) );
            DY_CRITICAL_ERROR( ErrorMessage );
         }
         actuallyActiveNamesVec.append( layerToActivate.asConstChar( ) );
      }

   DENDYENGINE_CALLSTACK_EXIT;
      return actuallyActiveNamesVec;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void CVolkInstance::_setCallbackDebugLogger( ) {

   }

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Object oriented methods -----                                                                                              ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   CVolkInstance::CVolkInstance(dyString const& a_programName, dyUInt a_programVersionMajor, dyUInt a_programVersionMinor, dyUInt a_programVersionPatch) {
   DENDYENGINE_CALLSTACK_ENTER;

      if ( instancesCount == 0 ) {
         _startGlfw( );
      }

      //// REQUIRED EXTENSIONS
      //
      // Required to draw on screen
      m_activeExtensionNamesVec.append( VK_KHR_SURFACE_EXTENSION_NAME );
      //
      // Enables debug reports
      m_activeExtensionNamesVec.append( VK_EXT_DEBUG_REPORT_EXTENSION_NAME );
      //
      //// -------------------

      //// REQUIRED VALIDATION LAYERS
      //
      // Build in standard validation
      /* 
      #if DENDYENGINE_MODE_DEBUG
         m_activeValidationLayerNamesVec.append( "VK_LAYER_LUNARG_standard_validation" );
      #endif
         */
      //
      //// -------------------


      dyVec<const char*> actuallyActiveExtensionNamesVec = _retrieveSupportedExtensions( );
      dyVec<const char*> actuallyActiveLayerNamesVec = _retrieveSupportedValidationLayers( );



      VkApplicationInfo vkAppConfiguration = { };
      vkAppConfiguration.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
      vkAppConfiguration.pApplicationName = a_programName.asConstChar( );
      vkAppConfiguration.applicationVersion = VK_MAKE_VERSION( DENDYENGINE_VERSION_MAJOR, DENDYENGINE_VERSION_MINOR, DENDYENGINE_VERSION_PATCH );
      vkAppConfiguration.pEngineName = "Dendy Engine";
      vkAppConfiguration.engineVersion = VK_MAKE_VERSION( DENDYENGINE_VERSION_MAJOR, DENDYENGINE_VERSION_MINOR, DENDYENGINE_VERSION_PATCH );
      vkAppConfiguration.apiVersion = VK_API_VERSION_1_0;


      VkInstanceCreateInfo vkInstanceConfiguration = { };
      vkInstanceConfiguration.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
      vkInstanceConfiguration.pApplicationInfo = &vkAppConfiguration;
      vkInstanceConfiguration.ppEnabledExtensionNames = actuallyActiveExtensionNamesVec.data( );
      vkInstanceConfiguration.enabledExtensionCount = static_cast<dyUInt32>( actuallyActiveExtensionNamesVec.len( ) );
      vkInstanceConfiguration.ppEnabledLayerNames = actuallyActiveLayerNamesVec.data( );
      vkInstanceConfiguration.enabledLayerCount = static_cast<dyUInt32>( actuallyActiveLayerNamesVec.len( ) );



      //// SURFACE KHR CREATION
      VkResult result = vkCreateInstance( &vkInstanceConfiguration, nullptr, &m_vulkanInstance );
      //// --------------------


      if ( result != VK_SUCCESS ) {
         DY_CRITICAL_ERROR( "Failed to create a Vulkan instance" );
      }
      
#if DENDYENGINE_MODE_DEBUG
      VkDebugReportCallbackCreateInfoEXT vkDebugInfo;
      vkDebugInfo.flags = VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_DEBUG_BIT_EXT |
         VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_ERROR_BIT_EXT |
         VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_FLAG_BITS_MAX_ENUM_EXT |
         VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
         VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
         VkDebugReportFlagBitsEXT::VK_DEBUG_REPORT_WARNING_BIT_EXT;
      vkDebugInfo.pfnCallback = DendyEngine::PixPhetamine::VulkanDebug::debugCallback;

      //vkCreateDebugReportCallbackEXT( m_vulkanInstance, &vkDebugInfo, nullptr, &m_callback );
#endif



      //// KHR Surface (destroy previous)
      //if ( m_surface != VkSurfaceKHR( ) )
      //   vkDestroySurfaceKHR( m_vulkanInstance, m_surface, nullptr );

      //// WINDOW CREATION
      glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
      glfwWindowHint( GLFW_DECORATED, GLFW_TRUE );
      m_glfwWindowHandle = glfwCreateWindow( 640, 480, a_programName.asConstChar( ), nullptr, nullptr );
      //// --------------------

      //// SURFACE KHR CREATION
      result = glfwCreateWindowSurface( m_vulkanInstance, m_glfwWindowHandle, nullptr, &m_surface );
      //// --------------------

      instancesCount++;

   DENDYENGINE_CALLSTACK_EXIT;
   }

   CVolkInstance::~CVolkInstance( ) {
   DENDYENGINE_CALLSTACK_ENTER;

      if ( m_callback != VK_NULL_HANDLE ) {
         //auto func = (PFN_vkDestroyDebugReportCallbackEXT)getProcAddr( "vkDestroyDebugReportCallbackEXT" );
         //func( m_instance, mCallback, nullptr );
      }

      vkDestroyInstance( m_vulkanInstance, nullptr );

      //glfwDestroyWindow( window );

      instancesCount--;
      if ( instancesCount == 0 )
         glfwTerminate( );

      
      //vkDestroySurfaceKHR( m_surface );
      //destroy( );

      
   DENDYENGINE_CALLSTACK_ENTER;
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
