#pragma once
#include <string>

namespace viper
{
	inline std::string toLower(const std::string& str) {
		std::string result = str;
		for (char& c : result) {
			c = std::tolower(c);
		}
		return result;
	}
}