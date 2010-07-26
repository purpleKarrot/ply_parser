#ifndef STREAM_HPP
#define STREAM_HPP

#include <string>
#include <vector>
#include <boost/optional.hpp>
//#include <boost/la/all.hpp>

namespace stream
{

struct vec3
{
	float x, y, z;
};

struct mat4x4
{
	float m[16];
};

//typedef boost::la::vec<float, 3> vec3;
//typedef boost::la::mat<float, 4, 4> mat4x4;

enum endian_t
{
	little, big
};

enum type_t
{
	float_,
	double_,
	uint8_,
	int8_,
	uint16_,
	int16_,
	uint32_,
	int32_,
	uint64_,
	int64_,
	unknown_,
};

struct attribute
{
	std::string name;
	type_t type;
	std::size_t array_size;
	std::size_t size_in_bytes;
	std::size_t flags;
};

struct element
{
	std::string name;
	std::size_t count;
	std::size_t offset;
	std::vector<attribute> attributes;
};

struct header
{
	vec3 min, max;
	endian_t endian;
	mat4x4 transform;
	std::vector<element> elements;
};

} // namespace stream

#endif /* STREAM_HPP */
