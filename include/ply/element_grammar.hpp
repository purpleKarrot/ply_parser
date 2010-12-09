#ifndef PLY_ELEMENT_GRAMMAR_HPP
#define PLY_ELEMENT_GRAMMAR_HPP

#include <ply/types.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/scoped_array.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

namespace ply
{
namespace ph = boost::phoenix;
namespace qi = boost::spirit::qi;

template<typename Rule>
//Rule ascii_omit(ply::scalar const& scalar)
Rule ascii_omit(ply::property_type const& property_type)
{
	switch (boost::get<ply::scalar>(property_type))
	{
	case ply::uint8:
		return qi::omit[qi::uint_parser<unsigned char>()];
	case ply::uint16:
		return qi::omit[qi::ushort_];
	case ply::uint32:
		return qi::omit[qi::uint_];
	case ply::uint64:
		return qi::omit[qi::ulong_long];
	case ply::int8:
		return qi::omit[qi::int_parser<char>()];
	case ply::int16:
		return qi::omit[qi::short_];
	case ply::int32:
		return qi::omit[qi::int_];
	case ply::int64:
		return qi::omit[qi::long_long];
	case ply::float32:
		return qi::omit[qi::float_];
	case ply::float64:
		return qi::omit[qi::double_];
	}
}

template<typename Rule, typename Semantic>
//Rule ascii_scalar(ply::scalar const& scalar, Semantic semantic)
Rule ascii_scalar(ply::property_type const& property_type, Semantic semantic)
{
	switch (boost::get<ply::scalar>(property_type))
	{
	case ply::uint8:
		return qi::uint_parser<unsigned char>()[semantic];
	case ply::uint16:
		return qi::ushort_[semantic];
	case ply::uint32:
		return qi::uint_[semantic];
	case ply::uint64:
		return qi::ulong_long[semantic];
	case ply::int8:
		return qi::int_parser<char>()[semantic];
	case ply::int16:
		return qi::short_[semantic];
	case ply::int32:
		return qi::int_[semantic];
	case ply::int64:
		return qi::long_long[semantic];
	case ply::float32:
		return qi::float_[semantic];
	case ply::float64:
		return qi::double_[semantic];
	}
}

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
