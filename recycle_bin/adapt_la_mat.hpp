/*
 * fusion_mat.hpp
 *
 *  Created on: Jul 22, 2010
 *      Author: danielp
 */

#ifndef ADAPT_LA_MAT_HPP
#define ADAPT_LA_MAT_HPP

#include <boost/la/all.hpp>
#include <boost/fusion/adapted/class.hpp>

typedef boost::la::mat<float, 4, 4> mat4x4;

BOOST_FUSION_ADAPT_CLASS(mat4x4,
		(float, float, obj.imag(), /**/)
		(float, float, obj.real(), /**/)
		(float, float, obj.imag(), /**/)
)

#endif /* ADAPT_LA_MAT_HPP */
