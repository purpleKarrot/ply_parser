# Copyright (c) 2010 Daniel Pfeifer

include(Extract)

macro(EXTRACT_BOOST NAME VERSION)
  string(TOUPPER ${NAME} UNAME)
  set(COMPONENT_ROOT_DIR   ${CMAKE_CURRENT_BINARY_DIR}/boost-${NAME})
  set(BOOST_${UNAME}_SOURCE_DIR ${COMPONENT_ROOT_DIR}/libs/${NAME}/src)
  extract(boost.${NAME}-${VERSION}.tar.gz ${COMPONENT_ROOT_DIR})
  include_directories(${COMPONENT_ROOT_DIR})
endmacro(EXTRACT_BOOST)

extract_boost(context 0.2.0)
extract_boost(fiber   0.5.1)
extract_boost(task    0.4.2)

add_library(boost_context
  ${BOOST_CONTEXT_SOURCE_DIR}/context_fc_posix.cpp
  ${BOOST_CONTEXT_SOURCE_DIR}/asm/fcontext_i386_sysv_elf_gas.S
  )

add_library(boost_fiber
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

add_library(boost_task
  ${BOOST_TASK_SOURCE_DIR}/callable.cpp
  ${BOOST_TASK_SOURCE_DIR}/context.cpp
  ${BOOST_TASK_SOURCE_DIR}/fast_semaphore.cpp
  ${BOOST_TASK_SOURCE_DIR}/poolsize.cpp
  ${BOOST_TASK_SOURCE_DIR}/semaphore_posix.cpp
  ${BOOST_TASK_SOURCE_DIR}/spin/auto_reset_event.cpp
  ${BOOST_TASK_SOURCE_DIR}/spin/barrier.cpp
  ${BOOST_TASK_SOURCE_DIR}/spin/condition.cpp
  ${BOOST_TASK_SOURCE_DIR}/spin/count_down_event.cpp
  ${BOOST_TASK_SOURCE_DIR}/spin/manual_reset_event.cpp
  ${BOOST_TASK_SOURCE_DIR}/spin/mutex.cpp
  ${BOOST_TASK_SOURCE_DIR}/stacksize.cpp
  ${BOOST_TASK_SOURCE_DIR}/watermark.cpp
  ${BOOST_TASK_SOURCE_DIR}/detail/worker.cpp
  ${BOOST_TASK_SOURCE_DIR}/detail/worker_group.cpp
  ${BOOST_TASK_SOURCE_DIR}/detail/wsq.cpp
  )
