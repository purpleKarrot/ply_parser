#include "stream/stream.hpp"
#include <boost/fusion/adapted/struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(stream::attribute,
		(std::string, name)
		(stream::type_t, type)
		(std::size_t, array_size)
		(std::size_t, size_in_bytes)
		(std::size_t, flags)
)

BOOST_FUSION_ADAPT_STRUCT(stream::header,
		(stream::vec3, min)
		(stream::vec3, max)
		(boost::optional<stream::endian_type>, endian)
		//		(boost::optional<stream::mat4x4>, transform)
		//		(std::vector<stream::element>, elements)
)

BOOST_FUSION_ADAPT_STRUCT(stream::element,
		(std::string, name)
		(std::size_t, count)
		(std::size_t, offset)
		(std::vector<stream::attribute>, attributes)
)


BOOST_FUSION_ADAPT_STRUCT(stream::vec3,
		(float, x)
		(float, y)
		(float, z)
)

BOOST_FUSION_ADAPT_STRUCT(stream::mat4x4,
		(float, m[0])
		(float, m[1])
		(float, m[3])
		(float, m[4])
		(float, m[5])
		(float, m[6])
		(float, m[7])
		(float, m[8])
		(float, m[9])
		(float, m[10])
		(float, m[11])
		(float, m[12])
		(float, m[13])
		(float, m[14])
		(float, m[15])
		(float, m[16])
)
