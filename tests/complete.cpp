
#include <ply/parse_header.hpp>
#include <ply/parse_element.hpp>

#include <fstream>
#include <sstream>
#include <boost/test/unit_test.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace classic = boost::spirit::classic;

struct vertex_
{
	//float x, y, z;
	float intensity;
	float confidence;
};

BOOST_FUSION_ADAPT_STRUCT(vertex_,
		(float, intensity)
		(float, confidence)
)

BOOST_AUTO_TEST_CASE(complete)
{
	std::ifstream file("bunny.ply");
	BOOST_REQUIRE(file);

	// iterate over stream input
	typedef std::istreambuf_iterator<char> base_iterator_type;
	base_iterator_type in_begin(file);

	// convert input iterator to forward iterator, usable by spirit parser
	typedef boost::spirit::multi_pass<base_iterator_type> forward_iterator_type;
	forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(
			in_begin);
	forward_iterator_type fwd_end;

	// wrap forward iterator with position iterator, to record the position
	typedef classic::position_iterator2<forward_iterator_type> iterator;
	iterator position_begin(fwd_begin, fwd_end, "bunny.ply");
	iterator position_end;

	// parse
	try
	{
		ply::header header;
		ply::parse_header(position_begin, position_end, header);

		std::vector<vertex_> vertices;
		ply::parse_element(position_begin, position_end, header.elements[0],
				std::back_inserter(vertices));

 		BOOST_CHECK_EQUAL(vertices.size(), header.elements[0].count);

 		for (int i = 0; i < 10; ++i)
		{
 			BOOST_MESSAGE(i << ": " << vertices[i].intensity);
		}
	}
	catch (const qi::expectation_failure<iterator>& e)
	{
		const classic::file_position_base<std::string>& pos =
				e.first.get_position();

		std::stringstream msg;
		msg << "parse error at file " << pos.file << " line " << pos.line
				<< " column " << pos.column << std::endl;
		msg << "'" << e.first.get_currentline() << "'" << std::endl;
		msg << std::setw(pos.column) << " " << "^- here";

		BOOST_FAIL(msg.str());
	}
}
