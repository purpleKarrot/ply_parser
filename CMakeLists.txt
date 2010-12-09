# Copyright (c) 2010 Daniel Pfeifer

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(ChunkLoad)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

#add_definitions(-DFUSION_MAX_VECTOR_SIZE=20)

find_package(ZLIB REQUIRED)
find_package(Boost REQUIRED COMPONENTS iostreams system thread)
include_directories(${Boost_INCLUDE_DIRS})


include_directories(include ${CMAKE_BINARY_DIR}/include)


include(AddReference)
include(AddDocumentation)
set(THIS_PROJECT_NAME JunkLoad)
add_subdirectory(doc)

add_subdirectory(externals)
add_subdirectory(tests)
