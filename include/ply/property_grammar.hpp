/*
 * property_grammar.hpp
 *
 *  Created on: 16.12.2010
 *      Author: daniel
 */

#ifndef PLY_PROPERTY_GRAMMAR_HPP
#define PLY_PROPERTY_GRAMMAR_HPP

#include <ply/types.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <ply/property_parsers.hpp>

namespace ply
{
namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

template<typename Iterator, typename Skipper>
struct list_grammar: qi::grammar<Iterator, void(), qi::locals<std::size_t>, Skipper>
{
	list_grammar() :
		list_grammar::base_type(start)
	{
		using namespace qi::labels;
		start %= size_(_a) > list_(_a);
		size_ %= qi::omit[qi::int_[_r1 = _1]];
		list_ %= qi::omit[qi::repeat(_r1)[qi::int_]];
	}

	qi::rule<Iterator, void(), qi::locals<std::size_t>, Skipper> start;
	qi::rule<Iterator, void(std::size_t&), Skipper> size_;
	qi::rule<Iterator, void(std::size_t), Skipper> list_;
};

template<typename Iterator, typename Skipper, typename Element>
class property_grammar: public qi::grammar<Iterator, void(Element&), Skipper>
{
	typedef parser_factory<Iterator, Skipper> factory;

public:
	property_grammar() :
		property_grammar::base_type(start)
	{
	}

	// initialize the parser to omit the parsed value
	void omit(/*ply::format format,*/ply::property_type const& property_type)
	{
		typedef typename factory::template visitor<void>::type visitor;
		start = boost::apply_visitor(visitor(ply::ascii), property_type);
	}

	// initialize the parser to write parsed value into Element at I
	template<typename I, typename Rule>
	void init(I, Rule& rule, /*ply::format format,*/ply::property_type const& property_type)
	{
		typedef typename boost::fusion::result_of::at<Element, I>::type type;
		typedef typename factory::template visitor<type>::type visitor;

		rule = boost::apply_visitor(visitor(ply::ascii), property_type);
		start = rule(ph::at_c<I::value>(qi::_r1));
	}

private:
	qi::rule<Iterator, void(Element&), Skipper> start;
};

} // namespace ply

#endif /* PLY_PROPERTY_GRAMMAR_HPP */
