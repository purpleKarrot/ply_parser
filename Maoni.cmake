# Copyright (c) 2010 Daniel Pfeifer <daniel@pfeifer-mail.de>

maoni_module(JunkLoader
  INCLUDE_DIRECTORIES
    include
  SOURCE
    examples/libMaoni/ply.cpp
    examples/libMaoni/ply_gz.cpp
    examples/libMaoni/ply_bz2.cpp
    examples/libMaoni/model.cpp
  DATA
    data/bunny.ply.gz
  )
