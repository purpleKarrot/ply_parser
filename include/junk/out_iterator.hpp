/*
 * iterator.hpp
 *
 *  Created on: 02.08.2010
 *      Author: daniel
 */

#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <iterator>

template<typename T, typename Base>
class output_range_iterator: //
public std::iterator<std::output_iterator_tag, void, void, void, void>
{
public:
	output_range_iterator(const Base& base, std::size_t begin, std::size_t end) :
		base(base), begin(begin), end(end), current(0)
	{
	}

	/// Copy constructor.
	output_range_iterator(const output_range_iterator& rhs) :
		base(rhs.base), begin(rhs.begin), end(rhs.end), current(rhs.current)
	{
	}

	output_range_iterator& operator=(T const& value)
	{
		if (current >= begin && current < end)
			*base = value;

//		else
//		{
//			std::cerr << "not assigning " << value << ", " << begin << " < "
//					<< current << " < " << end << std::endl;
//		}

		return *this;
	}

	output_range_iterator& operator*()
	{
		return *this;
	}

	output_range_iterator& operator++()
	{
		++current;

		if (current > begin && current <= end)
			++base;

		return *this;
	}

private:
	output_range_iterator& operator++(int);

private:
	Base base;
	std::size_t begin, end;
	std::size_t current;
};

#endif /* ITERATOR_HPP */
