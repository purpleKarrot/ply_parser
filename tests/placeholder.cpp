/*
 * placeholder.cpp
 *
 *  Created on: Aug 10, 2010
 *      Author: danielp
 */

#include <boost/test/unit_test.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

template<typename P, typename Attr>
void test_parser(char const* input, P const& p, Attr const& expected)
{
	char const* f(input);
	char const* l(f + strlen(f));

	Attr attr;
	BOOST_CHECK(qi::phrase_parse(f, l, p, ascii::space, attr));
	BOOST_CHECK(f == l);
	BOOST_CHECK_EQUAL(attr, expected);
}

BOOST_AUTO_TEST_CASE(placeholder)
{
	qi::rule<char const*, int(void), ascii::space_type> grammar;
	grammar	= (qi::int_ > qi::int_)[qi::_val = (qi::_1 + qi::_2)];

	test_parser("7 5", grammar, 12);
	test_parser("1 2", grammar,  3);

	//	std::string input("7,5");
	//	std::string::const_iterator begin = input.begin();
	//	std::string::const_iterator end = input.end();
	//	qi::parse(begin, end,
	//	    (qi::int_ >> ',' >> qi::int_)
	//	    [
	//	        std::cout << "Sum: " << qi::_1 + qi::_2 << "\n"
	//	    ]
	//	);
}
