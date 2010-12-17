#ifndef PLY_ELEMENT_GRAMMAR_HPP
#define PLY_ELEMENT_GRAMMAR_HPP

#include <ply/property_parsers.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/scoped_array.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace ply
{
namespace qi = boost::spirit::qi;
namespace ph = boost::phoenix;

template<typename Iterator, typename Skipper, typename Element>
class element_grammar: public boost::spirit::qi::grammar<Iterator, Element(), Skipper>
{
	BOOST_STATIC_CONSTANT(int, size = boost::mpl::size<Element>::value);
	typedef qi::rule<Iterator, void(Element&), Skipper> property_grammar;
	typedef boost::scoped_array<property_grammar> property_parsers_t;

	struct assign_grammar
	{
		assign_grammar(property_grammar& parser, ply::property const& property) :
			parser(parser), property(property)
		{
		}

		template<int I>
		const char* name()
		{
			return boost::fusion::extension::struct_member_name<Element, I>::call();
		}

		template<typename I>
		void operator()(I)
		{
			using namespace boost::fusion::extension;
			if (property.name == name<I::value> ())
			{
				using namespace qi::labels;
				parser = ascii_scalar<property_grammar> (
						property.type, ph::at_c<I::value>(_r1) = _1);

				std::cout << I::value << ": " << property.name << " == " << name<I::value> () << std::endl;
			}
		}

		property_grammar& parser;
		ply::property const& property;
	};

public:
	element_grammar(ply::element const& element) :
		element_grammar::base_type(start, element.name), property_parsers(
				new property_grammar[element.properties.size()])
	{
		typedef boost::mpl::range_c<int, 0, size> indices;

		start = qi::eps;
		for (int i = 0; i < element.properties.size(); ++i)
		{
			using namespace qi::labels;
			property_parsers[i] = ascii_omit<property_grammar> (
					element.properties[i].type);

			boost::mpl::for_each<indices>(assign_grammar(property_parsers[i],
					element.properties[i]));

			start = start.copy() > property_parsers[i](_val);
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
