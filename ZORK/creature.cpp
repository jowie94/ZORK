#include "creature.h"
#include <iostream>
#include <string>
#include "ai.h"
#include "utils.h"

using namespace std;

Creature::Creature(const char* name, const char* description, Room* parent) : Entity(name, description, parent)
{
	Type = CREATURE;
	MaxHitpoints = MinHitpoints = MaxDefense = MinDefense = 0;
	Life = 1;

	Target = nullptr;
	AI = nullptr;
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
		cout << Name << "'s corpse is here" << endl;
	}
}

void Creature::Tick()
{
	if (AI && IsAlive())
	{
		AI->Tick();
	}
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

void Creature::AttackTarget()
{
	int damage = GetAttackDamage();

	if (IsPlayerInRoom())
	{
		cout << Target->Name << " receives " << damage << " hit points from " << Name << endl;
	}

	Target->ReceiveAttack(damage, this);
}

void Creature::ReceiveAttack(int amount, Creature* who)
{
	int defense = GetDefense();
	int received = amount - defense;

	if (received < 0)
	{
		received = 0;
	}

	Life -= received;

	if (IsPlayerInRoom())
	{
		cout << Name << " gets a hit for " << received << " life points (" << defense << " blocked)" << endl;
	}

	if (AI) {
		AI->OnAttacked(who);
	}

	if (!IsAlive())
	{
		Die();
	}
}

void Creature::Die()
{
	if (AI)
	{
		AI->OnDie();
	}
}

void Creature::Stats() const
{
	cout << Name << " stats:" << endl;
	cout << " - Life: " << Life << endl;
	cout << " - Weapon: " << (weapon ? weapon->Name : "no weapon") << endl;
	cout << " - Damage: " << (weapon ? weapon->MinValue : MinHitpoints) << " ~ " << (weapon ? weapon->MaxValue : MaxHitpoints) << endl;
	cout << " - Armour: " << (armour ? armour->Name : "no armour") << endl;
	cout << " - Defense: " << (armour ? armour->MinValue : MinDefense) << " ~ " << (armour ? armour->MaxValue : MaxDefense) << endl;
}

Room* Creature::CurrentRoom() const
{
	return (Room*)parent;
}

bool Creature::IsPlayerInRoom() const
{
	return parent->Find(PLAYER) != nullptr;
}

int Creature::GetDefense() const
{
	return armour ? armour->GetValue() : randomize(MinDefense, MaxDefense);
}

int Creature::GetAttackDamage() const
{
	return weapon ? weapon->GetValue() : randomize(MinHitpoints, MaxHitpoints);
}
