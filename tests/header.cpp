
#include <ply/header_grammar.hpp>

#include <fstream>
#include <sstream>
#include <boost/test/unit_test.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace classic = boost::spirit::classic;

BOOST_AUTO_TEST_CASE(header)
{
	std::ifstream file("bunny.ply");
	BOOST_REQUIRE(file);

	// iterate over stream input
	typedef std::istreambuf_iterator<char> base_iterator_type;
	base_iterator_type in_begin(file);

	// convert input iterator to forward iterator, usable by spirit parser
	typedef boost::spirit::multi_pass<base_iterator_type> forward_iterator_type;
	forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin);
	forward_iterator_type fwd_end;

	// wrap forward iterator with position iterator, to record the position
	typedef classic::position_iterator2<forward_iterator_type> pos_iterator_type;
	pos_iterator_type position_begin(fwd_begin, fwd_end, "bunny.ply");
	pos_iterator_type position_end;

	// prepare output
	ply::header header;

	BOOST_AUTO(comment, qi::lit("comment") >> *(ascii::char_ - qi::eol) >> qi::eol);
	BOOST_AUTO(skip, ascii::blank | comment);

	ply::header_grammar<pos_iterator_type, BOOST_TYPEOF(skip)> grammar;

	// parse
	try
	{
		qi::phrase_parse(position_begin, position_end, grammar, skip, header);
	}
	catch (const qi::expectation_failure<pos_iterator_type>& e)
	{
		const classic::file_position_base<std::string>& pos = e.first.get_position();

		std::stringstream msg;
		msg << "parse error at file " << pos.file << " line " << pos.line << " column " << pos.column << std::endl;
		msg << "'" << e.first.get_currentline() << "'" << std::endl;
		msg << std::setw(pos.column) << " " << "^- here";

		BOOST_FAIL(msg.str());
	}

	BOOST_MESSAGE(header.elements[0].name << " " << header.elements[0].count);
	BOOST_MESSAGE(header.elements[1].name << " " << header.elements[1].count);
}
