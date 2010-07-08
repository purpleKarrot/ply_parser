# Copyright (c) 2010 Daniel Pfeifer

add_executable(obj2obj obj2obj.cpp)
add_executable(obj2raw obj2raw.cpp)

target_link_libraries(obj2obj obj)
target_link_libraries(obj2raw obj)
