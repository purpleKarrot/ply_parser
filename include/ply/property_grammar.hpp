/*
 * property_grammar.hpp
 *
 *  Created on: 16.12.2010
 *      Author: daniel
 */

#ifndef PLY_PROPERTY_GRAMMAR_HPP
#define PLY_PROPERTY_GRAMMAR_HPP

#include <ply/types.hpp>

namespace ply
{

template<typename Iterator, typename Skipper>
struct list_grammar: qi::grammar<Iterator, void(), qi::locals<std::size_t>,
		Skipper>
{
	list_grammar() :
		list_grammar::base_type(start)
	{
		start %= size_(_a) > list_(_a);
		size_ %= qi::omit[qi::int_[_r1 = _1]];
		list_ %= qi::omit[qi::repeat(_r1)[qi::int_]];
	}

	qi::rule<Iterator, void(), qi::locals<std::size_t>, Skipper> start;
	qi::rule<Iterator, void(std::size_t&), Skipper> size_;
	qi::rule<Iterator, void(std::size_t), Skipper> list_;
};

template<typename Iterator, typename Element, typename Skipper>
class property_grammar: public qi::grammar<Iterator, void(Element&), Skipper>
{
public:
	property_grammar() :
		property_grammar::base_type(start)
	{
	}

	// initialize the parser to omit the parsed value
	void omit(ply::format format, ply::property_type const& property_type)
	{
		start = list_grammar<Iterator, Skipper> ();
	}

	// initialize the parser to write parsed value into Element at I
	template<typename I>
	void init(ply::format format, ply::property_type const& property_type)
	{
		typename boost::fusion::result_of::at<I, Element>::type wanted_type;
	}

private:
	typedef qi::rule<Iterator, void(Element&), Skipper> rule_type;
	rule_type start;
};

} // namespace ply

#endif /* PLY_PROPERTY_GRAMMAR_HPP */
