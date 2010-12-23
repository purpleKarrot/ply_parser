#ifndef PLY_ELEMENT_GRAMMAR_HPP
#define PLY_ELEMENT_GRAMMAR_HPP

#include <ply/property_grammar.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/scoped_array.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/fusion/mpl.hpp>

namespace ply
{
namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

template<typename Iterator, typename Skipper, typename Element>
class element_grammar: public boost::spirit::qi::grammar<Iterator, Element(), Skipper>
{
	typedef parser_factory<Iterator, Skipper> factory;
	typedef property_grammar<Iterator, Skipper, Element> property_parser;

	typedef typename factory::template rules<Element>::type property_rules;

	struct assign_grammar
	{
		assign_grammar(property_rules& rules, property_parser& parser, ply::property const& property) :
			rules(rules), parser(parser), property(property)
		{
		}

		template<typename I>
		void operator()(I)
		{
			using boost::fusion::extension::struct_member_name;
			if (property.name == struct_member_name<Element, I::value>::call())
				parser.init(I(), boost::fusion::at<I>(rules), property.type);
		}

		property_rules& rules;
		property_parser& parser;
		ply::property const& property;
	};

public:
	element_grammar(ply::element const& element) :
		element_grammar::base_type(start, element.name), property_parsers(new property_parser[element.properties.size()])
	{
		typedef boost::mpl::range_c<int, 0, size> indices;

		start = qi::eps;
		for (int i = 0; i < element.properties.size(); ++i)
		{
			property_parsers[i].omit(element.properties[i].type);
			boost::mpl::for_each<indices>(assign_grammar(rules, property_parsers[i], element.properties[i]));
			start = start.copy() > property_parsers[i](qi::labels::_val);
		}

		// TODO: if format ascii
		start = start.copy() > qi::eol;
	}

private:
	//
	boost::spirit::qi::rule<Iterator, Element(), Skipper> start;

	//! the number of properties in this element
	static const int size = boost::mpl::size<Element>::value;

	//! the rules to parse the properties.
	//* The signature is 'void(T&)' and the amount is static */
	property_rules rules;

	//! the parsers for the properties.
	//* The signature is 'void(Element&)' and the amount is dynamic */
	boost::scoped_array<property_parser> property_parsers;
};

} // namespace ply

#endif /* PLY_ELEMENT_GRAMMAR_HPP */
