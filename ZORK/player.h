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
	bool UnLock(const arglist& args);
	bool Lock(const arglist& args);
	bool Equip(const arglist& args);
	bool UnEquip(const arglist& args);
	bool Attack(const arglist& args);
	void Stats(const arglist& args);
	bool Examine(const arglist& args);
	bool Loot(const arglist& args);
};

