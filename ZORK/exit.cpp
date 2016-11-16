#include "exit.h"
#include <iostream>
#include "room.h"
#include "item.h"

Exit::Exit(const char* direction, const char* opposite_direction, const char* description, Room* origin, Room* destination, Item* key) 
: Entity(direction, description, origin), Locked(key!=nullptr), Closed(Locked), opposite_direction(opposite_direction), destination(destination), key(key)
{
	Type = EXIT;

	destination->SubEntities.push_back(this);
}

Exit::~Exit()
{
}

void Exit::Look() const
{
	cout << Name << " to " << opposite_direction << endl << Description << endl << endl;
}

const string& Exit::GetExitDirectionFrom(const Room* room) const
{
	
	if (room == parent) 
	{
		return Name;
	}
	
	if (room == destination)
	{
		return opposite_direction;
	}

	return Name;
}

Room* Exit::GetExitDestinationFrom(const Room* room) const
{
	Room* destination = nullptr;
	
	if (room == parent)
	{
		destination = this->destination;
	}
	else if (room == this->destination)
	{
		destination = (Room*)parent;
	}

	return destination;
}

bool Exit::UnLock(Item* key)
{
	if (Locked && key->ItemType == KEY)
	{
		Locked = key != this->key;
	}

	return !Locked;
}

bool Exit::Lock(Item* key)
{
	if (!Locked && key->ItemType == KEY)
	{
		Locked = Closed = true;
		this->key = key;
	}

	return Locked;
}
