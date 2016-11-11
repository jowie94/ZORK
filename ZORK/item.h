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
	bool Closed;
	bool Openable;

	ITEM_TYPE ItemType;
};

