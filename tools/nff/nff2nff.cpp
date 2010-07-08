#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

#include <tr1/functional>

#include <nff/config.hpp>
#include <nff/nff_parser.hpp>

class nff_to_nff_converter
{
public:
  typedef int flags_type;
  enum { triangulate = 1 << 0 };
  nff_to_nff_converter(flags_type flags = 0);
  bool convert(std::istream& nff_istream, const std::string& nff_ifilename, std::ostream& nff_ostream, const std::string& nff_ofilename);
private:
  void info_callback(const std::string& filename, std::size_t line_number, const std::string& message);
  void warning_callback(const std::string& filename, std::size_t line_number, const std::string& message);
  void error_callback(const std::string& filename, std::size_t line_number, const std::string& message);
  void viewpoint_location_callback(const nff::float_3_tuple_type& from, const nff::float_3_tuple_type& at, const nff::float_3_tuple_type& up, nff::float_type angle, nff::float_type hither, nff::size_type resolution_x, nff::size_type resolution_y);
  void background_color_callback(const nff::float_3_tuple_type& color);
  void positional_light_callback(const nff::float_3_tuple_type& position);
  void colored_positional_light_callback(const nff::float_3_tuple_type& position, const nff::float_3_tuple_type& color);
  void fill_color_and_shading_parameters_callback(const nff::float_3_tuple_type& color, nff::float_type kd, nff::float_type ks, nff::float_type shine, nff::float_type t, nff::float_type index_of_refraction);
  void cylinder_or_cone_callback(const nff::float_3_tuple_type& base, nff::float_type base_radius, const nff::float_3_tuple_type& apex, nff::float_type apex_radius);
  void sphere_callback(const nff::float_3_tuple_type& center, nff::float_type radius);
  void triangular_polygon_callback(const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& vert_3);
  void quadrilateral_polygon_callback(const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& vert_3, const nff::float_3_tuple_type& vert_4);
  void general_polygon_begin_callback(nff::size_type total_vertices, const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& vert_3);
  void general_polygon_vertex_callback(const nff::float_3_tuple_type& vert);
  void general_polygon_end_callback();
  void triangular_polygonal_patch_callback(const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& norm_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& norm_2, const nff::float_3_tuple_type& vert_3, const nff::float_3_tuple_type& norm_3);
  void quadrilateral_polygonal_patch_callback(const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& norm_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& norm_2, const nff::float_3_tuple_type& vert_3, const nff::float_3_tuple_type& norm_3, const nff::float_3_tuple_type& vert_4, const nff::float_3_tuple_type& norm_4);
  void general_polygonal_patch_begin_callback(nff::size_type total_vertices, const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& norm_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& norm_2, const nff::float_3_tuple_type& vert_3, const nff::float_3_tuple_type& norm_3);
  void general_polygonal_patch_vertex_callback(const nff::float_3_tuple_type& vert, const nff::float_3_tuple_type& norm);
  void general_polygonal_patch_end_callback();
  void comment_callback(const std::string& comment);
  flags_type flags_;
  std::ostream* ostream_;
};

nff_to_nff_converter::nff_to_nff_converter(flags_type flags)
  : flags_(flags)
{
}

void nff_to_nff_converter::info_callback(const std::string& filename, std::size_t line_number, const std::string& message)
{
  std::cerr << filename << ":" << line_number << ": " << "info: " << message << std::endl;
}

void nff_to_nff_converter::warning_callback(const std::string& filename, std::size_t line_number, const std::string& message)
{
  std::cerr << filename << ":" << line_number << ": " << "warning: " << message << std::endl;
}

void nff_to_nff_converter::error_callback(const std::string& filename, std::size_t line_number, const std::string& message)
{
  std::cerr << filename << ":" << line_number << ": " << "error: " << message << std::endl;
}

void nff_to_nff_converter::viewpoint_location_callback(const nff::float_3_tuple_type& from, const nff::float_3_tuple_type& at, const nff::float_3_tuple_type& up, nff::float_type angle, nff::float_type hither, nff::size_type resolution_x, nff::size_type resolution_y)
{
  (*ostream_) << "v\n";
  (*ostream_) << "from " << std::tr1::get<0>(from) << " " << std::tr1::get<1>(from) << " " << std::tr1::get<2>(from) << "\n";
  (*ostream_) << "at " << std::tr1::get<0>(at) << " " << std::tr1::get<1>(at) << " " << std::tr1::get<2>(at) << "\n";
  (*ostream_) << "up " << std::tr1::get<2>(up) << " " << std::tr1::get<1>(up) << " " << std::tr1::get<2>(up) << "\n";
  (*ostream_) << "angle " << angle << "\n";
  (*ostream_) << "hither " << hither << "\n";
  (*ostream_) << "resolution " << resolution_x << " " << resolution_y << "\n";
}

