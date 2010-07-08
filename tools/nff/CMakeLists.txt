# Copyright (c) 2010 Daniel Pfeifer

add_executable(nff2nff nff2nff.cpp)
add_executable(nff2obj nff2obj.cpp)

target_link_libraries(nff2nff nff)
target_link_libraries(nff2obj nff)
