#include <fstream>
#include <sstream>
#include <stream/stream.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace classic = boost::spirit::classic;

// http://boost-spirit.com/home/articles/qi-example/tracking-the-input-position-while-parsing/

BOOST_AUTO_TEST_CASE(stream_spirit)
{
	std::ifstream file("stream.stream");
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
	pos_iterator_type position_begin(fwd_begin, fwd_end, "filename");
	pos_iterator_type position_end;

	// prepare output
	stream::header header;

	// parse
	try
	{
		qi::phrase_parse(position_begin, position_end,                      // iterators over input
				qi::double_ > *(',' > qi::double_) >> qi::eoi,              // recognize list of doubles
				ascii::space | '#' >> *(ascii::char_ - qi::eol) >> qi::eol  // comment skipper
				/*, output*/ );                                             // doubles are stored into this object
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
}