void nff_to_nff_converter::background_color_callback(const nff::float_3_tuple_type& color)
{
  (*ostream_) << "b " << std::tr1::get<0>(color) << " " << std::tr1::get<1>(color) << " " << std::tr1::get<2>(color) << "\n";
}

void nff_to_nff_converter::positional_light_callback(const nff::float_3_tuple_type& position)
{
  (*ostream_) << "l " << std::tr1::get<0>(position) << " " << std::tr1::get<1>(position) << " " << std::tr1::get<2>(position) << "\n";
}

void nff_to_nff_converter::colored_positional_light_callback(const nff::float_3_tuple_type& position, const nff::float_3_tuple_type& color)
{
  (*ostream_) << "l " << std::tr1::get<0>(position) << " " << std::tr1::get<1>(position) << " " << std::tr1::get<2>(position) << " " << std::tr1::get<0>(color) << " " << std::tr1::get<1>(color) << " " << std::tr1::get<2>(color) << "\n";
}

void nff_to_nff_converter::fill_color_and_shading_parameters_callback(const nff::float_3_tuple_type& color, nff::float_type kd, nff::float_type ks, nff::float_type shine, nff::float_type t, nff::float_type index_of_refraction)
{
  (*ostream_) << "f " << std::tr1::get<0>(color) << " " << std::tr1::get<1>(color) << " " << std::tr1::get<2>(color) << " " << kd << " " << ks << " " << shine << " " << t << " " << index_of_refraction << "\n";
}

void nff_to_nff_converter::cylinder_or_cone_callback(const nff::float_3_tuple_type& base, nff::float_type base_radius, const nff::float_3_tuple_type& apex, nff::float_type apex_radius)
{
  (*ostream_) << "c " << std::tr1::get<0>(base) << " " << std::tr1::get<1>(base) << " " << std::tr1::get<2>(base) << " " << base_radius << " " << std::tr1::get<0>(apex) << " " << std::tr1::get<1>(apex) << " " << std::tr1::get<2>(apex) << " " << apex_radius << "\n";
}

void nff_to_nff_converter::sphere_callback(const nff::float_3_tuple_type& center, nff::float_type radius)
{
  (*ostream_) << "s " << std::tr1::get<0>(center) << " " << std::tr1::get<1>(center) << " " << std::tr1::get<2>(center) << " " << radius << "\n";
}

void nff_to_nff_converter::triangular_polygon_callback(const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& vert_3)
{
  (*ostream_) << "p 3\n";
  (*ostream_) << std::tr1::get<0>(vert_1) << " " << std::tr1::get<1>(vert_1) << " " << std::tr1::get<2>(vert_1) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_2) << " " << std::tr1::get<1>(vert_2) << " " << std::tr1::get<2>(vert_2) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_3) << " " << std::tr1::get<1>(vert_3) << " " << std::tr1::get<2>(vert_3) << "\n";
}

void nff_to_nff_converter::quadrilateral_polygon_callback(const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& vert_3, const nff::float_3_tuple_type& vert_4)
{
  (*ostream_) << "p 4\n";
  (*ostream_) << std::tr1::get<0>(vert_1) << " " << std::tr1::get<1>(vert_1) << " " << std::tr1::get<2>(vert_1) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_2) << " " << std::tr1::get<1>(vert_2) << " " << std::tr1::get<2>(vert_2) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_3) << " " << std::tr1::get<1>(vert_3) << " " << std::tr1::get<2>(vert_3) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_4) << " " << std::tr1::get<1>(vert_4) << " " << std::tr1::get<2>(vert_4) << "\n";
}

void nff_to_nff_converter::general_polygon_begin_callback(nff::size_type total_vertices, const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& vert_3)
{
  (*ostream_) << "p " << total_vertices << "\n";
  (*ostream_) << std::tr1::get<0>(vert_1) << " " << std::tr1::get<1>(vert_1) << " " << std::tr1::get<2>(vert_1) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_2) << " " << std::tr1::get<1>(vert_2) << " " << std::tr1::get<2>(vert_2) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_3) << " " << std::tr1::get<1>(vert_3) << " " << std::tr1::get<2>(vert_3) << "\n";
}

