#pragma once
#include "creature.h"
class Player :
	public Creature
{
public:
	Player(const char* name, const char* description, Room* parent);
	~Player();

	void Look(const arglist &args) const;
	void Inventory() const;

	bool Pick(const arglist& args);
	bool Drop(const arglist& args);
	bool Move(const arglist& args);
	void Open(const arglist& args);
	void Close(const arglist& args);
	void UnLock(const arglist& args);
	void Lock(const arglist& args);
};

