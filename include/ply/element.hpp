/*
 * element.hpp
 *
 *  Created on: 02.08.2010
 *      Author: daniel
 */

#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <boost/fusion/sequence.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

//template<typename Seq, int N>
//boost::fusion::extension::struct_member_name<Seq, N>::type member_name()
//{
//	return boost::fusion::extension::struct_member_name<Seq, N>::call();
//}

namespace ply
{

template<typename Properties>
struct element
{
	typedef typename boost::fusion::result_of::as_vector<Properties>::type properties_type;

	template<typename Iterator, typename Skipper>
	struct rules
	{
		template<typename T>
		struct rule
		{
			typedef boost::spirit::qi::rule<Iterator, T(), Skipper> type;
		};

		typedef typename boost::mpl::transform<properties_type, rule<boost::mpl::_1> >::type type;
	};
};

} // namespace ply

#endif /* ELEMENT_HPP */
