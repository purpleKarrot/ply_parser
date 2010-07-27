
include(AddTestModule)

file(GLOB DATA_FILES ${CMAKE_SOURCE_DIR}/data/*)
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test_module(ply_test
  ply_gz.cpp
  stream.cpp
  stream_spirit.cpp
  )

target_link_libraries(ply_test
  ${Boost_LIBRARIES}
  )

add_custom_target(test_xml DEPENDS ${ply_test_LOG_XML})
