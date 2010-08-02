/*
 * element.hpp
 *
 *  Created on: 02.08.2010
 *      Author: daniel
 */

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/container/vector.hpp>

namespace ply
{

template<typename Properties>
struct element
{
	typedef boost::mpl::if_<boost::fusion::traits::is_sequence<Properties>,
		Properties, boost::fusion::vector<Properties> > properties;



	//	BOOST_MPL_ASSERT((boost::fusion::traits::is_sequence<Properties>));
};

} // namespace ply

#endif /* ELEMENT_HPP */
