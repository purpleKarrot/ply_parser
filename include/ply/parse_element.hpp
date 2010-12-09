#ifndef PLY_PARSE_ELEMENT_HPP
#define PLY_PARSE_ELEMENT_HPP

#include <ply/element_grammar.hpp>
#include <junk/element_parser.hpp>
#include <junk/iterator.hpp>

namespace ply
{

template<typename OutputIterator>
struct value_type
{
};

template<typename Container>
struct value_type<std::back_insert_iterator<Container> >
{
	typedef typename Container::value_type type;
};

template<typename Iterator, typename OutputIterator>
void parse_element(Iterator& begin, Iterator end, const ply::element& element, OutputIterator output)
{
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;

	typedef typename value_type<OutputIterator>::type value_t;
	ply::element_grammar<Iterator, ascii::blank_type, value_t> grammar(element);

	typedef element_phrase_parser<value_t, Iterator, ascii::blank_type> parser_t;
	boost::shared_ptr<parser_t> parser(new parser_t(begin, end, grammar, ascii::blank, element.count));

	typedef ::iterator<value_t, parser_t> parse_iterator;
	std::copy(parse_iterator(parser), parse_iterator(), output);
}

} // namespace ply

#endif /* PLY_PARSE_ELEMENT_HPP */
