/*
 * mpl_ply.hpp
 *
 *  Created on: 02.08.2010
 *      Author: daniel
 */

#include <ply/property.hpp>
#include <ply/element.hpp>
#include <ply/model.hpp>

#include <boost/test/unit_test.hpp>

struct vertex: boost::fusion::vector<float, float, float>
{
};

struct vertices: ply::element<vertex>
{
	static const char* const name()
	{
		return "vertices";
	}
};

struct face: ply::list<ply::uint8, ply::uint32, 3>
{
};

struct faces: ply::element<face>
{
	static const char* const name()
	{
		return "faces";
	}
};

struct model: ply::model<boost::fusion::vector<vertices, faces> >
{
};

BOOST_AUTO_TEST_CASE(mpl_ply)
{
//	model m("bunny.ply.gz");
//
//	vertices v = m.element<vertices> ();
//	faces v = m.element<faces> ();
}
