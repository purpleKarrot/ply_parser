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

struct vertex
{
	float x, y, z;
};

BOOST_FUSION_ADAPT_STRUCT(vertex, (float, x)(float, y)(float, z))

//template<int I, int End, typename F, bool Enabled>
//struct loop
//{
//	static void call()
//	{
//	}
//};
//
//template<int I, int End, typename F>
//struct loop<I, End, F, true>
//{
//	static void call()
//	{
//		F::call<I>();
//		loop<I + 1, End, F, I != End>::call();
//	}
//};
//
//template<typename Seq>
//struct foo
//{
//	template<int I>
//	static void call()
//	{
//		using namespace boost::fusion::extension;
//		BOOST_MESSAGE((struct_member_name<Seq, I>::call()));
//	}
//};

// TODO: rewrite this using a loop

template<typename Seq, typename Val>
void named_set(Seq& seq, const std::string& name, Val val)
{
	using namespace boost::fusion::extension;

	BOOST_CHECK_EQUAL(boost::mpl::size<Seq>::value, 3);

	if (name == struct_member_name<Seq, 0>::call())
	{
		boost::fusion::at_c<0>(seq) = val;
	}

	if (name == struct_member_name<Seq, 1>::call())
	{
		boost::fusion::at_c<1>(seq) = val;
	}

	if (name == struct_member_name<Seq, 2>::call())
	{
		boost::fusion::at_c<2>(seq) = val;
	}
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

//	loop<0, boost::mpl::size<vertex>::value, foo<vertex> , true>::call();
}
