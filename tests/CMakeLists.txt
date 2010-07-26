
include(AddTestModule)

file(COPY ${CMAKE_SOURCE_DIR}/data/bunny.ply.gz
  DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test_module(ply_test
  ply_gz.cpp
  )

target_link_libraries(ply_test
  ${Boost_LIBRARIES}
  )

add_custom_target(test_xml DEPENDS ${ply_test_LOG_XML})
