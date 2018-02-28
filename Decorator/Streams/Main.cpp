#include "stdafx.h"
#include "MemoryInputStream.h"

int main()
{
	MemoryInputStream strm({});
	std::vector<uint8_t> data(3);
	auto read = strm.ReadBlock(data.data(), data.size());
	std::cout << "Read " << read << " bytes" << std::endl;
	return 0;
}
