#include <fstream>
#include <iostream>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(ply_gz)
{
	std::ifstream file("bunny.ply.gz", std::ios_base::in | std::ios_base::binary);

	BOOST_REQUIRE(file.good());

	boost::iostreams::filtering_istreambuf inbuf;
	inbuf.push(boost::iostreams::gzip_decompressor());
	inbuf.push(file);

	std::istream istream(&inbuf);

	char magic[3];
	istream.read(magic, 3);

	BOOST_REQUIRE_EQUAL(magic[0], 'p');
	BOOST_REQUIRE_EQUAL(magic[1], 'l');
	BOOST_REQUIRE_EQUAL(magic[2], 'y');

	istream.ignore(1);

	std::string line;
	while (std::getline(istream, line))
	{
		BOOST_MESSAGE(line);

		if (line == "end_header")
			break;
	}
}
