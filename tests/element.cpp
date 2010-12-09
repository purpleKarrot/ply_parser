//

#include <boost/spirit/include/qi.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <boost/array.hpp>
#include <vector>

#include <ply/element_grammar.hpp>

BOOST_FUSION_DEFINE_STRUCT(, vertex,
		(int, x)
		(int, y)
		(int, z)
)

BOOST_FUSION_DEFINE_STRUCT(, face,
		(std::vector<int>, vertex_indices)
)

BOOST_AUTO_TEST_CASE(element)
{
	namespace qi = boost::spirit::qi;
	namespace ascii = boost::spirit::ascii;
	using namespace qi::labels;

	typedef std::string::iterator iterator;

	ply::element e;
	e.name = "vertex";
	e.properties.push_back(ply::property(ply::float32, "x"));
	e.properties.push_back(ply::property(ply::float32, "y"));
	e.properties.push_back(ply::property(ply::float32, "z"));
	e.properties.push_back(ply::property(ply::float32, "confidence"));
	e.properties.push_back(ply::property(ply::float32, "intensity"));

	ply::element_grammar<iterator, ascii::blank_type, vertex> g(e);

	std::string string = "3 4.5 5.5 6.5 8.15\n3 4.5 5.5 6.5 8.15\n";
	iterator f = string.begin();
	iterator l = string.end();

	vertex v;

	boost::spirit::qi::phrase_parse(f, l, g, ascii::blank, v);

	std::cout << v.x << std::endl;
	std::cout << v.y << std::endl;
	std::cout << v.z << std::endl;

	boost::spirit::qi::phrase_parse(f, l, g, ascii::blank, v);

	std::cout << v.x << std::endl;
	std::cout << v.y << std::endl;
	std::cout << v.z << std::endl;
}
