#include <fstream>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/spirit/include/classic_position_iterator.hpp>
#include <boost/spirit/home/qi/operator/expect.hpp>

namespace junk
{

struct istreambuf_range
{
	typedef std::istreambuf_iterator<char> iterator;
	typedef boost::spirit::qi::expectation_failure<iterator> expectation_failure;

	istreambuf_range(std::ifstream& streambuf) :
		begin(streambuf)
	{
	}

	iterator begin, end;
};

struct forward_range
{
	typedef boost::spirit::multi_pass<istreambuf_range::iterator> iterator;
	typedef boost::spirit::qi::expectation_failure<iterator> expectation_failure;

	forward_range(const istreambuf_range& is) :
		begin(is.begin)
	{
	}

	iterator begin, end;
};

struct position_range
{
	typedef boost::spirit::classic::position_iterator2<forward_range::iterator> iterator;
	typedef boost::spirit::qi::expectation_failure<iterator> expectation_failure;

	position_range(const forward_range& fw, const char* filename) :
		begin(fw.begin, fw.end, filename)
	{
	}

	iterator begin, end;
};

class simple_loader
{
public:
	typedef forward_range::iterator iterator;
	typedef boost::spirit::qi::expectation_failure<iterator> expectation_failure;

	simple_loader(const char* filename) :
		file(filename), istreambuf(file), forward(istreambuf)
	{
	}

	iterator& begin()
	{
		return forward.begin;
	}

	iterator end() const
	{
		return iterator();
	}

	void error(const expectation_failure& failure)
	{
		throw failure;
	}

private:
	std::ifstream file;

	istreambuf_range istreambuf;
	forward_range forward;
};

class error_loader
{
public:
	typedef position_range::iterator iterator;
	typedef boost::spirit::qi::expectation_failure<iterator> expectation_failure;

	error_loader(const char* filename) :
		file(filename), istreambuf(file), forward(istreambuf), position(forward, filename)
	{
	}

	iterator& begin()
	{
		return position.begin;
	}

	iterator end() const
	{
		return iterator();
	}

	void error(const expectation_failure& failure)
	{
		const boost::spirit::classic::file_position_base<std::string>& pos =
				failure.first.get_position();

		std::stringstream msg;
		msg << "parse error at file " << pos.file << " line " << pos.line
				<< " column " << pos.column << std::endl;
		msg << "'" << failure.first.get_currentline() << "'" << std::endl;
		msg << std::setw(pos.column) << " " << "^- here";

		throw std::runtime_error(msg.str());
	}

private:
	std::ifstream file;

	istreambuf_range istreambuf;
	forward_range forward;
	position_range position;
};

} // namespace junk
