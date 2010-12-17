/*
 * meta.hpp
 *
 *  Created on: Dec 17, 2010
 *      Author: danielp
 */

#ifndef PLY_META_HPP
#define PLY_META_HPP

#include <ply/types.hpp>
#include <boost/cstdint.hpp>

namespace ply
{

template<ply::scalar>
struct c_type
{
};

#define PLY_C_TYPE(S, T) template<> struct c_type<S> { typedef T type; };

PLY_C_TYPE(ply::int8, boost::int8_t)
PLY_C_TYPE(ply::int16, boost::int16_t)
PLY_C_TYPE(ply::int32, boost::int32_t)
PLY_C_TYPE(ply::int64, boost::int64_t)
PLY_C_TYPE(ply::uint8, boost::uint8_t)
PLY_C_TYPE(ply::uint16, boost::uint16_t)
PLY_C_TYPE(ply::uint32, boost::uint32_t)
PLY_C_TYPE(ply::uint64, boost::uint64_t)
PLY_C_TYPE(ply::float32, float)
PLY_C_TYPE(ply::float64, double)

#undef PLY_C_TYPE

} // namespace ply

#endif /* PLY_META_HPP */
