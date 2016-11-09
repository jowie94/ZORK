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
	// TODO: Search the inventory
}

bool Creature::Equip(const arglist &args)
{
	// TODO
	return true;
}

bool Creature::UnEquip(const arglist& args)
{
	// TODO
	return true;
}

Room* Creature::CurrentRoom() const
{
	return (Room*)parent;
}
