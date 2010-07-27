#ifndef NFF_NFF_PARSER_HPP_INCLUDED
#define NFF_NFF_PARSER_HPP_INCLUDED

#include <fstream>
#include <istream>
#include <string>

#include <tr1/functional>

#include <nff/nff.hpp>

namespace nff
{

class nff_parser
{
public:
	typedef std::tr1::function<void(std::size_t, const std::string&)> info_callback_type;
	typedef std::tr1::function<void(std::size_t, const std::string&)> warning_callback_type;
	typedef std::tr1::function<void(std::size_t, const std::string&)> error_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, float_type, float_type, size_type, size_type)> viewpoint_location_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&)> background_color_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&)> positional_light_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&, const float_3_tuple_type&)> colored_positional_light_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&, float_type, float_type, float_type, float_type, float_type)> fill_color_and_shading_parameters_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&, float_type, const float_3_tuple_type&, float_type)> cylinder_or_cone_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&, float_type)> sphere_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&)> triangular_polygon_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&)> quadrilateral_polygon_callback_type;
	typedef std::tr1::function<void(std::size_t, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&)> general_polygon_begin_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&)> general_polygon_vertex_callback_type;
	typedef std::tr1::function<void()> general_polygon_end_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&)> triangular_polygonal_patch_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&)> quadrilateral_polygonal_patch_callback_type;
	typedef std::tr1::function<void(std::size_t, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&, const float_3_tuple_type&)> general_polygonal_patch_begin_callback_type;
	typedef std::tr1::function<void(const float_3_tuple_type&, const float_3_tuple_type&)> general_polygonal_patch_vertex_callback_type;
	typedef std::tr1::function<void()> general_polygonal_patch_end_callback_type;
	typedef std::tr1::function<void(std::string&)> comment_callback_type;
	typedef int flags_type;

	enum
	{
		parse_blank_lines_as_comment = 1 << 0, triangulate_polygons = 1 << 1, triangulate_polygonal_patches = 1 << 2, triangulate = triangulate_polygons | triangulate_polygonal_patches
	};

	nff_parser(flags_type flags = 0);
	void info_callback(const error_callback_type& error_callback);
	void warning_callback(const warning_callback_type& warning_callback);
	void error_callback(const info_callback_type& info_callback);
	void viewpoint_location_callback(const viewpoint_location_callback_type& viewpoint_location_callback);
	void background_color_callback(const background_color_callback_type& background_color_callback);
	void positional_light_callbacks(const positional_light_callback_type& positional_light_callback, const colored_positional_light_callback_type& colored_positional_light_callback);
	void fill_color_and_shading_parameters_callback(const fill_color_and_shading_parameters_callback_type& fill_color_and_shading_parameters_callback);
	void cylinder_or_cone_callback(const cylinder_or_cone_callback_type& cylinder_or_cone_callback);
	void sphere_callback(const sphere_callback_type& sphere_callback);
	void polygon_callbacks(const triangular_polygon_callback_type& triangular_polygon_callback, const quadrilateral_polygon_callback_type& quadrilateral_polygon_callback, const general_polygon_begin_callback_type& general_polygon_begin_callback, const general_polygon_vertex_callback_type& general_polygon_vertex_callback, const general_polygon_end_callback_type& general_polygon_end_callback);
	void polygonal_patch_callbacks(const triangular_polygonal_patch_callback_type& triangular_polygonal_patch_callback, const quadrilateral_polygonal_patch_callback_type& quadrilateral_polygonal_patch_callback, const general_polygonal_patch_begin_callback_type& general_polygonal_patch_begin_callback, const general_polygonal_patch_vertex_callback_type& general_polygonal_patch_vertex_callback, const general_polygonal_patch_end_callback_type& general_polygonal_patch_end_callback);
	void comment_callback(const comment_callback_type& comment_callback);
	bool parse(std::istream& istream);
	bool parse(const std::string& filename);

