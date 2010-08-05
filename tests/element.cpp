#include <ply/element.hpp>

struct vertex
{
	float x;
	float y;
	float z;
	float confidence;
	float intensity;
};

#include <boost/fusion/adapted/struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(vertex,
		(float, x)
		(float, y)
		(float, z)
		(float, confidence)
		(float, intensity)
)

#include <iterator.hpp>
#include <element_parser.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <fstream>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

template<typename Seq, int N>
typename boost::fusion::extension::struct_member_name<Seq, N>::type member_name()
{
	return boost::fusion::extension::struct_member_name<Seq, N>::call();
}

BOOST_AUTO_TEST_CASE(element)
{
	std::ifstream file("parser.txt");

	// iterate over stream input
	typedef std::istreambuf_iterator<char> base_iterator_type;
	base_iterator_type in_begin(file);

	// convert input iterator to forward iterator, usable by spirit parser
	typedef boost::spirit::multi_pass<base_iterator_type> iterator_type;
	iterator_type fwd_begin = boost::spirit::make_default_multi_pass(in_begin);
	iterator_type fwd_end;

	typedef BOOST_TYPEOF(ascii::blank) skipper_type;
	skipper_type skipper = ascii::blank;

	typedef ply::element<vertex>::rules<iterator_type, skipper_type>::type rules_type;
	rules_type rules;

	boost::fusion::at_c<0>(rules) = qi::double_;

	boost::fusion::at_c<0>(rules).name(member_name<vertex, 0>());

	BOOST_MESSAGE((member_name<vertex, 4>()));
}
