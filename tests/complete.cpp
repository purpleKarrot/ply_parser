#include <ply/header_grammar.hpp>
#include <ply/element_grammar.hpp>

#include <fstream>
#include <sstream>
#include <boost/test/unit_test.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/fusion/adapted/struct/define_struct.hpp>

#include <junk/iterator.hpp>
#include <junk/element_parser.hpp>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;
namespace classic = boost::spirit::classic;

struct vertex_
{
	//float x, y, z;
	float intensity;
	float confidence;
};

BOOST_FUSION_ADAPT_STRUCT(vertex_,
		(float, intensity)
		(float, confidence)
)

template<typename Iterator>
void parse_ply_header(Iterator& begin, Iterator end, ply::header& header)
{
	static BOOST_AUTO(comment, qi::lit("comment") >> *(ascii::char_ - qi::eol) >> qi::eol);
	static BOOST_AUTO(skip, ascii::blank | comment);

	static ply::header_grammar<Iterator, BOOST_TYPEOF(skip)> grammar;

	qi::phrase_parse(begin, end, grammar, skip, header);
}

template<typename OutputIterator>
struct value_type
{
};

template<typename Container>
struct value_type<std::back_insert_iterator<Container> >
{
	typedef typename Container::value_type type;
};

template<typename Iterator, typename OutputIterator>
void parse_ply_element(Iterator& begin, Iterator end, const ply::element& element, OutputIterator output)
{
	typedef typename value_type<OutputIterator>::type value_t;
	ply::element_grammar<Iterator, ascii::blank_type, value_t> grammar(element);

	typedef element_phrase_parser<value_t, Iterator, ascii::blank_type> parser_t;
	boost::shared_ptr<parser_t> parser(new parser_t(begin, end, grammar, ascii::blank, element.count));

	typedef ::iterator<value_t, parser_t> parse_iterator;
	std::copy(parse_iterator(parser), parse_iterator(), output);
}

BOOST_AUTO_TEST_CASE(complete)
{
	std::ifstream file("bunny.ply");
	BOOST_REQUIRE(file);

	// iterate over stream input
	typedef std::istreambuf_iterator<char> base_iterator_type;
	base_iterator_type in_begin(file);

	// convert input iterator to forward iterator, usable by spirit parser
	typedef boost::spirit::multi_pass<base_iterator_type> forward_iterator_type;
	forward_iterator_type fwd_begin = boost::spirit::make_default_multi_pass(
			in_begin);
	forward_iterator_type fwd_end;

	// wrap forward iterator with position iterator, to record the position
	typedef classic::position_iterator2<forward_iterator_type> iterator;
	iterator position_begin(fwd_begin, fwd_end, "bunny.ply");
	iterator position_end;

	// parse
	try
	{
		ply::header header;
		parse_ply_header(position_begin, position_end, header);

		std::vector<vertex_> vertices;
		parse_ply_element(position_begin, position_end, header.elements[0],
				std::back_inserter(vertices));

 		BOOST_CHECK_EQUAL(vertices.size(), header.elements[0].count);

 		for (int i = 0; i < 10; ++i)
		{
 			BOOST_MESSAGE(i << ": " << vertices[i].intensity);
		}
	}
	catch (const qi::expectation_failure<iterator>& e)
	{
		const classic::file_position_base<std::string>& pos =
				e.first.get_position();

		std::stringstream msg;
		msg << "parse error at file " << pos.file << " line " << pos.line
				<< " column " << pos.column << std::endl;
		msg << "'" << e.first.get_currentline() << "'" << std::endl;
		msg << std::setw(pos.column) << " " << "^- here";

		BOOST_FAIL(msg.str());
	}
}
