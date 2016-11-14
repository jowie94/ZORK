#include "creature.h"
#include <iostream>
#include <string>

using namespace std;

Creature::Creature(const char* name, const char* description, Room* parent) : Entity(name, description, parent)
{
	Type = CREATURE;
	MaxHitpoints = MinHitpoints = MaxDefense = MinDefense = 0;
	Life = 1;

	Target = nullptr;
	weapon = armour = nullptr;
}


Creature::~Creature()
{}

void Creature::Look() const
{
	if (IsAlive())
	{
		Entity::Look();
	}
	else
	{
		cout << Name << " 's corpse is here" << endl;
	}
}

void Creature::Tick()
{
	// TODO: Logic
}

bool Creature::IsAlive() const
{
	return Life > 0;
}

void Creature::Inventory() const
{
	list<Entity*> inventory;
	FindAll(ITEM, inventory);

	if (inventory.size() == 0)
	{
		cout << Name << " doesn't own anything :(" << endl;
	}
	else
	{
		cout << Name << " owns:" << endl;
		for (Entity* item : inventory)
		{
			cout << " - " << item->Name;
			
			if (item == armour)
			{
				cout << " (as armour)";
			}
			else if (item == weapon)
			{
				cout << " (as weapon)";
			}

			cout << endl;
		}
	}
}

bool Creature::Equip(Item* item)
{
	bool res = false;

	if (item->ItemType == ARMOUR)
	{
		armour = item;
		res = true;
	}
	else if (item->ItemType == WEAPON)
	{
		weapon = item;
		res = true;
	}

	return res;
}

bool Creature::UnEquip(Item* item)
{
	bool res = false;

	if (item->ItemType == ARMOUR && item == armour)
	{
		armour = nullptr;
		res = true;
	}
	else if (item->ItemType == WEAPON && item == weapon)
	{
		weapon = nullptr;
		res = true;
	}

	return res;
}

Room* Creature::CurrentRoom() const
{
	return (Room*)parent;
}
