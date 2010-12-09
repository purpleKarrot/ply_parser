#include <vector>
#include <junk/mmap_allocator.hpp>

int main()
{
	//std::vector<int> v;
	std::vector<int, mmap_allocator<int> > v;
	v.reserve(v.max_size() / 4);

	for (size_t i(0); i < (v.max_size() / 4); ++i)
	{
		v.push_back(0);
	}
}
