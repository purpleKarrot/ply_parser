# Copyright (c) 2010 Daniel Pfeifer

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(Chunk)

set(CMAKE_BUILD_TYPE Debug)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)
include_directories(include)


find_package(Boost REQUIRED COMPONENTS thread system)

include(Extract)

set(FIBER_SRC
  ${CMAKE_BINARY_DIR}/externals/boost.fiber-0.5.0/libs/fiber/src)

if(NOT EXISTS ${FIBER_SRC})
  extract(${CMAKE_SOURCE_DIR}/externals/boost.fiber-0.5.0.zip
    ${CMAKE_BINARY_DIR}/externals)
endif(NOT EXISTS ${FIBER_SRC})

include_directories(${CMAKE_BINARY_DIR}/externals/boost.fiber-0.5.0)

add_library(boost_fiber
  ${FIBER_SRC}/detail/context_fc_posix.cpp
  ${FIBER_SRC}/asm/fcontext_i386_sysv_elf_gas.asm
  ${FIBER_SRC}/auto_reset_event.cpp
  ${FIBER_SRC}/barrier.cpp
  ${FIBER_SRC}/condition.cpp
  ${FIBER_SRC}/count_down_event.cpp
  ${FIBER_SRC}/detail/info_base.cpp
  ${FIBER_SRC}/fiber.cpp
  ${FIBER_SRC}/manual_reset_event.cpp
  ${FIBER_SRC}/mutex.cpp
  ${FIBER_SRC}/round_robin.cpp
  ${FIBER_SRC}/spin_condition.cpp
  ${FIBER_SRC}/spin_mutex.cpp
  ${FIBER_SRC}/strategy.cpp
  )


set(TASK_SRC
  ${CMAKE_BINARY_DIR}/externals/boost.task-0.4.2/libs/task/src)

if(NOT EXISTS ${TASK_SRC})
  extract(${CMAKE_SOURCE_DIR}/externals/boost.task-0.4.2.zip
    ${CMAKE_BINARY_DIR}/externals)
endif(NOT EXISTS ${TASK_SRC})

include_directories(${CMAKE_BINARY_DIR}/externals/boost.task-0.4.2)

add_library(boost_task
  ${TASK_SRC}/callable.cpp
  ${TASK_SRC}/context.cpp
  ${TASK_SRC}/fast_semaphore.cpp
  ${TASK_SRC}/poolsize.cpp
  ${TASK_SRC}/semaphore_posix.cpp
  ${TASK_SRC}/spin/auto_reset_event.cpp
  ${TASK_SRC}/spin/barrier.cpp
  ${TASK_SRC}/spin/condition.cpp
  ${TASK_SRC}/spin/count_down_event.cpp
  ${TASK_SRC}/spin/manual_reset_event.cpp
  ${TASK_SRC}/spin/mutex.cpp
  ${TASK_SRC}/stacksize.cpp
  ${TASK_SRC}/watermark.cpp
  ${TASK_SRC}/detail/worker.cpp
  ${TASK_SRC}/detail/worker_group.cpp
  ${TASK_SRC}/detail/wsq.cpp
  )


add_subdirectory(libs/obj)
add_subdirectory(tools/obj)

add_subdirectory(libs/ply)
add_subdirectory(tools/ply)
