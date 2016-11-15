#include "finalroom.h"

FinalRoom::FinalRoom(const char* name, const char* description, vector<bool>* goals)
: Room(name, description)
{
	this->goals = goals;
}

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