private:
	flags_type flags_;
	info_callback_type info_callback_;
	warning_callback_type warning_callback_;
	error_callback_type error_callback_;
	viewpoint_location_callback_type viewpoint_location_callback_;
	background_color_callback_type background_color_callback_;
	positional_light_callback_type positional_light_callback_;
	colored_positional_light_callback_type colored_positional_light_callback_;
	fill_color_and_shading_parameters_callback_type fill_color_and_shading_parameters_callback_;
	cylinder_or_cone_callback_type cylinder_or_cone_callback_;
	sphere_callback_type sphere_callback_;
	triangular_polygon_callback_type triangular_polygon_callback_;
	quadrilateral_polygon_callback_type quadrilateral_polygon_callback_;
	general_polygon_begin_callback_type general_polygon_begin_callback_;
	general_polygon_vertex_callback_type general_polygon_vertex_callback_;
	general_polygon_end_callback_type general_polygon_end_callback_;
	triangular_polygonal_patch_callback_type triangular_polygonal_patch_callback_;
	quadrilateral_polygonal_patch_callback_type quadrilateral_polygonal_patch_callback_;
	general_polygonal_patch_begin_callback_type general_polygonal_patch_begin_callback_;
	general_polygonal_patch_vertex_callback_type general_polygonal_patch_vertex_callback_;
	general_polygonal_patch_end_callback_type general_polygonal_patch_end_callback_;
	comment_callback_type comment_callback_;
};

} // namespace nff

inline nff::nff_parser::nff_parser(flags_type flags) :
	flags_(flags)
{
}

inline bool nff::nff_parser::parse(const std::string& filename)
{
	std::ifstream ifstream(filename.c_str());
	return parse(ifstream);
}

inline void nff::nff_parser::info_callback(const error_callback_type& error_callback)
{
	error_callback_ = error_callback;
}

inline void nff::nff_parser::warning_callback(const warning_callback_type& warning_callback)
{
	warning_callback_ = warning_callback;
}

inline void nff::nff_parser::error_callback(const info_callback_type& info_callback)
{
	info_callback_ = info_callback;
}

inline void nff::nff_parser::viewpoint_location_callback(const viewpoint_location_callback_type& viewpoint_location_callback)
{
	viewpoint_location_callback_ = viewpoint_location_callback;
}

inline void nff::nff_parser::background_color_callback(const background_color_callback_type& background_color_callback)
{
	background_color_callback_ = background_color_callback;
}

inline void nff::nff_parser::positional_light_callbacks(const positional_light_callback_type& positional_light_callback, const colored_positional_light_callback_type& colored_positional_light_callback)
{
	positional_light_callback_ = positional_light_callback;
	colored_positional_light_callback_ = colored_positional_light_callback;
}

inline void nff::nff_parser::fill_color_and_shading_parameters_callback(const fill_color_and_shading_parameters_callback_type& fill_color_and_shading_parameters_callback)
{
	fill_color_and_shading_parameters_callback_ = fill_color_and_shading_parameters_callback;
}

inline void nff::nff_parser::cylinder_or_cone_callback(const cylinder_or_cone_callback_type& cylinder_or_cone_callback)
{
	cylinder_or_cone_callback_ = cylinder_or_cone_callback;
}

inline void nff::nff_parser::sphere_callback(const sphere_callback_type& sphere_callback)
{
	sphere_callback_ = sphere_callback;
}

inline void nff::nff_parser::polygon_callbacks(const triangular_polygon_callback_type& triangular_polygon_callback, const quadrilateral_polygon_callback_type& quadrilateral_polygon_callback, const general_polygon_begin_callback_type& general_polygon_begin_callback, const general_polygon_vertex_callback_type& general_polygon_vertex_callback, const general_polygon_end_callback_type& general_polygon_end_callback)
{
	triangular_polygon_callback_ = triangular_polygon_callback;
	quadrilateral_polygon_callback_ = quadrilateral_polygon_callback;
	general_polygon_begin_callback_ = general_polygon_begin_callback;
	general_polygon_vertex_callback_ = general_polygon_vertex_callback;
	general_polygon_end_callback_ = general_polygon_end_callback;
}

inline void nff::nff_parser::polygonal_patch_callbacks(const triangular_polygonal_patch_callback_type& triangular_polygonal_patch_callback, const quadrilateral_polygonal_patch_callback_type& quadrilateral_polygonal_patch_callback, const general_polygonal_patch_begin_callback_type& general_polygonal_patch_begin_callback, const general_polygonal_patch_vertex_callback_type& general_polygonal_patch_vertex_callback, const general_polygonal_patch_end_callback_type& general_polygonal_patch_end_callback)
{
	triangular_polygonal_patch_callback_ = triangular_polygonal_patch_callback;
	quadrilateral_polygonal_patch_callback_ = quadrilateral_polygonal_patch_callback;
	general_polygonal_patch_begin_callback_ = general_polygonal_patch_begin_callback;
	general_polygonal_patch_vertex_callback_ = general_polygonal_patch_vertex_callback;
	general_polygonal_patch_end_callback_ = general_polygonal_patch_end_callback;
}

inline void nff::nff_parser::comment_callback(const comment_callback_type& comment_callback)
{
	comment_callback_ = comment_callback;
}

#endif // NFF_NFF_PARSER_HPP_INCLUDED
