#include "exit.h"
#include <iostream>
#include "room.h"

Exit::Exit(const char* direction, const char* opposite_direction, const char* description, Room* origin, Room* destination) 
: Entity(direction, description, origin), Locked(false), Closed(false), opposite_direction(opposite_direction), destination(destination)
{
	Type = EXIT;

	destination->SubEntities.push_back(this);
}

Exit::~Exit()
{
}

void Exit::Look() const
{
	cout << Name << " to " << opposite_direction << endl << Description << endl;
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
