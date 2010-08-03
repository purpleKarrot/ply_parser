/*
 * iterator.hpp
 *
 *  Created on: 02.08.2010
 *      Author: daniel
 */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <boost/iterator/iterator_facade.hpp>
#include <boost/spirit/home/qi/nonterminal/rule.hpp>

// parses exactly one element (line)
// only one parser may exist at a time (lock)

template<typename Element, typename Iterator>
class element_parser
{
	typedef boost::spirit::qi::rule<Iterator, Element()> grammar_type;

public:
	element_parser(Iterator begin, Iterator end, grammar_type grammar,
		std::size_t distance_to_end) :
		begin(begin), end(end), grammar(grammar), distance_to_end(
			distance_to_end)
	{
		//lock
	}

	~element_parser()
	{
		//unlock
	}

	bool parse(Element& element)
	{
		qi::phrase_parse(begin, end, grammar, element);
		distance_to_end--;
		return end_reached;
	}

private:
	Iterator begin, end;

	std::size_t distance_to_end;

	grammar_type grammar;

	lock_type lock;
};

template<typename Parser>
class iterator: public boost::iterator_facade<iterator,
	typename Parser::element_type, boost::single_pass_traversal_tag>
{
public:
	iterator()
	{
	}

	iterator(boost::shared_ptr<Parser> const& parser) :
		parser(parser)
	{
		increment();
	}

	iterator(const iterator& other) :
		parser(other.parser), value(other.value)
	{
	}

	~istream_iterator()
	{
	}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		if (!parser.parse(value))
			parser.reset();
	}

	bool equal(iterator const& other) const
	{
		return parser && other.parser //
			&& parser->distance_to_end == other.parser->distance_to_end;
	}

	const value_type& dereference() const
	{
		return value;
	}

private:
	boost::shared_ptr<Parser> parser;
	value_type value;
};

#endif /* ITERATOR_HPP */
