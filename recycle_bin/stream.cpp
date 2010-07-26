/*
 * main.cpp
 *
 *  Created on: Jul 22, 2010
 *      Author: danielp
 */

#define FUSION_MAX_VECTOR_SIZE 20

#include "stream_adapted.hpp"
#include <boost/fusion/adapted/struct.hpp>

#include <boost/spirit/include/qi.hpp>
namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

#include <boost/spirit/home/phoenix/core/reference.hpp>
#include <boost/spirit/home/phoenix/operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>


std::string header = //
//	"# stream_process data set header\n"
//	"\n"
//	"# == globals ==\n"
//	"\n"
//	"min -0.12144980579614639 0.03641635924577713 0.041934516280889511\n"
//	"max 0.034249193966388702 0.15708965063095093 0.19626812636852264\n"
//	"\n"
//	"endian big\n"
//	"\n"
//	"transform 1 0 0 -0.026759909465909004 0 0 -1 0.095216058194637299 0 1 0 0.008947114460170269 0 0 0 1\n"
	"\n"
	"# == vertex ==\n"
	"\n"
	"element vertex\n"
//	"vertex count 35947\n"
//	"vertex offset 0\n"
//	"\n"
//	"# element, attribute-identifier, name, type,  array_size, size_in_bytes, flags\n"
//	"vertex attribute    position        float           3       12      0\n"
//	"vertex attribute    confidence      float           1       4       0\n"
//	"vertex attribute    intensity       float           1       4       0\n"
	"\n"
	"# == face ==\n"
	"\n"
	"element face\n"
//	"face count 69451\n"
//	"\n"
//	"# element, attribute-identifier, name, type,  array_size, size_in_bytes, flags\n"
//	"face attribute      vertex_indices  uint32          3       12      0\n"
;

struct endian_: boost::spirit::qi::symbols<char, stream::endian_t>
{
	endian_()
	{
		add("little", stream::little)("big", stream::big);
	}
} endian_parser;

struct type_: boost::spirit::qi::symbols<char, stream::type_t>
{
	type_()
	{
		add
			("float", stream::float_)
			("double", stream::double_)
			("uint8", stream::uint8_)
			("int8", stream::int8_)
			("uint16", stream::uint16_)
			("int16", stream::int16_)
			("uint32", stream::uint32_)
			("int32", stream::int32_)
			("uint64", stream::uint64_)
			("int64", stream::int64_)
			("unknown", stream::unknown_)
		;
	}
} type_parser;


//start %= qi::lit("vertex") >> qi::lit("attribute") >> *(ascii::char_
//		- type_parser) >> type_parser >> qi::int_ >> qi::int_
//		>> qi::int_;


template<typename Iterator, typename Skip>
struct element_parser: qi::grammar<Iterator, stream::element(), Skip>
{
	element_parser() :
		element_parser::base_type(start, "element")
	{
		using qi::_val;
		using qi::_1;
		using boost::phoenix::at_c;

		string_ %= qi::lexeme[+(ascii::char_ - ascii::space)];
//		count_ %= qi::lit(at_c<0> (_val)) >> qi::lit("count") >> qi::int_;
//		offset_ %= qi::lit(at_c<0> (_val)) >> qi::lit("offset") >> qi::int_;

		test = qi::lit("element") >> string_[at_c<0> (_val) = _1];
	//	>> count_ >> -offset_;


	}

	qi::rule<Iterator, std::string(), Skip> string_;

	qi::rule<Iterator, int, Skip> count_;
	qi::rule<Iterator, int, Skip> offset_;

	qi::rule<Iterator, stream::element(), Skip> start;
	qi::rule<Iterator, Skip> test;
};

template<typename Iterator, typename Skip>
struct header_parser: qi::grammar<Iterator, stream::header(), Skip>
{
	header_parser() :
		header_parser::base_type(start)
	{
		vec3_ %= qi::float_ >> qi::float_ >> qi::float_;
		start %= qi::lit("min") >> vec3_ >> qi::lit("max") >> vec3_;
	}

	qi::rule<Iterator, stream::vec3(), Skip> vec3_;
	qi::rule<Iterator, stream::header(), Skip> start;
};


int main(int argc, char* argv[])
{
	BOOST_AUTO(comment, '#' >> *(qi::char_ - qi::eol) >> qi::eol);
	BOOST_AUTO(skip, ascii::space | comment);


//	BOOST_AUTO(vec3_, qi::float_ >> qi::float_ >> qi::float_);

	typedef std::string::const_iterator iterator_type;
	typedef element_parser<iterator_type, BOOST_TYPEOF(skip)> parser;


	qi::rule<iterator_type, stream::vec3(), BOOST_TYPEOF(skip)> vec3_;
	vec3_ %= qi::float_ >> qi::float_ >> qi::float_;

//	qi::rule<iterator_type, stream::mat4x4(), BOOST_TYPEOF(skip)> mat4x4_;
//	vec3_ %= qi::float_ >> qi::float_ >> qi::float_ >> qi::float_ >> qi::float_
//			>> qi::float_ >> qi::float_ >> qi::float_ >> qi::float_
//			>> qi::float_ >> qi::float_ >> qi::float_ >> qi::float_
//			>> qi::float_ >> qi::float_ >> qi::float_;

	//			(
	//				qi::lit("min") >> vec3_[ref(att.min) = _1]
	//		     >> qi::lit("max") >> vec3_[ref(att.max) = _1]
	//   		     >> -(qi::lit("endian") >> endian_parser[ref(att.endian) = _1])
	////   		     >> -(qi::lit("transform") >> mat4x4_[ref(att.transform) = _1])
	//			)

	parser g; // Our grammar

	stream::element att;
	std::string::const_iterator iter = header.begin();
	std::string::const_iterator end = header.end();

	using qi::_1;
	using boost::phoenix::ref;

	while (qi::phrase_parse(iter, end, g, skip, att))
	{
		std::cout << "\n-------------------------\n";
		std::cout << boost::fusion::tuple_open('[');
		std::cout << boost::fusion::tuple_close(']');
		std::cout << boost::fusion::tuple_delimiter(", ");

std::cout << att.name<<std::endl;

//		std::cout << "min: " << boost::fusion::as_vector(att.min) << '\n';
//		std::cout << "max: " << boost::fusion::as_vector(att.max) << '\n';
//		std::cout << "endian: " << att.endian << '\n';
////		std::cout << "transform: " << boost::fusion::as_vector(att.transform) << '\n';

		std::cout << "\n-------------------------\n";
		std::cout << std::flush;
	}
}
