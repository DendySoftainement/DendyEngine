#include "PixPhetamine/WindowHandle/GLFWWindowHandle.h"
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

      namespace WindowHandle {

         //// - Defines and macro section - ////

         //// - Using namespace shortcuts - ////

         //// - Static const init section - ////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Internal methods -----                                                                                                     ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
         
   void UGLFWWindowHandle::_createVkInstance( ) {
   DENDYENGINE_CALLSTACK_ENTER;
      VkApplicationInfo vkAppConfiguration = { };
      vkAppConfiguration.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
      vkAppConfiguration.pApplicationName = "Dendy Engine - Dendy Softainement";
      vkAppConfiguration.applicationVersion = VK_MAKE_VERSION( DENDYENGINE_VERSION_MAJOR, DENDYENGINE_VERSION_MINOR, DENDYENGINE_VERSION_PATCH );
      vkAppConfiguration.pEngineName = "PixPhetamine";
      vkAppConfiguration.engineVersion = VK_MAKE_VERSION( VOLKPHETAMINE_VERSION_MAJOR, VOLKPHETAMINE_VERSION_MINOR, VOLKPHETAMINE_VERSION_PATCH );
      vkAppConfiguration.apiVersion = VK_API_VERSION_1_0;


      VkInstanceCreateInfo vkInstanceConfiguration = { };
      vkInstanceConfiguration.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
      vkInstanceConfiguration.pApplicationInfo = &vkAppConfiguration;


      _getGlfwExtensionsForVk( &vkInstanceConfiguration.ppEnabledExtensionNames, vkInstanceConfiguration.enabledExtensionCount );

      
#if DENDYENGINE_MODE_DEBUG
      const char* debugLayers[] = { "VK_LAYER_LUNARG_standard_validation" };
      vkInstanceConfiguration.ppEnabledLayerNames = debugLayers;
      vkInstanceConfiguration.enabledLayerCount = 1;
      // Basic buildin validation error
#endif // DENDYENGINE_MODE_DEBUG
      

      VkResult result = vkCreateInstance( &vkInstanceConfiguration, nullptr, &m_vulkanInstance );

      if ( result != VK_SUCCESS ) {
         DENDYENGINE_CRITICAL_ERROR( "Failed to create a Vulkan instance" );
      }

   DENDYENGINE_CALLSTACK_EXIT;
   }

   void UGLFWWindowHandle::_getGlfwExtensionsForVk( const char *const** a_requiredExtensions, dyUInt& a_requiredExtensionsCount ) {
      DENDYENGINE_CALLSTACK_ENTER;
      *a_requiredExtensions = glfwGetRequiredInstanceExtensions( &a_requiredExtensionsCount );
      /*
      printf( "glfw required extensions:\n" );
      for ( int i = 0; i < glfwExtensionCount; i++ ) {
      printf( "\t %s\n", glfwExtensions[i] );
      }
      */
      DENDYENGINE_CALLSTACK_EXIT;
   }

   void UGLFWWindowHandle::_createVkDevice( ) {
   DENDYENGINE_CALLSTACK_ENTER;
      const dyUInt16 MAX_PHYSICAL_DEVICES = 16;

      VkPhysicalDevice physicalDevicesVec[MAX_PHYSICAL_DEVICES];
      dyUInt physicalDevicesCount = MAX_PHYSICAL_DEVICES;
      vkEnumeratePhysicalDevices( m_vulkanInstance, &physicalDevicesCount, physicalDevicesVec );

      // TODO Pick a real one
      VkPhysicalDevice vkPhysicalDevice = physicalDevicesVec[0];

      VkPhysicalDeviceProperties physicalDevicePropriety = { };
      vkGetPhysicalDeviceProperties( vkPhysicalDevice, &physicalDevicePropriety );
      // Also call 
      // vkGetPhysicalDeviceFeautures here!

      printf( "Picking GPU: %s\n", physicalDevicePropriety.deviceName );



      //QueueFamilyIndices indices = findQueueFamilies( physicalDevice );

      VkDeviceQueueCreateInfo vkDeviceQueueConfiguration = { };
      vkDeviceQueueConfiguration.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      vkDeviceQueueConfiguration.queueFamilyIndex = 0;
      // TODO
      //queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value( );
      vkDeviceQueueConfiguration.queueCount = 1;
      dyFloat priority = 1.0;
      vkDeviceQueueConfiguration.pQueuePriorities = &priority;

      dyUInt queueFamilyCount;
      vkGetPhysicalDeviceQueueFamilyProperties( vkPhysicalDevice, &queueFamilyCount, nullptr );
      std::vector<VkQueueFamilyProperties> vkQueueFamilyProprietiesVec( queueFamilyCount );
      vkGetPhysicalDeviceQueueFamilyProperties( vkPhysicalDevice, &queueFamilyCount, vkQueueFamilyProprietiesVec.data( ) );


      VkDevice vkDevice;
      VkDeviceCreateInfo vkDeviceConfiguration = { };
      vkDeviceConfiguration.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
      vkDeviceConfiguration.pQueueCreateInfos = &vkDeviceQueueConfiguration;
      vkDeviceConfiguration.queueCreateInfoCount = 1;
      
      
      VkResult result = vkCreateDevice( vkPhysicalDevice, &vkDeviceConfiguration, nullptr, &vkDevice );
      if ( result != VK_SUCCESS ) {
         DENDYENGINE_CRITICAL_ERROR( "Failed to create a Vulkan Device" );
      }





   DENDYENGINE_CALLSTACK_EXIT;
   }

   void UGLFWWindowHandle::_initGlfw( ) {
   DENDYENGINE_CALLSTACK_ENTER;
      glfwInit( );
   DENDYENGINE_CALLSTACK_EXIT;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void UGLFWWindowHandle::_setupDisplay( ) {
      DENDYENGINE_CALLSTACK_ENTER;

      _createVkInstance( );
      DENDYENGINE_LOG( " - Vulkan Instance creation: [ OK ]" );
      _createVkDevice( );
      DENDYENGINE_LOG( " - Vulkan Device creation: [ OK ]" );
      _initGlfw( );
      DENDYENGINE_LOG( " - GLFW Initialization: [ OK ]" );

      
      


      DENDYENGINE_CALLSTACK_EXIT;
   }


   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
   ////  ================================================================================================================================  ////
   ////    ---- Object oriented methods -----                                                                                              ////
   ////  ================================================================================================================================  ////
   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   UGLFWWindowHandle::UGLFWWindowHandle( ) {
   DENDYENGINE_CALLSTACK_ENTER;
      _setupDisplay( );
      //m_openedWindows.resize( MAX_OPENED_WINDOWS );
   DENDYENGINE_CALLSTACK_EXIT;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   UGLFWWindowHandle::~UGLFWWindowHandle( ) {
      DENDYENGINE_CALLSTACK_ENTER;
      glfwTerminate( );
      vkDestroyDevice( m_vulkanDevice, nullptr );
      vkDestroyInstance( m_vulkanInstance, nullptr );
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
   ////    ---- Acessor methods -----                                                                                                      ////
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
   UGLFWWindowHandle::SVulkanReadyWindow UGLFWWindowHandle::openWindow( SConfiguration const& a_config ) {
      DENDYENGINE_CALLSTACK_ENTER;

      m_config = a_config;

      SVulkanReadyWindow windowBinding;

      glfwWindowHint( GLFW_CLIENT_API, GLFW_NO_API );
      //glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
      if ( m_config.without_borders )
         glfwWindowHint( GLFW_DECORATED, GLFW_FALSE );
      else
         glfwWindowHint( GLFW_DECORATED, GLFW_TRUE );

      windowBinding.window = glfwCreateWindow( m_config.width, m_config.height, m_config.caption.asConstChar( ), nullptr, nullptr );

      if ( windowBinding.window == nullptr ) {
         DENDYENGINE_CRITICAL_ERROR( "Unable to create the window!" );
         exit( 666 );
      }

      glfwSetWindowUserPointer( windowBinding.window, this );
      //glfwSetFramebufferSizeCallback(windowBinding.window, framebufferResizeCallback);

      //m_openedWindows.append

      DENDYENGINE_CALLSTACK_EXIT;
      return windowBinding;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void UGLFWWindowHandle::closeWindow( SVulkanReadyWindow a_window ) {
      DENDYENGINE_CALLSTACK_ENTER;
      glfwDestroyWindow( a_window.window );
      DENDYENGINE_CALLSTACK_EXIT;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   dyBool UGLFWWindowHandle::isCloseTriggered( SVulkanReadyWindow a_window ) {
      DENDYENGINE_CALLSTACK_ENTER;
      dyBool result = glfwWindowShouldClose( a_window.window ) > 0;
      DENDYENGINE_CALLSTACK_EXIT;
      return result;
   }

   //----------------------------------------------------------------------------------------------------------------------------------------//
   //
   //----------------------------------------------------------------------------------------------------------------------------------------//
   void UGLFWWindowHandle::gatherInputs( ) {
      DENDYENGINE_CALLSTACK_ENTER;
      glfwPollEvents( );
      DENDYENGINE_CALLSTACK_EXIT;
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