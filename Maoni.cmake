# Copyright (c) 2010 Daniel Pfeifer <daniel@pfeifer-mail.de>

find_package(Boost REQUIRED COMPONENTS iostreams)
include_directories(${Boost_INCLUDE_DIRS})

maoni_module(JunkLoader
  INCLUDE_DIRECTORIES
    include
  LINK_LIBRARIES
    ${Boost_LIBRARIES}
  SOURCE
    examples/libMaoni/ply.cpp
    examples/libMaoni/model.cpp
  DATA
    data/bunny.ply.gz
  )
