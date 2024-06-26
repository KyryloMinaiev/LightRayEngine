#pragma once

#include <string>
#include <fstream>
#include <sstream>

class FileUtils
{
public:
	static std::string ReadFile(const std::string& path);
	static void WriteFile(const std::string& path, const std::string& content);
};

