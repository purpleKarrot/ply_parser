#include <boost/test/unit_test.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
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

namespace
{

int i1 = 0, i2 = 0, i3 = 0;

typedef qi::rule<char const*, void(), ascii::space_type> grammar_type;

grammar_type grammar;

void append_parser(int const& i)
{
	using boost::phoenix::ref;
	using boost::spirit::qi::_1;

	grammar_type g;

	switch (i)
	{
	case 1:
		g = qi::int_[ref(i1) = _1];
		break;
	case 2:
		g = qi::int_[ref(i2) = _1];
		break;
	case 3:
		g = qi::int_[ref(i3) = _1];
		break;
	default:
		g = qi::int_;
	}

	grammar = grammar.copy() > g.copy();
}

} // namespace

BOOST_AUTO_TEST_CASE(rule)
{
	//	grammar = qi::lit('B');
	//	grammar = qi::lit('A') > grammar.copy();
	//	grammar = grammar.copy() > qi::lit('C');
	//	BOOST_CHECK(test_parser("ABC", qi::eps > grammar));

	grammar = qi::eps;

	{
		const char* begin = "1 0 4 9 3 5";
		const char* end = begin + strlen(begin);
		BOOST_CHECK(qi::phrase_parse(begin, end, *qi::int_[&append_parser], ascii::space));
	}

	{
		const char* begin = "123 345 456 678 78 80";
		const char* end = begin + strlen(begin);
		BOOST_CHECK(qi::phrase_parse(begin, end, grammar, ascii::space));
	}

	BOOST_MESSAGE(i1 << " " << i2 << " " << i3);
}
