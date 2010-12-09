/*
 * spirit.hpp
 *
 *  Created on: Jul 28, 2010
 *      Author: danielp
 */

#ifndef PLY_TYPES_HPP
#define PLY_TYPES_HPP

#include <string>
#include <vector>
#include <boost/variant.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>

namespace ply
{

enum scalar
{
	// size types
	uint8,
	uint16,
	uint32,
	uint64,

	int8,
	int16,
	int32,
	int64,

	float32,
	float64
};

enum format
{
	ascii, binary_little_endian, binary_big_endian
};

} // namespace ply

BOOST_FUSION_DEFINE_STRUCT((ply), list,
		(ply::scalar, count)
		(ply::scalar, data)
)

namespace ply
{
typedef boost::variant<list, scalar> property_type;
}

BOOST_FUSION_DEFINE_STRUCT((ply), property,
		(ply::property_type, type)
		(std::string, name)
)

BOOST_FUSION_DEFINE_STRUCT((ply), element,
		(std::string, name)
		(std::size_t, count)
		(std::vector<ply::property>, properties)
)

BOOST_FUSION_DEFINE_STRUCT((ply), header,
		(ply::format, format)
		(double, version)
		(std::vector<ply::element>, elements)
)

#endif /* PLY_TYPES_HPP */
