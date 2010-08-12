/*
 * named_setter.cpp
 *
 *  Created on: Aug 11, 2010
 *      Author: danielp
 */

#include <boost/test/unit_test.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/adapted/struct.hpp>
#include <boost/fusion/mpl/size.hpp>

#include <boost/mpl/range_c.hpp>

struct vertex
{
	float x, y, z;
};

BOOST_FUSION_ADAPT_STRUCT(vertex, (float, x)(float, y)(float, z))

namespace detail
{

template<typename Seq, typename Val>
class named_setter
{
public:
	named_setter(Seq& seq, const std::string& name, Val val) :
		seq(seq), name(name), val(val)
	{
	}

	template<typename I>
	void operator()(I i)
	{
		using namespace boost::fusion::extension;

		if (name == struct_member_name<Seq, I::value>::call())
		{
			boost::fusion::at<I>(seq) = val;
		}
	}

private:
	Seq& seq;
	std::string name;
	int val;
};

} // namespace detail

template<typename Seq, typename Val>
void named_set(Seq& seq, const std::string& name, Val val)
{
	typedef boost::mpl::range_c<int, 0, boost::mpl::size<Seq>::value> indices;

	boost::mpl::for_each<indices>(detail::named_setter<Seq, Val>(seq, name, val));
}

BOOST_AUTO_TEST_CASE(named_setter)
{
	vertex v;
	named_set(v, "x", 1);
	named_set(v, "y", 2);
	named_set(v, "z", 3);

	BOOST_CHECK_EQUAL(v.x, 1);
	BOOST_CHECK_EQUAL(v.y, 2);
	BOOST_CHECK_EQUAL(v.z, 3);
}
