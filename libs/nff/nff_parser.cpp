#include <nff/nff_parser.hpp>

#include <fstream>
#include <sstream>

bool nff::nff_parser::parse(std::istream& istream)
{
	std::string line;
	std::size_t line_number = 0;
	std::istringstream stringstream;
	stringstream.unsetf(std::ios_base::skipws);

	std::size_t number_of_v_entities = 0;
	std::size_t number_of_b_entities = 0;
	std::size_t number_of_l_entities = 0;
	std::size_t number_of_f_entities = 0;
	std::size_t number_of_c_entities = 0;
	std::size_t number_of_s_entities = 0;
	std::size_t number_of_p_entities = 0;
	std::size_t number_of_pp_entities = 0;

	while (!istream.eof() && std::getline(istream, line))
	{
		++line_number;
		stringstream.clear();
		stringstream.str(line);
		stringstream >> std::ws;

		if (stringstream.eof())
		{
			if (flags_ & parse_blank_lines_as_comment)
			{
				if (comment_callback_)
					comment_callback_(line);
			}
		}
		else if (stringstream.peek() == '#')
		{
			if (comment_callback_)
				comment_callback_(line);
		}
		else
		{
			std::string keyword;
			stringstream >> keyword;

			// v
			if (keyword == "v")
			{
				if ((number_of_v_entities != 0) || ((number_of_f_entities != 0) || (number_of_c_entities != 0) || (number_of_s_entities != 0) || (number_of_p_entities != 0) || (number_of_pp_entities != 0)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				// v
				stringstream >> std::ws;
				if (!(stringstream && stringstream.eof()))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				// from
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				++line_number;
				stringstream.clear();
				stringstream.str(line);
				std::string from;
				float_type from_x, from_y, from_z;
				char ws_from_from_x, ws_from_x_from_y, ws_from_y_from_z;
				stringstream >> std::ws >> from >> ws_from_from_x >> std::ws >> from_x >> ws_from_x_from_y >> std::ws >> from_y >> ws_from_y_from_z >> std::ws >> from_z >> std::ws;

				if (!(stringstream && stringstream.eof() && (from == "from") && std::isspace(ws_from_from_x) && std::isspace(ws_from_x_from_y) && std::isspace(ws_from_y_from_z)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				// at
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}

				++line_number;
				stringstream.clear();
				stringstream.str(line);
				std::string at;
				float_type at_x, at_y, at_z;
				char ws_at_at_x, ws_at_x_at_y, ws_at_y_at_z;
				stringstream >> std::ws >> at >> ws_at_at_x >> std::ws >> at_x >> ws_at_x_at_y >> std::ws >> at_y >> ws_at_y_at_z >> std::ws >> at_z >> std::ws;

				if (!(stringstream && stringstream.eof() && (at == "at") && std::isspace(ws_at_at_x) && std::isspace(ws_at_x_at_y) && std::isspace(ws_at_y_at_z)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				// up
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}

				++line_number;
				stringstream.clear();
				stringstream.str(line);
				std::string up;
				float_type up_x, up_y, up_z;
				char ws_up_up_x, ws_up_x_up_y, ws_up_y_up_z;
				stringstream >> std::ws >> up >> ws_up_up_x >> std::ws >> up_x >> ws_up_x_up_y >> std::ws >> up_y >> ws_up_y_up_z >> std::ws >> up_z >> std::ws;

				if (!(stringstream && stringstream.eof() && (up == "up") && std::isspace(ws_up_up_x) && std::isspace(ws_up_x_up_y) && std::isspace(ws_up_y_up_z)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				// angle
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				++line_number;
				stringstream.clear();
				stringstream.str(line);
				std::string angle_keyword;
				float_type angle;
				char ws_angle_keyword_angle;
				stringstream >> std::ws >> angle_keyword >> ws_angle_keyword_angle >> std::ws >> angle >> std::ws;

				if (!(stringstream && stringstream.eof() && (angle_keyword == "angle") && std::isspace(ws_angle_keyword_angle)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				// hither
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}

				++line_number;
				stringstream.clear();
				stringstream.str(line);
				std::string hither_keyword;
				float_type hither;
				char ws_hither_keyword_hither;
				stringstream >> std::ws >> hither_keyword >> ws_hither_keyword_hither >> std::ws >> hither >> std::ws;

				if (!(stringstream && stringstream.eof() && (hither_keyword == "hither") && std::isspace(ws_hither_keyword_hither)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				// resolution
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				++line_number;
				stringstream.clear();
				stringstream.str(line);
				std::string resolution;
				size_type resolution_x, resolution_y;
				char ws_resolution_resolution_x, ws_resolution_x_resolution_y;
				stringstream >> std::ws >> resolution >> ws_resolution_resolution_x >> std::ws >> resolution_x >> ws_resolution_x_resolution_y >> std::ws >> resolution_y >> std::ws;

				if (!(stringstream && stringstream.eof() && (resolution == "resolution") && std::isspace(ws_resolution_resolution_x) && std::isspace(ws_resolution_x_resolution_y)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				++number_of_v_entities;
				if (viewpoint_location_callback_)
					viewpoint_location_callback_(float_3_tuple_type(from_x, from_y, from_z), float_3_tuple_type(at_x, at_y, at_z), float_3_tuple_type(up_x, up_y, up_z), angle, hither, resolution_x, resolution_y);
			}

			// b
			else if (keyword == "b")
			{
				if ((number_of_b_entities != 0) || ((number_of_f_entities != 0) || (number_of_c_entities != 0) || (number_of_s_entities != 0) || (number_of_p_entities != 0) || (number_of_pp_entities != 0)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				float_type r, g, b;
				char ws_b_r, ws_r_g, ws_g_b;
				stringstream >> ws_b_r >> std::ws >> r >> ws_r_g >> std::ws >> g >> ws_g_b >> std::ws >> b >> std::ws;

				if (!(stringstream && stringstream.eof() && std::isspace(ws_b_r) && std::isspace(ws_r_g) && std::isspace(ws_g_b)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				++number_of_b_entities;

				if (background_color_callback_)
					background_color_callback_(float_3_tuple_type(r, g, b));
			}

			// l
			else if (keyword == "l")
			{
				if ((number_of_f_entities != 0) || (number_of_c_entities != 0) || (number_of_s_entities != 0) || (number_of_p_entities != 0) || (number_of_pp_entities != 0))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				float_type x, y, z;
				char ws_l_x, ws_x_y, ws_y_z;
				stringstream >> ws_l_x >> std::ws >> x >> ws_x_y >> std::ws >> y >> ws_y_z >> std::ws >> z;
				char ws_z_r = ' ';

				if (!stringstream.eof())
				{
					stringstream >> ws_z_r >> std::ws;
				}

				if (!(stringstream && std::isspace(ws_l_x) && std::isspace(ws_x_y) && std::isspace(ws_y_z) && std::isspace(ws_z_r)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				if (stringstream.eof())
				{
					++number_of_l_entities;
					if (positional_light_callback_)
						positional_light_callback_(float_3_tuple_type(x, y, z));
				}
				else
				{
					float_type r, g, b;
					char ws_r_g, ws_g_b;
					stringstream >> r >> ws_r_g >> std::ws >> g >> ws_g_b >> std::ws >> b >> std::ws;

					if (!(stringstream && stringstream.eof() && std::isspace(ws_r_g) && std::isspace(ws_g_b)))
					{
						if (error_callback_)
							error_callback_(line_number, "parse error");

						return false;
					}

					++number_of_l_entities;

					if (colored_positional_light_callback_)
						colored_positional_light_callback_(float_3_tuple_type(x, y, z), float_3_tuple_type(r, g, b));
				}
			}

			// f
			else if (keyword == "f")
			{
				float_type r, g, b, kd, ks, shine, t, index_of_refraction;
				char ws_f_r, ws_r_g, ws_g_b, ws_b_kd, ws_kd_ks, ws_ks_shine, ws_shine_t, ws_t_index_of_refraction;
				stringstream >> ws_f_r >> std::ws >> r >> ws_r_g >> std::ws >> g >> ws_g_b >> std::ws >> b >> ws_b_kd >> std::ws >> kd >> ws_kd_ks >> std::ws >> ks >> ws_ks_shine >> std::ws >> shine >> ws_shine_t >> std::ws >> t >> ws_t_index_of_refraction >> std::ws >> index_of_refraction >> std::ws;

				if (!(stringstream && stringstream.eof() && std::isspace(ws_f_r) && std::isspace(ws_r_g) && std::isspace(ws_g_b) && std::isspace(ws_b_kd) && std::isspace(ws_kd_ks) && std::isspace(ws_ks_shine) && std::isspace(ws_shine_t) && std::isspace(ws_t_index_of_refraction)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				++number_of_f_entities;

				if (fill_color_and_shading_parameters_callback_)
					fill_color_and_shading_parameters_callback_(float_3_tuple_type(r, g, b), kd, ks, shine, t, index_of_refraction);
			}

			// c
			else if (keyword == "c")
			{
				float_type base_x, base_y, base_z, base_radius, apex_x, apex_y, apex_z, apex_radius;
				char wc_c_base_x, ws_base_x_base_y, ws_base_y_base_z, ws_base_z_base_radius, ws_base_radius_apex_x, ws_apex_x_apex_y, ws_apex_y_apex_z, ws_apex_z_apex_radius;
				stringstream >> wc_c_base_x >> std::ws >> base_x >> ws_base_x_base_y >> std::ws >> base_y >> ws_base_y_base_z >> std::ws >> base_z >> ws_base_z_base_radius >> std::ws >> base_radius >> ws_base_radius_apex_x >> std::ws >> apex_x >> ws_apex_x_apex_y >> std::ws >> apex_y >> ws_apex_y_apex_z >> std::ws >> apex_z >> ws_apex_z_apex_radius >> std::ws >> apex_radius >> std::ws;

				if (!(stringstream && stringstream.eof() && std::isspace(wc_c_base_x) && std::isspace(ws_base_x_base_y) && std::isspace(ws_base_y_base_z) && std::isspace(ws_base_z_base_radius) && std::isspace(ws_base_radius_apex_x) && std::isspace(ws_apex_x_apex_y) && std::isspace(ws_apex_y_apex_z) && std::isspace(ws_apex_z_apex_radius)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				++number_of_c_entities;

				if (cylinder_or_cone_callback_)
					cylinder_or_cone_callback_(float_3_tuple_type(base_x, base_y, base_z), base_radius, float_3_tuple_type(apex_x, apex_y, apex_z), apex_radius);
			}

			// s
			else if (keyword == "s")
			{
				float_type center_x, center_y, center_z, radius;
				char ws_s_center_x, ws_center_x_center_y, ws_center_y_center_z, ws_center_z_radius;
				stringstream >> ws_s_center_x >> std::ws >> center_x >> ws_center_x_center_y >> std::ws >> center_y >> ws_center_y_center_z >> std::ws >> center_z >> ws_center_z_radius >> std::ws >> radius >> std::ws;

				if (!(stringstream && stringstream.eof() && std::isspace(ws_s_center_x) && std::isspace(ws_center_x_center_y) && std::isspace(ws_center_y_center_z) && std::isspace(ws_center_z_radius)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				++number_of_s_entities;

				if (sphere_callback_)
					sphere_callback_(float_3_tuple_type(center_x, center_y, center_z), radius);
			}

			// p
			else if (keyword == "p")
			{
				size_type total_vertices;
				char ws_p_total_vertices;
				stringstream >> ws_p_total_vertices >> std::ws >> total_vertices >> std::ws;

				if (!(stringstream && stringstream.eof() && std::isspace(ws_p_total_vertices)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				if (total_vertices < 3)
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				// vert1
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				++line_number;
				stringstream.clear();
				stringstream.str(line);
				float_type vert_1_x, vert_1_y, vert_1_z;
				char ws_vert_1_x_vert_1_y, ws_vert_1_y_vert_1_z;
				stringstream >> std::ws >> vert_1_x >> ws_vert_1_x_vert_1_y >> std::ws >> vert_1_y >> ws_vert_1_y_vert_1_z >> std::ws >> vert_1_z >> std::ws;

				if (!(stringstream && stringstream.eof() && std::isspace(ws_vert_1_x_vert_1_y) && std::isspace(ws_vert_1_y_vert_1_z)))
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				// vert2
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
						error_callback_(line_number, "parse error");

					return false;
				}

				++line_number;
				stringstream.clear();
				stringstream.str(line);
				float_type vert_2_x, vert_2_y, vert_2_z;
				char ws_vert_2_x_vert_2_y, ws_vert_2_y_vert_2_z;
				stringstream >> std::ws >> vert_2_x >> ws_vert_2_x_vert_2_y >> std::ws >> vert_2_y >> ws_vert_2_y_vert_2_z >> std::ws >> vert_2_z >> std::ws;
				if (!(stringstream && stringstream.eof() && std::isspace(ws_vert_2_x_vert_2_y) && std::isspace(ws_vert_2_y_vert_2_z)))
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				// vert3
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				++line_number;
				stringstream.clear();
				stringstream.str(line);
				float_type vert_3_x, vert_3_y, vert_3_z;
				char ws_vert_3_x_vert_3_y, ws_vert_3_y_vert_3_z;
				stringstream >> std::ws >> vert_3_x >> ws_vert_3_x_vert_3_y >> std::ws >> vert_3_y >> ws_vert_3_y_vert_3_z >> std::ws >> vert_3_z >> std::ws;
				if (!(stringstream && stringstream.eof() && std::isspace(ws_vert_3_x_vert_3_y) && std::isspace(ws_vert_3_y_vert_3_z)))
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				if (total_vertices == 3)
				{
					if (triangular_polygon_callback_)
					{
						triangular_polygon_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(vert_2_x, vert_2_y, vert_2_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z));
					}
				}
				else
				{
					// vert4
					std::getline(istream, line);
					if (!istream)
					{
						if (error_callback_)
						{
							error_callback_(line_number, "parse error");
						}
						return false;
					}
					++line_number;
					stringstream.clear();
					stringstream.str(line);
					float_type vert_4_x, vert_4_y, vert_4_z;
					char ws_vert_4_x_vert_4_y, ws_vert_4_y_vert_4_z;
					stringstream >> std::ws >> vert_4_x >> ws_vert_4_x_vert_4_y >> std::ws >> vert_4_y >> ws_vert_4_y_vert_4_z >> std::ws >> vert_4_z >> std::ws;
					if (!(stringstream && stringstream.eof() && std::isspace(ws_vert_4_x_vert_4_y) && std::isspace(ws_vert_4_y_vert_4_z)))
					{
						if (error_callback_)
						{
							error_callback_(line_number, "parse error");
						}
						return false;
					}
					if (total_vertices == 4)
					{
						if (flags_ & triangulate_polygons)
						{
							if (triangular_polygon_callback_)
							{
								triangular_polygon_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(vert_2_x, vert_2_y, vert_2_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z));
								triangular_polygon_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z), float_3_tuple_type(vert_4_x, vert_4_y, vert_4_z));
							}
						}
						else
						{
							if (quadrilateral_polygon_callback_)
							{
								quadrilateral_polygon_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(vert_2_x, vert_2_y, vert_2_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z), float_3_tuple_type(vert_4_x, vert_4_y, vert_4_z));
							}
						}
					}
					else
					{
						if (flags_ & triangulate_polygons)
						{
							if (triangular_polygon_callback_)
							{
								triangular_polygon_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(vert_2_x, vert_2_y, vert_2_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z));
								triangular_polygon_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z), float_3_tuple_type(vert_4_x, vert_4_y, vert_4_z));
							}
						}
						else
						{
							if (general_polygon_begin_callback_)
							{
								general_polygon_begin_callback_(total_vertices, float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(vert_2_x, vert_2_y, vert_2_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z));
							}
							if (general_polygon_vertex_callback_)
							{
								general_polygon_vertex_callback_(float_3_tuple_type(vert_4_x, vert_4_y, vert_4_z));
							}
						}
						size_type number_of_vertices = 4;
						float_type vert_previous_x = vert_4_x, vert_previous_y = vert_4_y, vert_previous_z = vert_4_z;
						do
						{
							// vert
							std::getline(istream, line);
							if (istream)
							{
								++line_number;
								stringstream.clear();
								stringstream.str(line);
								float_type vert_x, vert_y, vert_z;
								char ws_vert_x_vert_y, ws_vert_y_vert_z;
								stringstream >> std::ws >> vert_x >> ws_vert_x_vert_y >> std::ws >> vert_y >> ws_vert_y_vert_z >> std::ws >> vert_z >> std::ws;
								if (stringstream && stringstream.eof() && std::isspace(ws_vert_x_vert_y) && std::isspace(ws_vert_y_vert_z))
								{
									++number_of_vertices;
									if (flags_ & triangulate_polygons)
									{
										if (triangular_polygon_callback_)
										{
											triangular_polygon_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(vert_previous_x, vert_previous_y, vert_previous_z), float_3_tuple_type(vert_x, vert_y, vert_z));
										}
										vert_previous_x = vert_x, vert_previous_y = vert_y, vert_previous_z = vert_z;
									}
									else
									{
										if (general_polygon_vertex_callback_)
										{
											general_polygon_vertex_callback_(float_3_tuple_type(vert_x, vert_y, vert_z));
										}
									}
								}
							}
						} while (istream && stringstream && (number_of_vertices < total_vertices));
						if (!istream || !stringstream)
						{
							if (error_callback_)
							{
								error_callback_(line_number, "parse error");
							}
							return false;
						}
						if (general_polygon_vertex_callback_)
						{
							general_polygon_end_callback_();
						}
					}
				}
				++number_of_p_entities;
			}

			// pp
			else if (keyword == "pp")
			{
				size_type total_vertices;
				char ws_pp_total_vertices;
				stringstream >> ws_pp_total_vertices >> std::ws >> total_vertices >> std::ws;
				if (!(stringstream && stringstream.eof() && std::isspace(ws_pp_total_vertices)))
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				if (total_vertices < 3)
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				// vert1
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				++line_number;
				stringstream.clear();
				stringstream.str(line);
				float_type vert_1_x, vert_1_y, vert_1_z, norm_1_x, norm_1_y, norm_1_z;
				char ws_vert_1_x_vert_1_y, ws_vert_1_y_vert_1_z, ws_vert_1_z_norm_1_x, ws_norm_1_x_norm_1_y, ws_norm_1_y_norm_1_z;
				stringstream >> std::ws >> vert_1_x >> ws_vert_1_x_vert_1_y >> std::ws >> vert_1_y >> ws_vert_1_y_vert_1_z >> std::ws >> vert_1_z >> ws_vert_1_z_norm_1_x >> std::ws >> norm_1_x >> ws_norm_1_x_norm_1_y >> std::ws >> norm_1_y >> ws_norm_1_y_norm_1_z >> std::ws >> norm_1_z >> std::ws;
				if (!(stringstream && stringstream.eof() && std::isspace(ws_vert_1_x_vert_1_y) && std::isspace(ws_vert_1_y_vert_1_z) && std::isspace(ws_vert_1_z_norm_1_x) && std::isspace(ws_norm_1_x_norm_1_y) && std::isspace(ws_norm_1_y_norm_1_z)))
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				// vert2
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				++line_number;
				stringstream.clear();
				stringstream.str(line);
				float_type vert_2_x, vert_2_y, vert_2_z, norm_2_x, norm_2_y, norm_2_z;
				char ws_vert_2_x_vert_2_y, ws_vert_2_y_vert_2_z, ws_vert_2_z_norm_2_x, ws_norm_2_x_norm_2_y, ws_norm_2_y_norm_2_z;
				stringstream >> std::ws >> vert_2_x >> ws_vert_2_x_vert_2_y >> std::ws >> vert_2_y >> ws_vert_2_y_vert_2_z >> std::ws >> vert_2_z >> ws_vert_2_z_norm_2_x >> std::ws >> norm_2_x >> ws_norm_2_x_norm_2_y >> std::ws >> norm_2_y >> ws_norm_2_y_norm_2_z >> std::ws >> norm_2_z >> std::ws;
				if (!(stringstream && stringstream.eof() && std::isspace(ws_vert_2_x_vert_2_y) && std::isspace(ws_vert_2_y_vert_2_z) && std::isspace(ws_vert_2_z_norm_2_x) && std::isspace(ws_norm_2_x_norm_2_y) && std::isspace(ws_norm_2_y_norm_2_z)))
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				// vert3
				std::getline(istream, line);
				if (!istream)
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				++line_number;
				stringstream.clear();
				stringstream.str(line);
				float_type vert_3_x, vert_3_y, vert_3_z, norm_3_x, norm_3_y, norm_3_z;
				char ws_vert_3_x_vert_3_y, ws_vert_3_y_vert_3_z, ws_vert_3_z_norm_3_x, ws_norm_3_x_norm_3_y, ws_norm_3_y_norm_3_z;
				stringstream >> std::ws >> vert_3_x >> ws_vert_3_x_vert_3_y >> std::ws >> vert_3_y >> ws_vert_3_y_vert_3_z >> std::ws >> vert_3_z >> ws_vert_3_z_norm_3_x >> std::ws >> norm_3_x >> ws_norm_3_x_norm_3_y >> std::ws >> norm_3_y >> ws_norm_3_y_norm_3_z >> std::ws >> norm_3_z >> std::ws;
				if (!(stringstream && stringstream.eof() && std::isspace(ws_vert_3_x_vert_3_y) && std::isspace(ws_vert_3_y_vert_3_z) && std::isspace(ws_vert_3_z_norm_3_x) && std::isspace(ws_norm_3_x_norm_3_y) && std::isspace(ws_norm_3_y_norm_3_z)))
				{
					if (error_callback_)
					{
						error_callback_(line_number, "parse error");
					}
					return false;
				}
				if (total_vertices == 3)
				{
					if (triangular_polygonal_patch_callback_)
					{
						triangular_polygonal_patch_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(norm_1_x, norm_1_y, norm_1_z), float_3_tuple_type(vert_2_x, vert_2_y, vert_2_z), float_3_tuple_type(norm_2_x, norm_2_y, norm_2_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z), float_3_tuple_type(norm_3_x, norm_3_y, norm_3_z));
					}
				}
				else
				{
					// vert4
					std::getline(istream, line);
					if (!istream)
					{
						if (error_callback_)
						{
							error_callback_(line_number, "parse error");
						}
						return false;
					}
					++line_number;
					stringstream.clear();
					stringstream.str(line);
					float_type vert_4_x, vert_4_y, vert_4_z, norm_4_x, norm_4_y, norm_4_z;
					char ws_vert_4_x_vert_4_y, ws_vert_4_y_vert_4_z, ws_vert_4_z_norm_4_x, ws_norm_4_x_norm_4_y, ws_norm_4_y_norm_4_z;
					stringstream >> std::ws >> vert_4_x >> ws_vert_4_x_vert_4_y >> std::ws >> vert_4_y >> ws_vert_4_y_vert_4_z >> std::ws >> vert_4_z >> ws_vert_4_z_norm_4_x >> std::ws >> norm_4_x >> ws_norm_4_x_norm_4_y >> std::ws >> norm_4_y >> ws_norm_4_y_norm_4_z >> std::ws >> norm_4_z >> std::ws;
					if (!(stringstream && stringstream.eof() && std::isspace(ws_vert_4_x_vert_4_y) && std::isspace(ws_vert_4_y_vert_4_z) && std::isspace(ws_vert_4_z_norm_4_x) && std::isspace(ws_norm_4_x_norm_4_y) && std::isspace(ws_norm_4_y_norm_4_z)))
					{
						if (error_callback_)
						{
							error_callback_(line_number, "parse error");
						}
						return false;
					}
					if (total_vertices == 4)
					{
						if (flags_ & triangulate_polygonal_patches)
						{
							if (triangular_polygonal_patch_callback_)
							{
								triangular_polygonal_patch_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(norm_1_x, norm_1_y, norm_1_z), float_3_tuple_type(vert_2_x, vert_2_y, vert_2_z), float_3_tuple_type(norm_2_x, norm_2_y, norm_2_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z), float_3_tuple_type(norm_3_x, norm_3_y, norm_3_z));
								triangular_polygonal_patch_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(norm_1_x, norm_1_y, norm_1_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z), float_3_tuple_type(norm_3_x, norm_3_y, norm_3_z), float_3_tuple_type(vert_4_x, vert_4_y, vert_4_z), float_3_tuple_type(norm_4_x, norm_4_y, norm_4_z));
							}
						}
						else
						{
							if (quadrilateral_polygonal_patch_callback_)
							{
								quadrilateral_polygonal_patch_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(norm_1_x, norm_1_y, norm_1_z), float_3_tuple_type(vert_2_x, vert_2_y, vert_2_z), float_3_tuple_type(norm_2_x, norm_2_y, norm_2_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z), float_3_tuple_type(norm_3_x, norm_3_y, norm_3_z), float_3_tuple_type(vert_4_x, vert_4_y, vert_4_z), float_3_tuple_type(norm_4_x, norm_4_y, norm_4_z));
							}
						}
					}
					else
					{
						if (flags_ & triangulate_polygonal_patches)
						{
							if (triangular_polygonal_patch_callback_)
							{
								triangular_polygonal_patch_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(norm_1_x, norm_1_y, norm_1_z), float_3_tuple_type(vert_2_x, vert_2_y, vert_2_z), float_3_tuple_type(norm_2_x, norm_2_y, norm_2_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z), float_3_tuple_type(norm_3_x, norm_3_y, norm_3_z));
								triangular_polygonal_patch_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(norm_1_x, norm_1_y, norm_1_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z), float_3_tuple_type(norm_3_x, norm_3_y, norm_3_z), float_3_tuple_type(vert_4_x, vert_4_y, vert_4_z), float_3_tuple_type(norm_4_x, norm_4_y, norm_4_z));
							}
						}
						else
						{
							if (general_polygonal_patch_begin_callback_)
							{
								general_polygonal_patch_begin_callback_(total_vertices, float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(norm_1_x, norm_1_y, norm_1_z), float_3_tuple_type(vert_2_x, vert_2_y, vert_2_z), float_3_tuple_type(norm_2_x, norm_2_y, norm_2_z), float_3_tuple_type(vert_3_x, vert_3_y, vert_3_z), float_3_tuple_type(norm_3_x, norm_3_y, norm_3_z));
							}
							if (general_polygonal_patch_vertex_callback_)
							{
								general_polygonal_patch_vertex_callback_(float_3_tuple_type(vert_4_x, vert_4_y, vert_4_z), float_3_tuple_type(norm_4_x, norm_4_y, norm_4_z));
							}
						}
						size_type number_of_vertices = 4;
						float_type vert_previous_x = vert_4_x, vert_previous_y = vert_4_y, vert_previous_z = vert_4_z;
						float_type norm_previous_x = norm_4_x, norm_previous_y = norm_4_y, norm_previous_z = norm_4_z;
						do
						{
							// vert
							std::getline(istream, line);
							if (istream)
							{
								++line_number;
								stringstream.clear();
								stringstream.str(line);
								float_type vert_x, vert_y, vert_z, norm_x, norm_y, norm_z;
								char ws_vert_x_vert_y, ws_vert_y_vert_z, ws_vert_z_norm_x, ws_norm_x_norm_y, ws_norm_y_norm_z;
								stringstream >> std::ws >> vert_x >> ws_vert_x_vert_y >> std::ws >> vert_y >> ws_vert_y_vert_z >> std::ws >> vert_z >> ws_vert_z_norm_x >> std::ws >> norm_x >> ws_norm_x_norm_y >> std::ws >> norm_y >> ws_norm_y_norm_z >> std::ws >> norm_z >> std::ws;
								if (stringstream && stringstream.eof() && std::isspace(ws_vert_x_vert_y) && std::isspace(ws_vert_y_vert_z) && std::isspace(ws_vert_z_norm_x) && std::isspace(ws_norm_x_norm_y) && std::isspace(ws_norm_y_norm_z))
								{
									++number_of_vertices;
									if (flags_ & triangulate_polygonal_patches)
									{
										if (triangular_polygonal_patch_callback_)
										{
											triangular_polygonal_patch_callback_(float_3_tuple_type(vert_1_x, vert_1_y, vert_1_z), float_3_tuple_type(norm_1_x, norm_1_y, norm_1_z), float_3_tuple_type(vert_previous_x, vert_previous_y, vert_previous_z), float_3_tuple_type(norm_previous_x, norm_previous_y, norm_previous_z), float_3_tuple_type(vert_x, vert_y, vert_z), float_3_tuple_type(norm_x, norm_y, norm_z));
										}
										vert_previous_x = vert_x, vert_previous_y = vert_y, vert_previous_z = vert_z;
										norm_previous_x = norm_x, norm_previous_y = norm_y, norm_previous_z = norm_z;
									}
									else
									{
										if (general_polygonal_patch_vertex_callback_)
										{
											general_polygonal_patch_vertex_callback_(float_3_tuple_type(vert_x, vert_y, vert_z), float_3_tuple_type(norm_x, norm_y, norm_z));
										}
									}
								}
							}
						} while (istream && stringstream && (number_of_vertices < total_vertices));
						if (!istream || !stringstream)
						{
							if (error_callback_)
							{
								error_callback_(line_number, "parse error");
							}
							return false;
						}
						if (general_polygonal_patch_end_callback_)
						{
							general_polygonal_patch_end_callback_();
						}
					}
				}
				++number_of_pp_entities;
			}

			// unknown keyword
			else
			{
				if (warning_callback_)
				{
					warning_callback_(line_number, "ignoring line ‘" + line + "’");
				}
			}

		}
	}

	return !istream.bad() && istream.eof();
}
