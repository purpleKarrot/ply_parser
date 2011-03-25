/*
 * property_parsers.hpp
 *
 *  Created on: 16.12.2010
 *      Author: daniel
 */

#ifndef PLY_PROPERTY_PARSERS_HPP
#define PLY_PROPERTY_PARSERS_HPP

#include <ply/types.hpp>
#include <boost/type_traits/is_arithmetic.hpp>
#include <boost/type_traits/remove_reference.hpp>

namespace ply
{
namespace qi = boost::spirit::qi;

namespace traits
{

template<typename Iterator, typename Skipper, typename T>
struct rule
{
	typedef qi::rule<Iterator, void(T&), Skipper> type;
};

template<typename T>
struct is_scalar: boost::is_arithmetic<T>
{
};

template<typename T>
struct is_scalar<T&>: boost::is_arithmetic<T>
{
};

} // namespace traits

template<typename Rule>
class omit_visitor: public boost::static_visitor<void>
{
public:
	omit_visitor(Rule& rule, ply::format format) :
		rule(rule), format(format)
	{
	}

	void operator()(ply::scalar property) const
	{
		switch (property)
		{
		case ply::uint8:
			rule %= qi::uint_parser<unsigned char>();
			break;
		case ply::uint16:
			rule %= qi::ushort_;
			break;
		case ply::uint32:
			rule %= qi::uint_;
			break;
		case ply::uint64:
			rule %= qi::ulong_long;
			break;
		case ply::int8:
			rule %= qi::int_parser<char>();
			break;
		case ply::int16:
			rule %= qi::short_;
			break;
		case ply::int32:
			rule %= qi::int_;
			break;
		case ply::int64:
			rule %= qi::long_long;
			break;
		case ply::float32:
			rule %= qi::float_;
			break;
		case ply::float64:
			rule %= qi::double_;
			break;
		}
	}

	void operator()(ply::list const& property) const
	{
		// TODO: actually do something depending on property here
		assert(property.count == ply::uint8);
		assert(property.data == ply::int32);
		rule = qi::int_[qi::_a = qi::_1] > qi::repeat(qi::_a)[qi::int_];
	}

private:
	Rule& rule;
	ply::format format;
};

template<typename Rule>
void assign_omit_parser(Rule& rule, ply::format format, ply::property const& property)
{
	typedef omit_visitor<Rule> visitor;
	boost::apply_visitor(visitor(rule, format), property.type);
}

template<typename Rule>
class visitor: public boost::static_visitor<Rule>
{
public:
	visitor(ply::format format) :
		format(format)
	{
	}

	Rule operator()(ply::scalar property) const
	{
		switch (property)
		{
		case ply::uint8:
			return qi::uint_parser<unsigned char>()[qi::_r1 = qi::_1];
		case ply::uint16:
			return qi::ushort_[qi::_r1 = qi::_1];
		case ply::uint32:
			return qi::uint_[qi::_r1 = qi::_1];
		case ply::uint64:
			return qi::ulong_long[qi::_r1 = qi::_1];
		case ply::int8:
			return qi::int_parser<char>()[qi::_r1 = qi::_1];
		case ply::int16:
			return qi::short_[qi::_r1 = qi::_1];
		case ply::int32:
			return qi::int_[qi::_r1 = qi::_1];
		case ply::int64:
			return qi::long_long[qi::_r1 = qi::_1];
		case ply::float32:
			return qi::float_[qi::_r1 = qi::_1];
		case ply::float64:
			return qi::double_[qi::_r1 = qi::_1];
		}
	}

	Rule operator()(ply::list const& property) const
	{
		assert(!"list property not expected!");
		return Rule();
	}

private:
	ply::format format;
};

template<typename Rule>
class visitor2: public boost::static_visitor<Rule>
{
public:
	visitor2(ply::format format) :
		format(format)
	{
	}

	Rule operator()(ply::scalar property) const
	{
		assert(!"scalar property not expected!");
		return Rule();
	}

	Rule operator()(ply::list const& property) const
	{
		// TODO: actually do something depending on property here
		assert(property.count == ply::uint8);
		assert(property.data == ply::int32);
		return "4" > qi::int_ > qi::int_ > qi::int_;
	}

private:
	ply::format format;
};

template<typename Iterator, typename Skipper>
struct parser_factory
{
	template<typename T>
	struct rule
	{
		typedef qi::rule<Iterator, void(T&), Skipper> type;
	};

	template<typename T>
	struct rules: boost::mpl::transform<typename boost::fusion::result_of::as_vector<T>::type, rule<boost::mpl::_1> >
	{
	};

	template<typename T>
	struct scalar_visitor
	{
		typedef ply::visitor<typename rule<T>::type> type;
	};

	template<typename T>
	struct list_visitor
	{
		typedef ply::visitor2<typename rule<T>::type> type;
	};

	template<typename T>
	struct visitor: boost::mpl::if_<traits::is_scalar<T>, scalar_visitor<T> , list_visitor<T> >::type
	{
	};
};

} // namespace ply

#endif /* PLY_PROPERTY_PARSERS_HPP */
