# Copyright (c) 2010 Daniel Pfeifer

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Chunk)

#set(CMAKE_BUILD_TYPE Debug)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CToolBox)

#add_definitions(-DFUSION_MAX_VECTOR_SIZE=20)

function(EXTRACT ARCHIVE DIRECTORY)
  file(MAKE_DIRECTORY ${DIRECTORY})
  message(STATUS "extracting ${ARCHIVE}")
  execute_process(COMMAND ${CMAKE_COMMAND} -E tar xzf ${ARCHIVE}
    WORKING_DIRECTORY ${DIRECTORY})
endfunction(EXTRACT ARCHIVE DIRECTORY)


find_package(ZLIB REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams system thread)
#include(${CMAKE_SOURCE_DIR}/externals/UseBoostFiber.cmake)
#include(${CMAKE_SOURCE_DIR}/externals/UseBoostTask.cmake)


extract(${CMAKE_SOURCE_DIR}/externals/libzio-0.99.tar.gz
  ${CMAKE_BINARY_DIR}/externals/libzio-0.99)


extract(${CMAKE_SOURCE_DIR}/externals/boost-la.tar.gz
  ${CMAKE_BINARY_DIR}/include)

include_directories(include ${CMAKE_BINARY_DIR}/include)


include(AddReference)
include(AddDocumentation)
set(THIS_PROJECT_NAME JunkLoad)
add_subdirectory(doc)

add_subdirectory(tests)

#add_subdirectory(libs/nff)
#add_subdirectory(tools/nff)

#add_subdirectory(libs/obj)
#add_subdirectory(tools/obj)

#add_subdirectory(libs/ply)
#add_subdirectory(tools/ply)
