#pragma once
#include "entity.h"
#include "room.h"
#include <vector>
#include "item.h"

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
	int Life;

	Creature* Target;

private:
	Item *weapon;
	Item *armour;
	// TODO: Fields for weapons / armour
};

