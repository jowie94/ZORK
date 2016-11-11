#include "utils.h"

bool str_equals(const std::string& first, const std::string& second)
{
	return str_equals(first.c_str(), second.c_str());
}

bool str_equals(const char* first, const std::string& second)
{
	return str_equals(first, second.c_str());
}

bool str_equals(const std::string& first, const char* second)
{
	return str_equals(first.c_str(), second);
}

bool str_equals(const char* first, const char* second)
{
	return _stricmp(first, second) == 0;
}

void complete_direction(std::string& direction)
{
	if (direction == "n")
	{
		direction = "north";
	}
	else if (direction == "s")
	{
		direction = "south";
	}
	else if (direction == "e")
	{
		direction = "east";
	}
	else if (direction == "w")
	{
		direction = "west";
	}
}
