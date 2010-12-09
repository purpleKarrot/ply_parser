/*
 * iterator.hpp
 *
 *  Created on: 02.08.2010
 *      Author: daniel
 */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <boost/iterator/iterator_facade.hpp>
#include <boost/shared_ptr.hpp>

template<typename Element, typename Parser>
class iterator: public boost::iterator_facade<iterator<Element, Parser> ,
		Element, boost::single_pass_traversal_tag>
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

	~iterator()
	{
	}

private:
	friend class boost::iterator_core_access;

	void increment()
	{
		if (parser && !parser->parse(value))
			parser.reset();
	}

	bool equal(iterator const& other) const
	{
		return (!parser && !other.parser) || (parser && other.parser
				&& parser->distance_to_end == other.parser->distance_to_end);
	}

	Element& dereference() const
	{
		return value;
	}

private:
	boost::shared_ptr<Parser> parser;
	mutable Element value;
};

#endif /* ITERATOR_HPP */
