#include "stdafx.h"
#include "MemoryInputStream.h"
#include "FileInputStream.h"
#include "ByteReplacementTable.h"

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	ByteReplacementTable table(10);

	/*MemoryInputStream strm({});
	std::vector<uint8_t> destination(3);
	auto readBytesCount = strm.ReadBlock(destination.data(), destination.size());
	std::cout << "Read " << readBytesCount << " bytes" << std::endl;*/
	return 0;
}
