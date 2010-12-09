/*
 * binary.cpp
 *
 *  Created on: 24.08.2010
 *      Author: daniel
 */

#include <boost/test/unit_test.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/home/phoenix/object/reinterpret_cast.hpp>

namespace qi = boost::spirit::qi;

BOOST_AUTO_TEST_CASE(binary)
{
//	qi::byte_;
//	qi::little_word;
//	qi::little_dword;
//
//	qi::big_word;
//	qi::big_dword;

	qi::dword[qi::_val = *phoenix::reinterpret_cast_<float*>(&_1)];
	qi::qword[qi::_val = *phoenix::reinterpret_cast_<double*>(&_1)];



	test_parser_attr("\x01\x02", little_word, us); assert(us == 0x0201);
	test_parser_attr("\x01\x02\x03\x04", little_dword, ui); assert(ui == 0x04030201);
	test_parser_attr("\x01\x02\x03\x04\x05\x06\x07\x08", little_qword, ul);
	assert(ul == 0x0807060504030201LL);

	test_parser("\x01\x02", little_word(0x0201));
	test_parser("\x01\x02\x03\x04", little_dword(0x04030201));
	test_parser("\x01\x02\x03\x04\x05\x06\x07\x08",
	    little_qword(0x0807060504030201LL));


}
