//

#include <fstream>
#include <iostream>
#include <junk/out_iterator.hpp>
#include <cassert>

template<typename T, typename Base>
inline output_range_iterator<T, Base> make_out_iter(const Base& base,
		std::size_t begin, std::size_t end)
{
	return output_range_iterator<T, Base> (base, begin, end);
}

template<typename T, std::size_t N>
inline output_range_iterator<T, T*> make_out_iter(T(&array)[N], int begin,
		std::size_t end)
{
	assert(N >= end - begin);
	return output_range_iterator<T, T*> (array, begin, end);
}

int main(int argc, char* argv[])
{
	std::ifstream file("faces.txt");

	std::ostream_iterator<int> out_it(std::cout, ", ");

	int array[4];

	std::copy(std::istream_iterator<int>(file), // begin
			std::istream_iterator<int>(), // end
			make_out_iter<int> (array, 3, 7));
}
