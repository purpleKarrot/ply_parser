#ifndef PLY_PARSE_HEADER_HPP
#define PLY_PARSE_HEADER_HPP

#include <ply/header_grammar.hpp>

namespace ply
{

template<typename Iterator>
void parse_header(Iterator& begin, Iterator end, ply::header& header)
{
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;

	static BOOST_AUTO(comment, qi::lit("comment") >> *(ascii::char_ - qi::eol) >> qi::eol);
	static BOOST_AUTO(skip, ascii::blank | comment);

	static ply::header_grammar<Iterator, BOOST_TYPEOF(skip)> grammar;

	boost::spirit::qi::phrase_parse(begin, end, grammar, skip, header);
}

} // namespace ply

#endif /* PLY_PARSE_HEADER_HPP */
