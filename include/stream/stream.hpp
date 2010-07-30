#ifndef STREAM_HPP
#define STREAM_HPP

#include <string>
#include <vector>
#include <boost/optional.hpp>

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

enum endian_type
{
	little, big
};

enum type_t
{
	float_, double_, uint8_, int8_, uint16_, int16_, uint32_, int32_, uint64_, int64_, unknown_,
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
	int count;
	boost::optional<int> offset;
	std::vector<attribute> attributes;
};

struct header
{
	vec3 min, max;
	boost::optional<endian_type> endian;
	boost::optional<mat4x4> transform;
	std::vector<element> elements;
};

} // namespace stream

#endif /* STREAM_HPP */
