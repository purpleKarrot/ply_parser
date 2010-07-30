//

class ply;

int main()
{

	ply::element < vec3 > indices = ply.element("indices");

	std::vector<vec3> vec3s;
	std::back_insert_iterator<std::vector<vec3> > back_it(vec3s);

	std::copy(indices.begin(), indices.end(), back_it);

	std::copy(indices.begin() + 100, indices.end() + 200, back_it);

}

using namespace std;

struct x
{
};

namespace std
{

template<class traits>
class basic_istream<x, traits> : public basic_ifstream<uint32_t>
{
public:
	explicit basic_istream<x, traits> (const wchar_t* _Filename, ios_base::openmode _Mode, int _Prot = (int) ios_base::_Openprot) :
		basic_ifstream<uint32_t> (_Filename, _Mode, _Prot)
	{
	}

	basic_istream<x, traits>& operator>>(uint32_t& data)
	{
		read(&data, 1);
		return *this;
	}
};

} // namespace std

int main()
{
	basic_istream<x> file("somefile.dat", ios::in | ios::binary);
	vector<uint32_t> buffer;
	buffer.assign(istream_iterator<uint32_t, x> (file), istream_iterator<uint32_t, x> ());
	cout << buffer.size() << endl;
	return 0;
}
