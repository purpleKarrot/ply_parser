#include "stream/stream.hpp"
#include "stream/stream_adapted.hpp"

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>

namespace stream
{

template<typename Iterator, typename Skipper>
struct element_grammar: boost::spirit::qi::grammar<Iterator, stream::element(), boost::spirit::qi::locals<std::string>, Skipper>
{
	element_grammar() :
		element_grammar::base_type(start)
	{
		namespace qi = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;
		using namespace qi::labels;

		start %= qi::lit("element") > name_[_a = _1] > count_(_a) > -offset_(_a);

		name_ %= +(ascii::char_ - ascii::space);

		count_ %= qi::string(_r1) > qi::lit("count") > qi::int_;
		offset_ %= qi::string(_r1) > qi::lit("offset") > qi::int_;

	}

	boost::spirit::qi::rule<Iterator, stream::element(), boost::spirit::qi::locals<std::string>, Skipper> start;

	boost::spirit::qi::rule<Iterator, std::string(), Skipper> name_;

	boost::spirit::qi::rule<Iterator, int(std::string), Skipper> count_;
	boost::spirit::qi::rule<Iterator, int(std::string), Skipper> offset_;

	boost::spirit::qi::symbols<char, stream::type_t> type_;
};

template<typename Iterator, typename Skipper>
struct header_grammar: boost::spirit::qi::grammar<Iterator, stream::header(), Skipper>
{
	header_grammar() :
		header_grammar::base_type(start)
	{
		namespace qi = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;

		start %= qi::eps > min_ > max_ > -endian_ > -transform_ > *element_ > qi::eoi;

		min_ %= qi::lit("min") > vec3_;
		max_ %= qi::lit("max") > vec3_;

		vec3_ %= qi::float_ > qi::float_ > qi::float_;

		endian_ %= qi::lit("endian") > endian_type_;

		endian_type_.add
			("little", stream::little)
			("big",    stream::big)
		;

		transform_ %= qi::lit("transform") > mat4x4_;

		mat4x4_ %= qi::float_ >> qi::float_ >> qi::float_ >> qi::float_
				>> qi::float_ >> qi::float_ >> qi::float_ >> qi::float_
				>> qi::float_ >> qi::float_ >> qi::float_ >> qi::float_
				>> qi::float_ >> qi::float_ >> qi::float_ >> qi::float_
				;
	}

	boost::spirit::qi::rule<Iterator, stream::header(), Skipper> start;

	boost::spirit::qi::rule<Iterator, stream::vec3(), Skipper> vec3_;
	boost::spirit::qi::rule<Iterator, stream::mat4x4(), Skipper> mat4x4_;

	boost::spirit::qi::rule<Iterator, stream::vec3(), Skipper> min_;
	boost::spirit::qi::rule<Iterator, stream::vec3(), Skipper> max_;

	boost::spirit::qi::rule<Iterator, stream::endian_type(), Skipper> endian_;
	boost::spirit::qi::symbols<char, stream::endian_type> endian_type_;

	boost::spirit::qi::rule<Iterator, stream::mat4x4(), Skipper> transform_;

	element_grammar<Iterator, Skipper> element_;
};

} // namespace stream
