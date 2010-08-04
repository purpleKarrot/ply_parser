#include <boost/spirit/home/qi/string/symbols.hpp>
#include <boost/spirit/home/qi/numeric.hpp>

namespace ply
{
namespace qi = boost::spirit::qi;

template<typename Rule>
struct size_symbols: qi::symbols<char, Rule>
{
	size_symbols()
	{
		this->add
			("uint8",  qi::uint_parser<unsigned char>()  )
			("uchar",  qi::uint_parser<unsigned char>()  )
			("uint16", qi::ushort_)("ushort", qi::ushort_)
			("uint32", qi::uint_  )("uint",   qi::uint_  )
		;
	}
};

template<typename Rule>
struct scalar_symbols: size_symbols<Rule>
{
	scalar_symbols()
	{
		this->add
			("int8",    qi::int_parser<char>()            )
			("char",    qi::int_parser<char>()            )
			("int16",   qi::short_ )("short",  qi::short_ )
			("int32",   qi::int_   )("int",    qi::int_   )
			("float32", qi::float_ )("float",  qi::float_ )
			("float64", qi::double_)("double", qi::double_)
		;
	}
};

} // namespace ply
