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

	typedef qi::rule<Iterator, void(Element&), qi::locals<std::size_t>, Skipper> property_parser;

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
			typedef typename boost::fusion::result_of::at<Element, I>::type type;
			typedef typename factory::template visitor<type>::type visitor;

			if (property.name == struct_member_name<Element, I::value>::call())
			{
				boost::fusion::at<I>(rules) = boost::apply_visitor(visitor(ply::ascii), property.type);
				parser = boost::fusion::at<I>(rules)(ph::at_c<I::value>(qi::_r1));

				std::cout << "match: " << property.name << std::endl;
			}
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
			assign_omit_parser(property_parsers[i], ply::ascii, element.properties[i]);
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
