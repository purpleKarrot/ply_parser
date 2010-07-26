/*
 * fusion_mat.hpp
 *
 *  Created on: Jul 22, 2010
 *      Author: danielp
 */

#ifndef ADAPT_LA_VEC_HPP
#define ADAPT_LA_VEC_HPP

#include <boost/la/all.hpp>
#include <boost/fusion/adapted/class.hpp>

#define ADAPT_LA_VEC_2(vec) \
	ADAPT_LA_VEC_2_I(vec, boost::la::vector_traits<vec>::scalar_type)

#define ADAPT_LA_VEC_3(vec) \
	ADAPT_LA_VEC_3_I(vec, boost::la::vector_traits<vec>::scalar_type)

#define ADAPT_LA_VEC_4(vec) \
	ADAPT_LA_VEC_4_I(vec, boost::la::vector_traits<vec>::scalar_type)


#define ADAPT_LA_VEC_2_I(vec, type)  BOOST_FUSION_ADAPT_CLASS(vec, \
		(type, type, obj|boost::la::X, obj|boost::la::X) \
		(type, type, obj|boost::la::Y, obj|boost::la::Y) )

#define ADAPT_LA_VEC_3_I(vec, type)  BOOST_FUSION_ADAPT_CLASS(vec, \
		(type, type, obj|boost::la::X, obj|boost::la::X) \
		(type, type, obj|boost::la::Y, obj|boost::la::Y) \
		(type, type, obj|boost::la::Z, obj|boost::la::Z) )

#define ADAPT_LA_VEC_4_I(vec, type)  BOOST_FUSION_ADAPT_CLASS(vec, \
		(type, type, obj|boost::la::X, obj|boost::la::X) \
		(type, type, obj|boost::la::Y, obj|boost::la::Y) \
		(type, type, obj|boost::la::Z, obj|boost::la::Z) \
		(type, type, obj|boost::la::W, obj|boost::la::W) )

#endif /* ADAPT_LA_VEC_HPP */
