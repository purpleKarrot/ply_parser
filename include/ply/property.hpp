/*
 * property.hpp
 *
 *  Created on: 02.08.2010
 *      Author: daniel
 */

#ifndef PROPERTY_HPP
#define PROPERTY_HPP

#include <boost/cstdint.hpp>
#include <boost/mpl/if.hpp>

#include <vector>
#include <boost/array.hpp>

namespace ply
{

typedef boost::int8_t int8;
typedef boost::uint8_t uint8;

typedef boost::int16_t int16;
typedef boost::uint16_t uint16;

typedef boost::int32_t int32;
typedef boost::uint32_t uint32;

typedef boost::int64_t int64;
typedef boost::uint64_t uint64;

typedef float float32;
typedef double float64;

template<typename SizeType, typename ElementType, SizeType Size = 0>
struct list: boost::mpl::if_c<Size == 0, //
	std::vector<ElementType>, boost::array<ElementType, Size> >
{
	//	typedef SizeType size_type;
	//	typedef ElementType element_type;
	//	typedef typename boost::mpl::bool_<Size != 0>::type fixed_size;
};

} // namespace ply

#endif /* PROPERTY_HPP */
