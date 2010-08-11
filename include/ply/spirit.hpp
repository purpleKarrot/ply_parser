/*
 * spirit.hpp
 *
 *  Created on: Jul 28, 2010
 *      Author: danielp
 */

#ifndef PLY_SPIRIT_HPP
#define PLY_SPIRIT_HPP

#include <string>
#include <vector>
#include <boost/variant.hpp>

namespace ply
{

enum data_type
{
	int8, uint8, int16, uint16, int32, uint32, float32, float64
};

enum format_type
{
	ascii, binary_little_endian, binary_big_endian
};

struct format_version
{
	format_type format;
	double version;
};

struct list_type
{
	data_type t1;
	data_type t2;
};

typedef boost::variant<list_type, data_type> single_or_list_type;

struct property
{
	single_or_list_type type;
	std::string name;
};

struct element
{
	std::string name;
	int count;
	std::vector<property> properties;
};

struct header
{
	format_version format;
	std::vector<element> elements;
};

} // namespace ply

#include <boost/fusion/adapted/struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(ply::format_version,
		(ply::format_type, format)
		(double, version)
)

BOOST_FUSION_ADAPT_STRUCT(ply::list_type,
		(ply::data_type, t1)
		(ply::data_type, t2)
)

BOOST_FUSION_ADAPT_STRUCT(ply::header,
		(ply::format_version, format)
		(std::vector<ply::element>, elements)
)

BOOST_FUSION_ADAPT_STRUCT(ply::property,
		(ply::single_or_list_type, type)
		(std::string, name)
)

BOOST_FUSION_ADAPT_STRUCT(ply::element,
		(std::string, name)
		(int, count)
		(std::vector<ply::property>, properties)
)

#include <boost/spirit/include/qi.hpp>

namespace ply
{

template<typename Iterator, typename Skipper>
struct header_grammar: boost::spirit::qi::grammar<Iterator, ply::header(), Skipper>
{
	header_grammar() :
		header_grammar::base_type(start)
	{
		namespace qi = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;

		start %= qi::eps > magic_ > format_p > *element_ > end_header_;
		magic_ %= "ply" > qi::eol;
		format_p %= "format" > format_ > qi::double_ > qi::eol;
		property_ %= "property" > sol_ > *(ascii::char_ - qi::eol) > qi::eol;
		element_ %= "element" > *(ascii::char_ - qi::int_) > qi::int_ > qi::eol > *property_;
		end_header_ %= "end_header" > qi::eol;

		list_ %= qi::lit("list") > type_ > type_;
		sol_ %= list_ | type_;

		type_.add
			("int8",    ply::int8   )("char",    ply::int8   )
			("int16",   ply::int16  )("short",   ply::int16  )
			("int32",   ply::int32  )("int",     ply::int32  )
			("uint8",   ply::uint8  )("uchar",   ply::uint8  )
			("uint16",  ply::uint16 )("ushort",  ply::uint16 )
			("uint32",  ply::uint32 )("uint",    ply::uint32 )
			("float32", ply::float32)("float",   ply::float32)
			("float64", ply::float64)("double",  ply::float64)
		;

		format_.add
			("ascii",                ply::ascii)
			("binary_little_endian", ply::binary_little_endian)
			("binary_big_endian",    ply::binary_big_endian)
		;
	}

	boost::spirit::qi::rule<Iterator, ply::header(), Skipper> start;
	boost::spirit::qi::rule<Iterator, Skipper> magic_;
	boost::spirit::qi::rule<Iterator, ply::format_version(), Skipper> format_p;
	boost::spirit::qi::rule<Iterator, ply::element(), Skipper> element_;
	boost::spirit::qi::rule<Iterator, ply::property(), Skipper> property_;
	boost::spirit::qi::rule<Iterator, Skipper> end_header_;

	boost::spirit::qi::rule<Iterator, ply::single_or_list_type(), Skipper> sol_;
	boost::spirit::qi::rule<Iterator, ply::list_type(), Skipper> list_;

	boost::spirit::qi::symbols<char, ply::data_type> type_;
	boost::spirit::qi::symbols<char, ply::format_type> format_;
};

} // namespace ply

#endif /* PLY_SPIRIT_HPP */
