
include(AddTestModule)

set(BUNNY_TGZ ${CMAKE_SOURCE_DIR}/data/bunny.ply.gz)
file(COPY ${BUNNY_TGZ} ${CMAKE_SOURCE_DIR}/data/faces.txt
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
execute_process(COMMAND gunzip -c ${BUNNY_TGZ}
  OUTPUT_FILE ${CMAKE_CURRENT_BINARY_DIR}/bunny.ply)

add_test_module(ply_test
  header.cpp
  element.cpp
  element_parser.cpp
  complete.cpp
  )

add_custom_target(check
  ${ply_test_EXECUTABLE} --result_code=no --log_level=all
  DEPENDS ${ply_test_EXECUTABLE}
  )

add_executable(mmap_alloc mmap.cpp)
target_link_libraries(mmap_alloc ${Boost_LIBRARIES})

add_executable(out_iterator out_iterator.cpp)
