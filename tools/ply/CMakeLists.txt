# Copyright (c) 2010 Daniel Pfeifer

add_executable(ply2obj ply2obj.cpp)
add_executable(ply2ply ply2ply.cpp)
add_executable(ply2raw ply2raw.cpp)

target_link_libraries(ply2obj ply)
target_link_libraries(ply2ply ply)
target_link_libraries(ply2raw ply)

add_executable(plyheader plyheader.cpp)
