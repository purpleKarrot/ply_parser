
include(AddPCH)
include(AddTestModule)

file(GLOB DATA_FILES ${CMAKE_SOURCE_DIR}/data/*)
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

add_definitions(-Winvalid-pch)

#add_pch(PRECOMPILED precompiled.hpp)

add_test_module(ply_test
  placeholder.cpp
  named_setter.cpp
  rule.cpp
  element_parser.cpp
  parser_parser.cpp
# element.cpp
# mpl_ply.cpp
  ply_gz.cpp
# stream.cpp
  ply_spirit.cpp
# stream_spirit.cpp
# ${PRECOMPILED}
  )

target_link_libraries(ply_test
  ${Boost_LIBRARIES}
  )

add_custom_target(test
  ${ply_test_EXECUTABLE} --log_level=all
  DEPENDS ${ply_test_EXECUTABLE}
  )
