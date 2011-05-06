# Copyright (c) 2011 Daniel Pfeifer

include(UseLATEX)

add_latex_document(parsing.tex
  BIBFILES
    bibliography.bib
  IMAGE_DIRS
    Bilder
  INPUTS
    1_introduction.tex
    2_related_work.tex
    3_generic_parsing.tex
    4_generic_programming.tex
    5_implementation.tex
    6_ply_example.tex
    7_conclusion.tex
  DEFAULT_PDF
  MANGLE_TARGET_NAMES
  )
