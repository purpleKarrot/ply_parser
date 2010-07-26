# Copyright (c) 2010 Daniel Pfeifer

set(BOOST_TASK_SOURCE_DIR
  ${CMAKE_BINARY_DIR}/externals/boost.task-0.4.2/libs/task/src)
if(NOT EXISTS ${BOOST_TASK_SOURCE_DIR})
  extract(${CMAKE_SOURCE_DIR}/externals/boost.task-0.4.2.tar.gz
    ${CMAKE_BINARY_DIR}/externals/boost.task-0.4.2)
endif(NOT EXISTS ${BOOST_TASK_SOURCE_DIR})

include_directories(${CMAKE_BINARY_DIR}/externals/boost.task-0.4.2)

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
