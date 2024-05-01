#pragma once

#include <filesystem>

namespace fs = std::filesystem;

class FileHandler
{
public:
	FileHandler() = delete;
	FileHandler(const FileHandler &fhandler) = delete;

public:
	static int Write(const fs::path &path, const char *src, int size, const char *mode);
	static int Read(const fs::path &path, char *dest, int size, const char *mode);
};