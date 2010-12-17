/*
 * property_parsers.hpp
 *
 *  Created on: 16.12.2010
 *      Author: daniel
 */

#ifndef PLY_PROPERTY_PARSERS_HPP
#define PLY_PROPERTY_PARSERS_HPP

#include <ply/types.hpp>

namespace ply
{
namespace qi = boost::spirit::qi;

template<typename Iterator, typename Skipper, typename T>
struct scalar_parser
{
};

template<typename Iterator, typename Skipper>
struct scalar_parser<Iterator, Skipper, char>
{
	typedef qi::rule<Iterator, char(), Skipper> rule_type;

	static rule_type create()
	{
		return qi::int_parser<char>();
	}
};

template<typename Iterator, typename Skipper, typename T>
struct omit_parser
{
	typedef qi::rule<Iterator, void(), Skipper> rule_type;

	static rule_type create()
	{
		return qi::omit[scalar_parser<Iterator, Skipper, T>::create()];
	}
};

template<typename Iterator, typename Skipper, typename Element>
struct factory
{
	typedef qi::rule<Iterator, void(Element&), Skipper> rule_type;

	struct omit_visitor
	{
	};

	template<typename I>
	struct property_visitor
	{
	};
};

//template<typename Iterator, typename Skipper, ply::format Format, ply::scalar Skalar>
//struct parser_factory_base
//{
//};
//
//template<typename Iterator, typename Skipper>
//struct parser_factory_base<Iterator, Skipper, ply::ascii, ply::int8>
//{
//	typedef boost::int8_t synth_type;
//	typedef qi::rule<Iterator, synth_type(), Skipper> rule_type;
//
//	static rule_type create()
//	{
//		return qi::int_parser<char>();
//	}
//};
//
//template<typename Iterator, typename Skipper, typename T>
//struct parser_factory
//{
//	typedef qi::rule<Iterator, T(), Skipper> rule;
//	typedef qi::rule<Iterator, void(), Skipper> omit_rule;
//
//};
//
//template<>
//struct parser_factory<int>
//{
//
//};

template<typename Iterator, typename Signature, typename Skipper>
boost::spirit::qi::rule<Iterator, Signature, Skipper> //
scalar_ascii_parser(ply::scalar property)
{
	namespace qi = boost::spirit::qi;

	switch (property)
	{
	case ply::uint8:
		return qi::uint_parser<unsigned char>();
	case ply::uint16:
		return qi::ushort_;
	case ply::uint32:
		return qi::uint_;
	case ply::uint64:
		return qi::ulong_long;
	case ply::int8:
		return qi::int_parser<char>();
	case ply::int16:
		return qi::short_;
	case ply::int32:
		return qi::int_;
	case ply::int64:
		return qi::long_long;
	case ply::float32:
		return qi::float_;
	case ply::float64:
		return qi::double_;
	}
}

template<typename Rule>
class ascii_omit_visitor: public boost::static_visitor<Rule>
{
public:
	Rule operator()(ply::scalar property) const
	{
		namespace qi = boost::spirit::qi;

		switch (property)
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

	Rule operator()(ply::list const& property) const
	{
		assert(!"not yet implemented!");
		// property.count;
		// property.data;
		return Rule();
	}

private:
};

template<typename Rule>
class omit_visitor: public boost::static_visitor<Rule>
{
public:
	omit_visitor(ply::format format) :
		format(format)
	{
	}

	Rule operator()(ply::scalar property) const
	{
		namespace qi = boost::spirit::qi;

		switch (property)
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

	Rule operator()(ply::list const& property) const
	{
		assert(!"not yet implemented!");
		// property.count;
		// property.data;
		return Rule();
	}

private:
	ply::format format;
};

template<typename Rule>
class binary_omit_visitor: public boost::static_visitor<Rule>
{
public:
	Rule operator()(ply::scalar property) const
	{
		namespace qi = boost::spirit::qi;

		switch (property)
		{
		case ply::int8:
		case ply::uint8:
			return qi::omit[qi::byte_];
		case ply::int16:
		case ply::uint16:
			return qi::omit[qi::word];
		case ply::int32:
		case ply::uint32:
		case ply::float32:
			return qi::omit[qi::dword];
		case ply::int64:
		case ply::uint64:
		case ply::float64:
			return qi::omit[qi::qword];
		}
	}

	Rule operator()(ply::list const& property) const
	{
		assert(!"not yet implemented!");
		// property.count;
		// property.data;
		return Rule();
	}

private:
};

template<typename Rule, typename Semantic>
//Rule ascii_scalar(ply::scalar const& scalar, Semantic semantic)
Rule ascii_scalar(ply::property_type const& property_type, Semantic semantic)
{
	namespace qi = boost::spirit::qi;

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

template<typename Iterator, typename Skipper>
struct parser_factory
{
	template<typename T>
	struct rule
	{
		typedef qi::rule<Iterator, T(), Skipper> type;
	};

	template<typename T>
	class visitor: public boost::static_visitor<typename rule<T>::type>
	{
		typedef typename rule<T>::type rule_type;

	public:
		visitor(ply::format format) :
			format(format)
		{
		}

		rule_type operator()(ply::scalar property) const
		{
			assert(!"not yet implemented!");
			return rule_type();
		}

		rule_type operator()(ply::list const& property) const
		{
			assert(!"not yet implemented!");
			return rule_type();
		}

	private:
		ply::format format;
	};
};

} // namespace ply

#endif /* PLY_PROPERTY_PARSERS_HPP */
