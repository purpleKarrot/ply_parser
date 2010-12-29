#include <boost/test/unit_test.hpp>

#include <boost/fusion/adapted/struct/define_struct.hpp>

#include <ply/loader.hpp>

struct vertex_
{
	float x, y, z;
	float intensity;
	float confidence;
};

typedef boost::array<int, 3> triangle;

struct face_
{
	triangle vertex_indices;
};

BOOST_FUSION_ADAPT_STRUCT(vertex_,
//		(float, x)
//		(float, y)
//		(float, z)
		(float, intensity)
		(float, confidence)
)

BOOST_FUSION_ADAPT_STRUCT(face_, (triangle, vertex_indices) )

BOOST_AUTO_TEST_CASE(complete)
{
	ply::loader<junk::error_loader> loader("bunny.ply");

	std::vector<vertex_> vertices;
	loader.parse_element(0, std::back_inserter(vertices));

//	std::vector<face_> faces;
//	loader.parse_element(1, std::back_inserter(faces));

	std::vector<vertex_> faces;
	loader.parse_element(1, std::back_inserter(faces));

	BOOST_CHECK_EQUAL(vertices.size(), loader.elements()[0].count);
	BOOST_CHECK_EQUAL(faces.size(), loader.elements()[1].count);

	for (int i = 0; i < 10; ++i)
	{
		BOOST_MESSAGE(i << ": " << vertices[i].intensity);
	}
}
