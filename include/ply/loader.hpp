#ifndef PLY_LOADER_HPP
#define PLY_LOADER_HPP

#include <ply/header_grammar.hpp>
#include <ply/element_grammar.hpp>
#include <junk/element_parser.hpp>
#include <junk/iterator.hpp>
#include <junk/loader.hpp>

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

template<typename Iterator>
struct loader_base
{
	void do_parse_header(Iterator& begin, Iterator end, ply::header& header)
	{
		namespace qi = boost::spirit::qi;
		namespace ascii = boost::spirit::ascii;

		static BOOST_AUTO(comment, qi::lit("comment") >> *(ascii::char_ - qi::eol) >> qi::eol);
		static BOOST_AUTO(skip, ascii::blank | comment);

		static ply::header_grammar<Iterator, BOOST_TYPEOF(skip)> grammar;

		boost::spirit::qi::phrase_parse(begin, end, grammar, skip, header);
	}

	template<typename OutputIterator>
	void do_parse_element(Iterator& begin, Iterator end, const ply::element& element, OutputIterator output)
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
};

template<typename P>
class loader: loader_base<typename P::iterator>
{
public:
	loader(const char* filename) :
		loader_impl(filename)
	{
		try
		{
			do_parse_header(loader_impl.begin(), loader_impl.end(), header);
		} catch (const typename P::expectation_failure& failure)
		{
			loader_impl.error(failure);
		}
	}

	ply::format format() const
	{
		return header.format;
	}

	double version() const
	{
		return header.version;
	}

	std::vector<ply::element> const& elements() const
	{
		return header.elements;
	}

	template<typename OutputIterator>
	void parse_element(int element, OutputIterator output)
	{
		try
		{
			do_parse_element(loader_impl.begin(), loader_impl.end(), header.elements[element], output);
		} catch (const typename P::expectation_failure& failure)
		{
			loader_impl.error(failure);
		}
	}

private:
	P loader_impl;
	ply::header header;
};

} // namespace ply

#endif /* PLY_LOADER_HPP */
