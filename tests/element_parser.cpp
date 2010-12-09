/*
 * element_parser.cpp
 *
 *  Created on: Aug 3, 2010
 *      Author: danielp
 */

#include <junk/iterator.hpp>
#include <junk/element_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <fstream>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace phoenix = boost::phoenix;

using namespace qi::labels;

template<typename Iterator, typename Skipper>
struct list_grammar: boost::spirit::qi::grammar<Iterator, std::vector<int>(), qi::locals<int>, Skipper>
{
	list_grammar() :
		list_grammar::base_type(start)
	{
		start %= qi::eps[phoenix::clear(_val)] > size_(_a) > list_(_a) > qi::eol;
		size_ %= qi::omit[qi::int_[_r1 = _1]];
		list_ %= qi::repeat(_r1)[qi::int_];
	}

	boost::spirit::qi::rule<Iterator, std::vector<int>(), qi::locals<int>, Skipper> start;
	boost::spirit::qi::rule<Iterator, void(int&), Skipper> size_;
	boost::spirit::qi::rule<Iterator, std::vector<int>(int), Skipper> list_;
};

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

	//	typedef boost::fusion::vector<int, int, int> element_type;
	//	element_type element;
	//
	//	typedef qi::rule<iterator_type, element_type(), skipper_type> grammar_type;
	//	grammar_type grammar;
	//	grammar %= qi::eps > "3" > qi::int_ > qi::int_ > qi::int_ > qi::eol;

	typedef std::vector<int> element_type;
	element_type element;

	typedef list_grammar<iterator_type, skipper_type> grammar_type;
	//	typedef qi::rule<iterator_type, element_type(), qi::locals<int>, skipper_type> grammar_type;
	grammar_type grammar;
	//	grammar %= qi::eps > qi::int_[_a = _1] > qi::repeat(_a)[qi::int_] > qi::eol;

	typedef element_phrase_parser<element_type, iterator_type, skipper_type> parser_type;
	boost::shared_ptr<parser_type> parser(new parser_type(fwd_begin, fwd_end, grammar, skipper, 5));

	//	while (parser->parse(element))
	//	{
	//		BOOST_MESSAGE("element: " << element);
	//	}

	typedef iterator<element_type, parser_type> e_iterator_type;
	for (e_iterator_type i(parser); i != e_iterator_type(); ++i)
	{
		BOOST_MESSAGE(i->size() << ": " << (*i)[0]<< ", " << (*i)[1]<< ", " << (*i)[2]);
	}
}
