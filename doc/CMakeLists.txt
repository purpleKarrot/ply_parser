
include(UseLATEX)

add_reference(chunk-ref.xml
# ../include/nff/nff.hpp
# ../include/nff/nff_parser.hpp
# ../include/obj/obj.hpp
# ../include/obj/obj_parser.hpp
  ../include/ply/ply.hpp
  ../include/ply/ply_parser.hpp
  HEADER_PREFIX include
  )

add_documentation(
  chunk.qbk
  ply.qbk
  ply_chunk.qbk
  ply_model.qbk
  chunk-ref.xml
  )

add_latex_document(junkload.tex DEFAULT_PDF MANGLE_TARGET_NAMES)