void nff_to_nff_converter::general_polygon_vertex_callback(const nff::float_3_tuple_type& vert)
{
  (*ostream_) << std::tr1::get<0>(vert) << " " << std::tr1::get<1>(vert) << " " << std::tr1::get<2>(vert) << "\n";
}

void nff_to_nff_converter::general_polygon_end_callback()
{
}

void nff_to_nff_converter::triangular_polygonal_patch_callback(const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& norm_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& norm_2, const nff::float_3_tuple_type& vert_3, const nff::float_3_tuple_type& norm_3)
{
  (*ostream_) << "pp 3\n";
  (*ostream_) << std::tr1::get<0>(vert_1) << " " << std::tr1::get<1>(vert_1) << " " << std::tr1::get<2>(vert_1) << " " << std::tr1::get<0>(norm_1) << " " << std::tr1::get<1>(norm_1) << " " << std::tr1::get<2>(norm_1) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_2) << " " << std::tr1::get<1>(vert_2) << " " << std::tr1::get<2>(vert_2) << " " << std::tr1::get<0>(norm_2) << " " << std::tr1::get<1>(norm_2) << " " << std::tr1::get<2>(norm_2) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_3) << " " << std::tr1::get<1>(vert_3) << " " << std::tr1::get<2>(vert_3) << " " << std::tr1::get<0>(norm_3) << " " << std::tr1::get<1>(norm_3) << " " << std::tr1::get<2>(norm_3) << "\n";
}

void nff_to_nff_converter::quadrilateral_polygonal_patch_callback(const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& norm_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& norm_2, const nff::float_3_tuple_type& vert_3, const nff::float_3_tuple_type& norm_3, const nff::float_3_tuple_type& vert_4, const nff::float_3_tuple_type& norm_4)
{
  (*ostream_) << "pp 4\n";
  (*ostream_) << std::tr1::get<0>(vert_1) << " " << std::tr1::get<1>(vert_1) << " " << std::tr1::get<2>(vert_1) << " " << std::tr1::get<0>(norm_1) << " " << std::tr1::get<1>(norm_1) << " " << std::tr1::get<2>(norm_1) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_2) << " " << std::tr1::get<1>(vert_2) << " " << std::tr1::get<2>(vert_2) << " " << std::tr1::get<0>(norm_2) << " " << std::tr1::get<1>(norm_2) << " " << std::tr1::get<2>(norm_2) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_3) << " " << std::tr1::get<1>(vert_3) << " " << std::tr1::get<2>(vert_3) << " " << std::tr1::get<0>(norm_3) << " " << std::tr1::get<1>(norm_3) << " " << std::tr1::get<2>(norm_3) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_4) << " " << std::tr1::get<1>(vert_4) << " " << std::tr1::get<2>(vert_4) << " " << std::tr1::get<0>(norm_4) << " " << std::tr1::get<1>(norm_4) << " " << std::tr1::get<2>(norm_4) << "\n";
}

void nff_to_nff_converter::general_polygonal_patch_begin_callback(nff::size_type total_vertices, const nff::float_3_tuple_type& vert_1, const nff::float_3_tuple_type& norm_1, const nff::float_3_tuple_type& vert_2, const nff::float_3_tuple_type& norm_2, const nff::float_3_tuple_type& vert_3, const nff::float_3_tuple_type& norm_3)
{
  (*ostream_) << "pp " << total_vertices << "\n";
  (*ostream_) << std::tr1::get<0>(vert_1) << " " << std::tr1::get<1>(vert_1) << " " << std::tr1::get<2>(vert_1) << " " << std::tr1::get<0>(norm_1) << " " << std::tr1::get<1>(norm_1) << " " << std::tr1::get<2>(norm_1) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_2) << " " << std::tr1::get<1>(vert_2) << " " << std::tr1::get<2>(vert_2) << " " << std::tr1::get<0>(norm_2) << " " << std::tr1::get<1>(norm_2) << " " << std::tr1::get<2>(norm_2) << "\n";
  (*ostream_) << std::tr1::get<0>(vert_3) << " " << std::tr1::get<1>(vert_3) << " " << std::tr1::get<2>(vert_3) << " " << std::tr1::get<0>(norm_3) << " " << std::tr1::get<1>(norm_3) << " " << std::tr1::get<2>(norm_3) << "\n";
}

void nff_to_nff_converter::general_polygonal_patch_vertex_callback(const nff::float_3_tuple_type& vert, const nff::float_3_tuple_type& norm)
{
  (*ostream_) << std::tr1::get<0>(vert) << " " << std::tr1::get<1>(vert) << " " << std::tr1::get<2>(vert) << " " << std::tr1::get<0>(norm) << " " << std::tr1::get<1>(norm) << " " << std::tr1::get<2>(norm) << "\n";
}

