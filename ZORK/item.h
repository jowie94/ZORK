#pragma once
#include "entity.h"

enum ITEM_TYPE
{
	WEAPON,
	ARMOUR,
	HEALTH
};

class Item :
	public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent);
	~Item();

	int MaxValue;
	int MinValue;

	ITEM_TYPE ItemType;
};

