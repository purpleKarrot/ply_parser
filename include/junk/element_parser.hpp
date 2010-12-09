/*
 * element_parser.hpp
 *
 *  Created on: Aug 3, 2010
 *      Author: danielp
 */

#ifndef ELEMENT_PARSER_HPP
#define ELEMENT_PARSER_HPP

#include <boost/spirit/home/qi/nonterminal/rule.hpp>
#include <boost/spirit/home/qi/parse.hpp>

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
				distance_to_end + 1)
	{
		//lock
	}

	~element_parser()
	{
		//unlock
	}

	bool parse(Element& element)
	{
		assert(distance_to_end);
		return --distance_to_end && boost::spirit::qi::parse(begin, end,
				grammar, element);
	}

private:
	Iterator begin, end;
	grammar_type grammar;

	//	lock_type lock;

public:
	std::size_t distance_to_end;
};

template<typename Element, typename Iterator, typename Skipper>
class element_phrase_parser
{
	typedef boost::spirit::qi::rule<Iterator, Element(), Skipper> grammar_type;

public:
	element_phrase_parser(Iterator begin, Iterator end, grammar_type grammar,
			Skipper skipper, std::size_t distance_to_end) :
		begin(begin), end(end), grammar(grammar), skipper(skipper),
				distance_to_end(distance_to_end + 1)
	{
		//lock
	}

	~element_phrase_parser()
	{
		//unlock
	}

	bool parse(Element& element)
	{
		assert(distance_to_end);
		return --distance_to_end && boost::spirit::qi::phrase_parse(begin, end,
				grammar, skipper, element);
	}

private:
	Iterator begin, end;
	grammar_type grammar;
	Skipper skipper;

	//	lock_type lock;

public:
	std::size_t distance_to_end;
};

#endif /* ELEMENT_PARSER_HPP */
