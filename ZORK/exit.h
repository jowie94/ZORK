#pragma once
#include "entity.h"

class Room;

class Exit :
	public Entity
{
public:
	Exit(const char* direction, const char* opposite_direction, const char* description, Room* origin, Room* destination);
	~Exit();

	void Look() const;

	const string& GetExitDirectionFrom(const Room* room) const;
	Room* GetExitDestinationFrom(const Room* room) const;
			 
	bool Locked;
	bool Closed;

private:
	string opposite_direction;
	Room* destination;
};

