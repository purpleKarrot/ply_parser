/*
 * element_parser.cpp
 *
 *  Created on: Aug 3, 2010
 *      Author: danielp
 */

#include <iterator.hpp>
#include <element_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <fstream>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

BOOST_AUTO_TEST_CASE(elem_parser)
{
	std::ifstream file("faces.txt");

	// iterate over stream input
	typedef std::istreambuf_iterator<char> base_iterator_type;
	base_iterator_type in_begin(file);

	// convert input iterator to forward iterator, usable by spirit parser
	typedef boost::spirit::multi_pass<base_iterator_type> iterator_type;
	iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin);
	iterator_type fwd_end;

	typedef BOOST_TYPEOF(ascii::blank) skipper_type;
	skipper_type skipper = ascii::blank;

	typedef boost::fusion::vector<int, int, int> element_type;
	element_type element;

	typedef qi::rule<iterator_type, element_type(), skipper_type> grammar_type;
	grammar_type grammar;
	grammar %= qi::eps > "3" > qi::int_ > qi::int_ > qi::int_ > qi::eol;

	typedef element_parser<element_type, iterator_type, skipper_type> parser_type;
	boost::shared_ptr<parser_type> parser(new parser_type(fwd_begin, fwd_end, grammar, skipper, 5));

	//	while (parser->parse(element))
	//	{
	//		BOOST_MESSAGE("element: " << element);
	//	}

	typedef iterator<element_type, parser_type> e_iterator_type;
	for (e_iterator_type i(parser); i != e_iterator_type(); ++i)
	{
		BOOST_MESSAGE("element: " << *i);
	}
}
