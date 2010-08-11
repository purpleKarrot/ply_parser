/*
 * property.hpp
 *
 *  Created on: Aug 10, 2010
 *      Author: danielp
 */

#ifndef PLY_PROPERTY_HPP
#define PLY_PROPERTY_HPP

#include <boost/spirit/home/qi/nonterminal/rule.hpp>

/*
 * ply
 * format ascii 1.0
 * comment zipper output
 * element vertex 35947
 * property float x
 * property float y
 * property float z
 * property float confidence
 * property float intensity
 * element face 69451
 * property list uchar int vertex_indices
 * end_header
 *
 *
 *
 * parsing the line
 *
 *   property float y
 *
 * appends a parser:
 *
 *   rule = rule.copy() > appendee;
 *
 * typedef rule<void(Element&)> rule_type;
 *
 * appendee has name "y" and parses float
 *
 * foreach e in Element (sequence)
 *  if name matches "y"
 *   use setter as semantic action [phoenix::at_c<N>(_val) = _1];
 *
 * omit synthesized attribute in any case
 *
 */

namespace ply
{
namespace qi = boost::spirit::qi;

template<typename Element>
struct property_grammar
{
	qi::rule<const char*, void(Element&)> rule;

	qi::rule<const char*> start;
	qi::rule<const char*> property;
	qi::rule<const char*> type_;
	qi::rule<const char*> name_;

	property_grammar()
	{
		property = "property" > type_ > name_;

		qi::float_(name_);

	}

};

} // namespace ply

#endif /* PLY_PROPERTY_HPP */
