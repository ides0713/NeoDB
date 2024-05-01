#include "common/file_handler.h"
#include <cassert>
#include <cstdio>

int FileHandler::Write(const fs::path &path, const char *src, int size, const char *mode)
{
	FILE *write_file = fopen(path.c_str(), mode);

	if (write_file == nullptr)
	{
		// todo error open file failed
		assert(false);
	}

	int ret = fwrite(src, 1, size, write_file);
	fclose(write_file);
	return ret;
}

int FileHandler::Read(const fs::path &path, char *dest, int size, const char *mode)
{
	FILE *read_file = fopen(path.c_str(), mode);

	if (read_file == nullptr)
	{
		// todo error open file failed
		assert(false);
	}

	int ret = fread(dest, 1, size, read_file);
	fclose(read_file);
	return ret;
}