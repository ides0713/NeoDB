#pragma once
#include <filesystem>

namespace fs = std::filesystem;

class FileHandler
{
public:
	FileHandler(const fs::path &path);
	bool IsAssociated();
    

private:
	std::string file_path_;
	FILE *file_;
};