#pragma once
#include "creature.h"
class Player :
	public Creature
{
public:
	Player(const char* name, const char* description, Room* parent);
	~Player();

	void Look(const arglist &args) const;
};

