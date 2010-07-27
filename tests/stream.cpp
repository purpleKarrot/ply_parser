#include <fstream>
#include <sstream>
#include <stream/stream.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(stream_test)
{
	std::ifstream file("stream.stream");
	BOOST_REQUIRE(file);

	std::string line;
	std::size_t line_number = 0;

	stream::header header;

	while (std::getline(file, line))
	{
		++line_number;
		std::istringstream stringstream(line);

		stringstream >> std::ws;
		if (stringstream.eof())
			continue;

		std::string keyword;
		stringstream >> keyword;

		if (keyword[0] == '#')
			continue;

		if (keyword == "min")
		{
			stream::vec3& vec = header.min;
			stringstream >> vec.x >> vec.y >> vec.z;
			continue;
		}

		if (keyword == "max")
		{
			stream::vec3& vec = header.max;
			stringstream >> vec.x >> vec.y >> vec.z;
			continue;
		}

		if (keyword == "endian")
		{
			std::string endian;
			stringstream >> endian;

			if (endian == "little")
			{
				header.endian == stream::little;
			}
			else if (endian == "big")
			{
				header.endian == stream::big;
			}
			else
			{
				BOOST_FAIL("invalid endian " << endian);
			}
			continue;
		}

		if (keyword == "transform")
		{
			float* m = header.transform.m;
			stringstream >> m[0] >> m[1] >> m[2] >> m[3] >> m[4] >> m[5] >> m[6] >> m[7] >> m[8] >> m[9] >> m[10] >> m[11] >> m[12] >> m[13] >> m[14] >> m[15];
			continue;
		}

		if (keyword == "element")
		{
			std::string name;
			stringstream >> name;
			header.elements.push_back(name);
			continue;
		}

		for (std::vector<stream::element>::iterator i = header.elements.begin(); i != header.elements.end(); ++i)
		{
			if (keyword == i->name)
			{
				stringstream >> keyword;

				if (keyword == "count")
				{
					stringstream >> i->count;
				}

				if (keyword == "offset")
				{
					stringstream >> i->offset;
				}

				if (keyword == "attribute")
				{
					stream::attribute attribute;
					stringstream >> attribute.name;

					std::string type;
					stringstream >> type;

					if (type == "float")
					{
						attribute.type = stream::float_;
					}
					else if (type == "double")
					{
						attribute.type = stream::double_;
					}
					else if (type == "uint8")
					{
						attribute.type = stream::uint8_;
					}
					else if (type == "int8")
					{
						attribute.type = stream::int8_;
					}
					else if (type == "uint16")
					{
						attribute.type = stream::uint16_;
					}
					else if (type == "int16")
					{
						attribute.type = stream::int16_;
					}
					else if (type == "uint32")
					{
						attribute.type = stream::uint32_;
					}
					else if (type == "int32")
					{
						attribute.type = stream::int32_;
					}
					else if (type == "uint64")
					{
						attribute.type = stream::uint64_;
					}
					else if (type == "int64")
					{
						attribute.type = stream::int64_;
					}
					else if (type == "unknown")
					{
						attribute.type = stream::unknown_;
					}
					else
					{
						BOOST_FAIL("invalid attribute type " << type);
					}

					stringstream >> attribute.array_size;
					stringstream >> attribute.size_in_bytes;
					stringstream >> attribute.flags;
					i->attributes.push_back(attribute);
				}
			}
		}
	}

	for (std::vector<stream::element>::iterator i = header.elements.begin(); i != header.elements.end(); ++i)
	{
		BOOST_MESSAGE("name " << i->name);
		BOOST_MESSAGE("count " << i->count);
		BOOST_MESSAGE("offset " << i->offset);

		for (std::vector<stream::attribute>::iterator k = i->attributes.begin(); k != i->attributes.end(); ++k)
		{
			BOOST_MESSAGE("  name " << k->name);
			BOOST_MESSAGE("  type " << k->type);
			BOOST_MESSAGE("  array_size " << k->array_size);
			BOOST_MESSAGE("  size_in_bytes " << k->size_in_bytes);
			BOOST_MESSAGE("  flags " << k->flags);
		}
	}
}
