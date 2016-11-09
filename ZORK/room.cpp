#include "room.h"

Room::Room(const char* name, const char* description) : Entity(name, description, nullptr)
{
	Type = ROOM;
}

Room::~Room()
{
}
