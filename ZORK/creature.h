#pragma once
#include "entity.h"
#include "room.h"
#include <vector>

class Creature :
	public Entity
{
public:
	Creature(const char* name, const char* description, Room* parent);
	virtual ~Creature();

	void Look() const;
	void Tick();

	bool IsAlive() const;
	void Inventory() const;
	virtual bool Equip(const arglist &args);
	virtual bool UnEquip(const arglist &args);

	Room* CurrentRoom() const;

	int MaxHitpoints;
	int MinHitpoints;
	int MaxDefense;
	int MinDefense;

	Creature* Target;

private:
	int life;

	// TODO: Fields for weapons / armour
};

