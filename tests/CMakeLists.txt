
include(AddTestModule)
include(PurplePrecompileHeaders)

set(BUNNY_TGZ ${CMAKE_SOURCE_DIR}/data/bunny.ply.gz)
file(COPY ${BUNNY_TGZ} ${CMAKE_SOURCE_DIR}/data/faces.txt
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
execute_process(COMMAND gunzip -c ${BUNNY_TGZ}
  OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/bunny.ply)


set(TEST_SOURCES
  header.cpp
  element.cpp
  element_parser.cpp
  complete.cpp
  )


purple_pch_prepare(test_pch TEST_SOURCES
  <boost/spirit/include/qi.hpp>
  <boost/fusion/include/all.hpp>
  )

add_test_module(ply_test ${TEST_SOURCES})

purple_pch_use(test_pch ply_test)


add_custom_target(check
  ${ply_test_EXECUTABLE} --result_code=no --log_level=all
  DEPENDS ${ply_test_EXECUTABLE}
  )

add_executable(mmap_alloc mmap.cpp)
target_link_libraries(mmap_alloc ${Boost_LIBRARIES})

add_executable(out_iterator out_iterator.cpp)
