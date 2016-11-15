#pragma once
#include "entity.h"
#include "room.h"
#include <vector>
#include "item.h"

class AI;

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
	void AttackTarget();
	void ReceiveAttack(int amount);
	void Die();
	void Stats() const;

	Room* CurrentRoom() const;
	bool IsPlayerInRoom() const;

	int MaxHitpoints;
	int MinHitpoints;
	int MaxDefense;
	int MinDefense;
	int Life;

	Creature* Target;
	AI* AI;

protected:
	int GetDefense() const;
	int GetAttackDamage() const;

	Item *weapon;
	Item *armour;
};

