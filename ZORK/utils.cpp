#include "utils.h"
#include <vector>
#include <iostream>

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

int randomize(int min, int max)
{
	return max > 0 ? min + rand() % (max - min) : 0;
}

bool all(std::vector<bool>& list)
{
	for (bool element : list)
	{
		if (!element)
		{
			return false;
		}
	}

	return true;
}

void help()
{
	std::cout << "- look: Gives you information about the current room." << std::endl
		<< "- look me: Gives information about you." << std::endl
		<< "- look object_name: Gives information about an object." << std::endl
		<< "- north|south|east|west: Go to the room on that direction." << std::endl
		<< "- pick|take object_name: Pick the specified object and save it into the inventory." << std::endl
		<< "- pick|take object_name from container_name: Picks the specified object from the specified container and saves it into the inventory." << std::endl
		<< "- drop object_name: Leave the object on the floor." << std::endl
		<< "- drop object_name into container_name: Leave the object inside a container." << std::endl
		<< "- open north|south|east|west door: Try to open a door." << std::endl
		<< "- close north|south|east|west door: Try to close a door." << std::endl
		<< "- open object Try to open an object." << std::endl
		<< "- close object Try to close an object." << std::endl
		<< "- unlock north|south|east|west door with object_name: Try to unlock a door with an item of your inventory." << std::endl
		<< "- lock north|south|east|west door with object_name: Try to lock a door with an item of your inventory." << std::endl
		<< "- equip weapon_name|armour_name: Equip the specified weapon or armour." << std::endl
		<< "- unequip weapon|armour|weapon_name|armour_name: Unequip the specified weapon or armour." << std::endl
		<< "- attack creature_name: Attack to the specified creature." << std::endl
		<< "- attack: Attack to the last creature attacked." << std::endl
		<< "- stats: Gives your current stats." << std::endl
		<< "- examine creature_name: Gives information about a creature." << std::endl
		<< "- loot creature_name: Loots a creature and gets its objects if dead." << std::endl
		<< "- help: This help message." << std::endl
		<< "- quit: Exits the game." << std::endl << std::endl;
}
