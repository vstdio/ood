#pragma once
#include <string>

class StringUtils
{
public:
	StringUtils() = delete;
	static std::string FloatToString(float value, unsigned precision);
};
