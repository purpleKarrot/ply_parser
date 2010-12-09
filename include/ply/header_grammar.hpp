#ifndef PLY_HEADER_GRAMMAR_HPP
#define PLY_HEADER_GRAMMAR_HPP

#include <ply/types.hpp>
#include <boost/spirit/include/qi.hpp>

namespace ply
{

struct size_symbols: boost::spirit::qi::symbols<char, ply::scalar>
{
	size_symbols()
	{
		this->add
			("uint8",   ply::uint8  )("uchar",  ply::uint8  )
			("uint16",  ply::uint16 )("ushort", ply::uint16 )
			("uint32",  ply::uint32 )("uint",   ply::uint32 )
			("uint64",  ply::uint64 )
		;
	}
};

struct scalar_symbols: size_symbols
{
	scalar_symbols()
	{
		this->add
			("int8",    ply::int8   )("char",   ply::int8   )
			("int16",   ply::int16  )("short",  ply::int16  )
			("int32",   ply::int32  )("int",    ply::int32  )
			("int64",   ply::int64  )
			("float32", ply::float32)("float",  ply::float32)
			("float64", ply::float64)("double", ply::float64)
		;
	}
};

struct format_symbols: boost::spirit::qi::symbols<char, ply::format>
{
	format_symbols()
	{
		this->add
			("ascii",                ply::ascii               )
			("binary_little_endian", ply::binary_little_endian)
			("binary_big_endian",    ply::binary_big_endian   )
		;
	}
};

template<typename Iterator, typename Skipper>
struct header_grammar: boost::spirit::qi::grammar<Iterator, ply::header(), Skipper>
{
	header_grammar() :
		header_grammar::base_type(start)
	{
		namespace qi    = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;

		start %= qi::eps
				> "ply" > qi::eol
				> "format" > format_ > qi::double_ > qi::eol
				> *element_
				> "end_header" > qi::eol;

		element_ %= "element" > *(ascii::char_ - qi::int_) > qi::int_ > qi::eol
				> *property_;

		property_ %= "property" > (list_ | scalar_) > *(ascii::char_ - qi::eol) > qi::eol;

		list_ %= "list" > size_ > scalar_;
	}

	boost::spirit::qi::rule<Iterator, ply::header(),   Skipper> start;
	boost::spirit::qi::rule<Iterator, ply::element(),  Skipper> element_;
	boost::spirit::qi::rule<Iterator, ply::property(), Skipper> property_;
	boost::spirit::qi::rule<Iterator, ply::list(),     Skipper> list_;

	size_symbols   size_;
	scalar_symbols scalar_;
	format_symbols format_;
};

} // namespace ply

#endif /* PLY_HEADER_GRAMMAR_HPP */
