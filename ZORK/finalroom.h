#pragma once
#include "room.h"

class FinalRoom : public Room
{
public:
	FinalRoom(const char* name, const char* description, vector<bool>* goals);

	~FinalRoom();


	void Tick();
private:
	vector<bool>* goals;
};

