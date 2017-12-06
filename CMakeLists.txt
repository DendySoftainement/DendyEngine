CMAKE_MINIMUM_REQUIRED( VERSION 3.10.0 )
PROJECT( DendyEngine )

#set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_BUILD_TYPE "Debug")

set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# we want to use C++11
if(NOT DEFINED MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")



#============== Link Dependancies ==============#
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_libraries(${OPENGL_LIBRARIES})
endif()

find_package(GLEW REQUIRED)
if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
    link_libraries(${GLEW_LIBRARY})
endif()

find_package(GLM REQUIRED)
if(GLM_FOUND)
    include_directories(${GLM_INCLUDE_DIRS})
endif()





find_package(SDL2 REQUIRED)
if(SDL2_FOUND)
    include_directories(${SDL2_INCLUDE_DIR})
    link_libraries(${SDL2_LIBRARY})
endif()

find_package(Vulkan REQUIRED)
if(Vulkan_FOUND)
    include_directories(${VULKAN_INCLUDE_DIR})
    link_libraries(${VULKAN_LIBRARY})
endif()


find_package(X11_XCB)
if(X11_XCB_FOUND)
  add_definitions(-DHAVE_X11_XCB)
  list(APPEND SUBSYSTEMS [X11])
  include_directories(${X11_XCB_INCLUDE_DIRS})
endif()

find_package(SDL2_image REQUIRED)
if(SDL2_IMAGE_FOUND)
    include_directories(${SDL2_IMAGE_INCLUDE_DIRS})
    link_libraries(${SDL2_IMAGE_LIBRARIES})
endif()
#============== Link Dependancies ==============#





file(GLOB_RECURSE HEADER_FILES code/hdr/*.h)
file(GLOB_RECURSE SOURCE_FILES code/src/*.cpp code/*.cpp)


#add_definitions( -DDEBUG=1 )
#add_definitions( -DOPENGL=0 )
#add_definitions( -DVULKAN=1 )

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES} ${SHADER_FILES})

set_target_properties(
   ${PROJECT_NAME}
      PROPERTIES
         COMPILE_DEFINITIONS
            DENDY_DEBUG=1
            DENDY_PLATFORM_WINDOWS=0
            DENDY_PLATFORM_LINUX=1
            DENDY_VERSION_MAJOR=1
            DENDY_VERSION_MINOR=0
            DENDY_VERSION_PATCH=0
)
