#pragma once

#include <string>

namespace StringHelper
{
	std::string Trim(const std::string&);
	std::string TrimStart(const std::string&);
	std::string TrimEnd(const std::string&);
	bool IsEmptyOrWhiteSpace(const std::string&);
}
