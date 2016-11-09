#include "room.h"
#include <iostream>

using namespace std;

Room::Room(const char* name, const char* description) : Entity(name, description, nullptr)
{
	Type = ROOM;
}

Room::~Room()
{
}

void Room::Look()
{
	cout << Name << endl << Description;

	// TODO: Separate elements
	for (Entity* entity : sub_entities)
	{
		cout << entity->Name << endl;
	}
}