void nff_to_nff_converter::general_polygonal_patch_end_callback()
{
}

void nff_to_nff_converter::comment_callback(const std::string& comment)
{
  (*ostream_) << comment << "\n";
}

bool nff_to_nff_converter::convert(std::istream& nff_istream, const std::string& nff_ifilename, std::ostream& nff_ostream, const std::string& nff_ofilename)
{
  using namespace std::tr1::placeholders;

  nff::nff_parser::flags_type nff_parser_flags = 0;
  nff_parser_flags |= nff::nff_parser::parse_blank_lines_as_comment;
  if (flags_ & triangulate) {
    nff_parser_flags |= nff::nff_parser::triangulate;
  }

  nff::nff_parser nff_parser(nff_parser_flags);

  nff_parser.info_callback(std::tr1::bind(&nff_to_nff_converter::info_callback, this, nff_ifilename, _1, _2));
  nff_parser.warning_callback(std::tr1::bind(&nff_to_nff_converter::warning_callback, this, nff_ifilename, _1, _2));
  nff_parser.error_callback(std::tr1::bind(&nff_to_nff_converter::error_callback, this, nff_ifilename, _1, _2));

  nff_parser.viewpoint_location_callback(std::tr1::bind(&nff_to_nff_converter::viewpoint_location_callback, this, _1, _2, _3, _4, _5, _6, _7));
  nff_parser.background_color_callback(std::tr1::bind(&nff_to_nff_converter::background_color_callback, this, _1));
  nff_parser.positional_light_callbacks(
    std::tr1::bind(&nff_to_nff_converter::positional_light_callback, this, _1),
    std::tr1::bind(&nff_to_nff_converter::colored_positional_light_callback, this, _1, _2)
  );
  nff_parser.fill_color_and_shading_parameters_callback(std::tr1::bind(&nff_to_nff_converter::fill_color_and_shading_parameters_callback, this, _1, _2, _3, _4, _5, _6));
  nff_parser.cylinder_or_cone_callback(std::tr1::bind(&nff_to_nff_converter::cylinder_or_cone_callback, this, _1, _2, _3, _4));
  nff_parser.sphere_callback(std::tr1::bind(&nff_to_nff_converter::sphere_callback, this, _1, _2));
  nff_parser.polygon_callbacks(
    std::tr1::bind(&nff_to_nff_converter::triangular_polygon_callback, this, _1, _2, _3),
    std::tr1::bind(&nff_to_nff_converter::quadrilateral_polygon_callback, this, _1, _2, _3, _4),
    std::tr1::bind(&nff_to_nff_converter::general_polygon_begin_callback, this, _1, _2, _3, _4),
    std::tr1::bind(&nff_to_nff_converter::general_polygon_vertex_callback, this, _1),
    std::tr1::bind(&nff_to_nff_converter::general_polygon_end_callback, this)
  );
  nff_parser.polygonal_patch_callbacks(
    std::tr1::bind(&nff_to_nff_converter::triangular_polygonal_patch_callback, this, _1, _2, _3, _4, _5, _6),
    std::tr1::bind(&nff_to_nff_converter::quadrilateral_polygonal_patch_callback, this, _1, _2, _3, _4, _5, _6, _7, _8),
    std::tr1::bind(&nff_to_nff_converter::general_polygonal_patch_begin_callback, this, _1, _2, _3, _4, _5, _6, _7),
    std::tr1::bind(&nff_to_nff_converter::general_polygonal_patch_vertex_callback, this, _1, _2),
    std::tr1::bind(&nff_to_nff_converter::general_polygonal_patch_end_callback, this)
  );
  nff_parser.comment_callback(std::tr1::bind(&nff_to_nff_converter::comment_callback, this, _1));

  ostream_ = &nff_ostream;

  return nff_parser.parse(nff_istream);
}

