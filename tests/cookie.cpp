//#define _GNU_SOURCE
#include <stdio.h>
#include <sys/mman.h>

#include <iostream>
#include <boost/shared_ptr.hpp>

ssize_t read(void *cookie, char *buf, size_t size)
{
	std::cout << "reading " << size;
}

ssize_t write(void *cookie, const char *buf, size_t size)
{
}

int seek(void *cookie, off64_t *offset, int whence)
{
	std::cout << "seeking " << *offset << " from " << whence << std::endl;
}

int close(void *cookie)
{
}

static std::size_t length = 10000;

int main(int argc, char* argv[])
{
	cookie_io_functions_t functions;
	functions.read = read;
	functions.write = write;
	functions.seek = seek;
	functions.close = close;

	boost::shared_ptr<FILE> file(fopencookie(NULL, "r", functions), fclose);

	void* buffer = mmap(0, length, PROT_READ, MAP_SHARED, file.get(), 0);

	char c;
	for (std::size_t i = 0; i < length; ++i)
	{
		c |= buffer[i];
	}

	int munmap(buffer, length);
}
