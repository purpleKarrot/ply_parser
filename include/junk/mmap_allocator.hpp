extern "C"
{
#include <sys/mman.h>
}

#include <limits>
#include <cstddef>
#include <boost/system/system_error.hpp>

template<typename T>
struct mmap_allocator
{
	typedef std::size_t size_type;
	typedef std::ptrdiff_t difference_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T value_type;

	//rebind
	template<typename U>
	struct rebind
	{
		typedef mmap_allocator<U> other;
	};

	mmap_allocator() throw ()
	{
	}

	mmap_allocator(mmap_allocator const &) throw ()
	{
	}

	template<typename U>
	mmap_allocator(mmap_allocator<U> const &) throw ()
	{
	}

	~mmap_allocator() throw ()
	{
	}

	pointer address(reference value) const
	{
		return &value;
	}

	const_pointer address(const_reference value) const
	{
		return &value;
	}

	size_type max_size() const throw ()
	{
		return std::numeric_limits<size_type>::max() / sizeof(T);
	}

	pointer allocate(size_type num, void* hint = 0)
	{
		void* p = ::mmap(hint, num * sizeof(T), PROT_READ | PROT_WRITE,
				MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

		if (p == MAP_FAILED)
		{
			throw boost::system::system_error(boost::system::error_code(errno,
					boost::system::get_system_category()));
		}

		return reinterpret_cast<pointer> (p);
	}

	void deallocate(pointer p, size_type num)
	{
		::munmap(p, num * sizeof(T));
	}

	void construct(pointer p, const_reference value)
	{
		new (p) T(value);
	}

	void destroy(pointer p)
	{
		p->~T();
	}
};

template<typename T1, typename T2>
bool operator ==(mmap_allocator<T1> const&, mmap_allocator<T2> const&) throw ()
{
	return true;
}

template<typename T1, typename T2>
bool operator !=(mmap_allocator<T1> const&, mmap_allocator<T2> const&) throw ()
{
	return false;
}
