#include <boost/test/unit_test.hpp>
#include <boost/spirit/include/qi.hpp>

namespace qi = boost::spirit::qi;
//namespace ascii = boost::spirit::ascii;
//using namespace qi::labels;

template<typename P>
bool test_parser(char const* input, P const& p)
{
	using boost::spirit::qi::parse;
	char const* f(input);
	char const* l(f + strlen(f));
	return parse(f, l, p);
}

template<typename P, typename Attr>
bool test_parser(char const* input, P const& p, Attr const& expected)
{
	using boost::spirit::qi::parse;
	char const* f(input);
	char const* l(f + strlen(f));
	Attr attr;
	return parse(f, l, p, attr) && f == l && attr == expected;
}

BOOST_AUTO_TEST_CASE(rule)
{
	qi::rule<char const*, void()> grammar;

	grammar = qi::lit('B');
	grammar = qi::lit('A') > grammar.copy();
	grammar = grammar.copy() > qi::lit('C');

	BOOST_CHECK(test_parser("ABC", qi::eps > grammar));
}
