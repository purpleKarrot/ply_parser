#include <boost/test/unit_test.hpp>

#include <boost/fusion/adapted/struct/define_struct.hpp>

#include <ply/loader.hpp>

struct vertex_
{
	float x, y, z;
	float intensity;
	float confidence;
};

BOOST_FUSION_ADAPT_STRUCT(vertex_,
		(float, x)
		(float, y)
		(float, z)
		(float, intensity)
		(float, confidence)
)

BOOST_AUTO_TEST_CASE(complete)
{
	ply::loader<junk::error_loader> loader("bunny.ply");

	std::vector<vertex_> vertices;
	loader.parse_element(0, std::back_inserter(vertices));

	BOOST_CHECK_EQUAL(vertices.size(), loader.elements()[0].count);

	for (int i = 0; i < 10; ++i)
	{
		BOOST_MESSAGE(i << ": " << vertices[i].intensity);
	}
}
