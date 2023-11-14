#include "common/file_handler.h"
#include <cassert>

FileHandler::FileHandler(const fs::path &path)
{
    file_ = nullptr;
	if (path.is_absolute() and fs::exists(path) and fs::is_regular_file(path))
	{
        file_ = fopen(path.c_str(), "r+");
        if(file_ != nullptr)
            file_path_ = std::string(path);
    }
}

bool FileHandler::IsAssociated()
{
	return !file_path_.empty() and file_ != nullptr;
}