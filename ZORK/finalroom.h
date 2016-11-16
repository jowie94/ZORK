#pragma once
#include "room.h"

class FinalRoom : public Room
{
public:
	FinalRoom(const char* name, const char* description, const char* ready_description, vector<bool>* goals);

	~FinalRoom();

	void Tick();
	void Look() const;

private:
	vector<bool>* goals;
	const char* ready_description;
};

