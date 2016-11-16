#include "finalroom.h"
#include <iostream>

FinalRoom::FinalRoom(const char* name, const char* description, const char* ready_description, vector<bool>* goals)
: Room(name, description), goals(goals), ready_description(ready_description)
{}

FinalRoom::~FinalRoom()
{
}

void FinalRoom::Tick()
{
	int trues = count(goals->begin(), goals->end(), true);
	
	if (trues == goals->size() - 1 && Find(PLAYER))
	{
		(*goals)[trues] = true;
	}
}

void FinalRoom::Look() const
{
	int trues = count(goals->begin(), goals->end(), true);

	if (trues == goals->size() - 1)
	{
		cout << Name << endl << ready_description << endl;
	}
	else
	{
		Room::Look();
	}
}
