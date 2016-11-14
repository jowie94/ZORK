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
	virtual void Inventory() const;
	bool Equip(Item* item);
	bool UnEquip(Item* item);

	Room* CurrentRoom() const;

	int MaxHitpoints;
	int MinHitpoints;
	int MaxDefense;
	int MinDefense;
	int Life;

	Creature* Target;

protected:
	Item *weapon;
	Item *armour;
};

