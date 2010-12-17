#ifndef PLY_ELEMENT_GRAMMAR_HPP
#define PLY_ELEMENT_GRAMMAR_HPP

#include <ply/property_grammar.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/scoped_array.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>

namespace ply
{
namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

template<typename Iterator, typename Skipper, typename Element>
class element_grammar: public boost::spirit::qi::grammar<Iterator, Element(), Skipper>
{
	BOOST_STATIC_CONSTANT(int, size = boost::mpl::size<Element>::value);
	typedef property_grammar<Iterator, Skipper, Element> property_parser;
	typedef boost::scoped_array<property_parser> property_parsers_t;

	struct assign_grammar
	{
		assign_grammar(property_parser& parser, ply::property const& property) :
			parser(parser), property(property)
		{
		}

		template<typename I>
		void operator()(I)
		{
			using boost::fusion::extension::struct_member_name;
			if (property.name == struct_member_name<Element, I::value>::call())
				parser.init(I(), property.type);
		}

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
			boost::mpl::for_each<indices>(assign_grammar(property_parsers[i], element.properties[i]));
			start = start.copy() > property_parsers[i](qi::labels::_val);
		}

		// TODO: if format ascii
		start = start.copy() > qi::eol;
	}

private:
	property_parsers_t property_parsers;
	boost::spirit::qi::rule<Iterator, Element(), Skipper> start;
};

} // namespace ply

#endif /* PLY_ELEMENT_GRAMMAR_HPP */
