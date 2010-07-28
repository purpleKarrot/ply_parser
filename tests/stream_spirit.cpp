#include <fstream>
#include <sstream>
#include <stream/stream.hpp>
#include <stream/stream_adapted.hpp>
#include <boost/test/unit_test.hpp>

#include <boost/fusion/adapted/struct.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace classic = boost::spirit::classic;

// http://boost-spirit.com/home/articles/qi-example/tracking-the-input-position-while-parsing/

struct endian_parser: boost::spirit::qi::symbols<char, stream::endian_type>
{
	endian_parser()
	{
		add
			("little", stream::little)
			("big",    stream::big)
		;
	}
} endian_;

struct type_parser: boost::spirit::qi::symbols<char, stream::type_t>
{
	type_parser()
	{
		add
			("float",   stream::float_)
			("double",  stream::double_)
			("uint8",   stream::uint8_)
			("int8",    stream::int8_)
			("uint16",  stream::uint16_)
			("int16",   stream::int16_)
			("uint32",  stream::uint32_)
			("int32",   stream::int32_)
			("uint64",  stream::uint64_)
			("int64",   stream::int64_)
			("unknown", stream::unknown_)
		;
	}
} type_;

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
	std::vector<double> output;

	BOOST_AUTO(comment, '#' >> *(ascii::char_ - qi::eol) >> qi::eol);
	BOOST_AUTO(skip, ascii::space | comment);

	qi::rule<pos_iterator_type, stream::vec3(), BOOST_TYPEOF(skip)> vec3_;
	vec3_ %= qi::float_ > qi::float_ > qi::float_;

	qi::rule<pos_iterator_type, stream::mat4x4(), BOOST_TYPEOF(skip)> mat4x4_;
	mat4x4_ %= qi::float_ >> qi::float_ >> qi::float_ >> qi::float_ >> qi::float_
				>> qi::float_ >> qi::float_ >> qi::float_ >> qi::float_
				>> qi::float_ >> qi::float_ >> qi::float_ >> qi::float_
				>> qi::float_ >> qi::float_ >> qi::float_;

	qi::rule<pos_iterator_type, stream::vec3(), BOOST_TYPEOF(skip)> min_;
	min_ %= qi::lit("min") > vec3_;

	qi::rule<pos_iterator_type, stream::vec3(), BOOST_TYPEOF(skip)> max_;
	max_ %= qi::lit("max") > vec3_;

	qi::rule<pos_iterator_type, stream::endian_type(), BOOST_TYPEOF(skip)> mendian_;
	mendian_ %= qi::lit("endian") > endian_;

	qi::rule<pos_iterator_type, stream::mat4x4(), BOOST_TYPEOF(skip)> transform_;
	transform_ %= qi::lit("transform") > mat4x4_;

	qi::rule<pos_iterator_type, stream::header(), BOOST_TYPEOF(skip)> header_;
	header_ %= qi::eps > min_ > max_ > -mendian_ > -transform_ > qi::lit("element");

	// parse
	try
	{
		qi::phrase_parse(position_begin, position_end, header_, skip, header);
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

	BOOST_MESSAGE("min " << header.min.x << " " << header.min.y << " " << header.min.z);
	BOOST_MESSAGE("max " << header.max.x << " " << header.max.y << " " << header.max.z);
	BOOST_MESSAGE("endian " << header.endian);
}
