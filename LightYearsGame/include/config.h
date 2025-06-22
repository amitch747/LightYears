#pragma once
#include <string>

std::string GetResourceDir()
{
#ifdef NDEBUG // release build
	return "assets/";
#else
	return "C:/Dev/Projects/LightYears/LightYearsGame/assets/";
#endif
}