int main(int argc, char* argv[])
{
  nff_to_nff_converter::flags_type nff_to_nff_converter_flags = 0;

  int argi;
  for (argi = 1; argi < argc; ++argi) {

    if (argv[argi][0] != '-') {
      break;
    }
    if (argv[argi][1] == 0) {
      ++argi;
      break;
    }
    char short_opt, *long_opt, *opt_arg;
    if (argv[argi][1] != '-') {
      short_opt = argv[argi][1];
      opt_arg = &argv[argi][2];
      long_opt = &argv[argi][2];
      while (*long_opt != '\0') {
        ++long_opt;
      }
    }
    else {
      short_opt = 0;
      long_opt = &argv[argi][2];
      opt_arg = long_opt;
      while ((*opt_arg != '=') && (*opt_arg != '\0')) {
        ++opt_arg;
      }
      if (*opt_arg == '=') {
        *opt_arg++ = '\0';
      }
    }

    if ((short_opt == 'h') || (std::strcmp(long_opt, "help") == 0)) {
      std::cout << "Usage: nff2nff [OPTION] [[INFILE] OUTFILE]\n";
      std::cout << "Parse a NFF file.\n";
      std::cout << "\n";
      std::cout << "  -h, --help       display this help and exit\n";
      std::cout << "  -v, --version    output version information and exit\n";
      std::cout << "  -f, --flag=FLAG  set parser flag\n";
      std::cout << "\n";
      std::cout << "FLAG may be one of the following: parse_blank_lines_as_comment,\n";
      std::cout << "triangulate_polygons, triangulate_polygonal_patches, triangulate.\n";
      std::cout << "\n";
      std::cout << "With no INFILE/OUTFILE, or when INFILE/OUTFILE is -, read standard input/output.\n";
      std::cout << "\n";
      std::cout << "Report bugs to <" << NFF_PACKAGE_BUGREPORT << ">.\n";
      return EXIT_SUCCESS;
    }

    else if ((short_opt == 'v') || (std::strcmp(long_opt, "version") == 0)) {
      std::cout << "nff2nff (" << NFF_PACKAGE_NAME << ") " << NFF_PACKAGE_VERSION << "\n";
      std::cout << "Copyright (C) 2007 " << NFF_PACKAGE_AUTHOR << "\n";
      std::cout << "\n";
      std::cout << "This program is free software; you can redistribute it and/or modify\n";
      std::cout << "it under the terms of the GNU General Public License as published by\n";
      std::cout << "the Free Software Foundation; either version 2 of the License, or\n";
      std::cout << "(at your option) any later version.\n";
      std::cout << "\n";
      std::cout << "This program is distributed in the hope that it will be useful,\n";
      std::cout << "but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
      std::cout << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
      std::cout << "GNU General Public License for more details.\n";
      std::cout << "\n";
      std::cout << "You should have received a copy of the GNU General Public License\n";
      std::cout << "along with this program; if not, write to the Free Software\n";
      std::cout << "Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA\n";
      return EXIT_SUCCESS;
    }

    else if ((short_opt == 'f') || (std::strcmp(long_opt, "flag") == 0)) {
      if (strcmp(opt_arg, "triangulate") == 0) {
        nff_to_nff_converter_flags |= nff_to_nff_converter::triangulate;
      }
      else {
        std::cerr << "nff2nff: " << "invalid option `" << argv[argi] << "'" << "\n";
        std::cerr << "Try `" << argv[0] << " --help' for more information.\n";
        return EXIT_FAILURE;
      }
    }

    else {
      std::cerr << "nff2nff: " << "invalid option `" << argv[argi] << "'" << "\n";
      std::cerr << "Try `" << argv[0] << " --help' for more information.\n";
      return EXIT_FAILURE;
    }
  }

  int parc = argc - argi;
  char** parv = argv + argi;
  if (parc > 2) {
    std::cerr << "nff2nff: " << "too many parameters" << "\n";
    std::cerr << "Try `" << argv[0] << " --help' for more information.\n";
    return EXIT_FAILURE;
  }

  std::ifstream ifstream;
  const char* ifilename = "";
  if (parc > 0) {
    ifilename = parv[0];
    if (std::strcmp(ifilename, "-") != 0) {
      ifstream.open(ifilename);
      if (!ifstream.is_open()) {
        std::cerr << "nff2nff: " << ifilename << ": " << "no such file or directory" << "\n";
        return EXIT_FAILURE;
      }
    }
  }

  std::ofstream ofstream;
  const char* ofilename = "";
  if (parc > 1) {
    ofilename = parv[1];
    if (std::strcmp(ofilename, "-") != 0) {
      ofstream.open(ofilename);
      if (!ofstream.is_open()) {
        std::cerr << "nff2nff: " << ofilename << ": " << "could not open file" << "\n";
        return EXIT_FAILURE;
      }
    }
  }

  std::istream& istream = ifstream.is_open() ? ifstream : std::cin;
  std::ostream& ostream = ofstream.is_open() ? ofstream : std::cout;

  nff_to_nff_converter converter(nff_to_nff_converter_flags);
  return converter.convert(istream, ifilename, ostream, ofilename);
}
