# Copyright (c) 2010 Daniel Pfeifer

set(BOOST_FIBER_SOURCE_DIR
  ${CMAKE_BINARY_DIR}/externals/boost.fiber-0.5.0/libs/fiber/src)
if(NOT EXISTS ${BOOST_FIBER_SOURCE_DIR})
  extract(${CMAKE_SOURCE_DIR}/externals/boost.fiber-0.5.0.tar.gz
    ${CMAKE_BINARY_DIR}/externals/boost.fiber-0.5.0)
endif(NOT EXISTS ${BOOST_FIBER_SOURCE_DIR})

include_directories(${CMAKE_BINARY_DIR}/externals/boost.fiber-0.5.0)

add_library(boost_fiber
  ${BOOST_FIBER_SOURCE_DIR}/detail/context_fc_posix.cpp
  ${BOOST_FIBER_SOURCE_DIR}/asm/fcontext_i386_sysv_elf_gas.asm
  ${BOOST_FIBER_SOURCE_DIR}/auto_reset_event.cpp
  ${BOOST_FIBER_SOURCE_DIR}/barrier.cpp
  ${BOOST_FIBER_SOURCE_DIR}/condition.cpp
  ${BOOST_FIBER_SOURCE_DIR}/count_down_event.cpp
  ${BOOST_FIBER_SOURCE_DIR}/detail/info_base.cpp
  ${BOOST_FIBER_SOURCE_DIR}/fiber.cpp
  ${BOOST_FIBER_SOURCE_DIR}/manual_reset_event.cpp
  ${BOOST_FIBER_SOURCE_DIR}/mutex.cpp
  ${BOOST_FIBER_SOURCE_DIR}/round_robin.cpp
  ${BOOST_FIBER_SOURCE_DIR}/spin_condition.cpp
  ${BOOST_FIBER_SOURCE_DIR}/spin_mutex.cpp
  ${BOOST_FIBER_SOURCE_DIR}/strategy.cpp
  )
