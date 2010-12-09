#include <Maoni.hpp>
#include <fstream>
#include <iostream>

#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

#include <ply/header_grammar.hpp>
#include <ply/element_grammar.hpp>

#define PLY_LOADER(SUF, EXT, NAME) MESH_LOADER_I(ply_loader##SUF, #NAME, #EXT)

PLY_LOADER(, ply, Stanford PLY)
{
	std::ifstream file(filename);

	// iterate over stream input
	typedef std::istreambuf_iterator<char> base_iterator_type;
	base_iterator_type in_begin(file);

}

PLY_LOADER(_gz, ply.gz, Stanford PLY (gz))
{
	std::ifstream file(filename, std::ios_base::in | std::ios_base::binary);

	boost::iostreams::filtering_istreambuf inbuf;
	inbuf.push(boost::iostreams::gzip_decompressor());
	inbuf.push(file);

	// iterate over stream input
	typedef std::istreambuf_iterator<char> base_iterator_type;
	base_iterator_type in_begin(&inbuf);

}

PLY_LOADER(_bz2, ply.bz2, Stanford PLY (bz2))
{
	std::ifstream file(filename, std::ios_base::in | std::ios_base::binary);

	boost::iostreams::filtering_istreambuf inbuf;
	inbuf.push(boost::iostreams::bzip2_decompressor());
	inbuf.push(file);

	// iterate over stream input
	typedef std::istreambuf_iterator<char> base_iterator_type;
	base_iterator_type in_begin(&inbuf);

}
