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
	cout << Name << endl << Description << endl;

	// TODO: Separate elements
	for (Entity* entity : SubEntities)
	{
		if (entity->Type != PLAYER)
			cout << entity->Name << endl;
	}
}

Exit* Room::GetExitAt(const string& direction)
{
	for (Entity* entity : SubEntities)
	{
		if (entity-> Type == EXIT && ((Exit*)entity)->GetExitDirectionFrom(this) == direction)
		{
			return (Exit*)entity;
		}
	}

	return nullptr;
}
