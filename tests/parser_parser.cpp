/*
 * element_parser.cpp
 *
 *  Created on: Aug 3, 2010
 *      Author: danielp
 */

#include <precompiled.hpp>

#include <iterator.hpp>
#include <element_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <fstream>

#include <ply/symbols.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;
using namespace qi::labels;

template<typename T, typename Iterator, typename Skipper>
struct rule
{
	typedef qi::rule<Iterator, T(), Skipper> type;
	typedef ply::scalar_symbols<type> symbol;
//	typedef qi::symbols<char, type> parser;
};

BOOST_AUTO_TEST_CASE(parser_parser)
{
	std::ifstream file("parser.txt");

	// iterate over stream input
	typedef std::istreambuf_iterator<char> base_iterator_type;
	base_iterator_type in_begin(file);

	// convert input iterator to forward iterator, usable by spirit parser
	typedef boost::spirit::multi_pass<base_iterator_type> iterator_type;
	iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin);
	iterator_type fwd_end;

	typedef BOOST_TYPEOF(ascii::blank) skipper_type;
	skipper_type skipper = ascii::blank;

	typedef rule<int, iterator_type, skipper_type> rule_type;

	rule_type::symbol type_parser;

//	type_parser.add
//		("int", qi::int_)
//		("short", qi::short_)
//		("ushort", qi::ushort_)
//		("double", qi::double_)
//	;

	rule_type::type rule;

	int value;

	int lines = 6;

	while (lines--)
	{
		BOOST_REQUIRE(qi::phrase_parse(fwd_begin, fwd_end, type_parser, skipper, rule));
		BOOST_REQUIRE(qi::phrase_parse(fwd_begin, fwd_end, rule>qi::eol, skipper, value));
		BOOST_MESSAGE(value);
	}
}
