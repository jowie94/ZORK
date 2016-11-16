#pragma once
#include "entity.h"

enum ITEM_TYPE
{
	COMMON,
	WEAPON,
	ARMOUR,
	HEALTH,
	KEY,
	CONTAINER
};

class Item :
	public Entity
{
public:
	Item(const char* name, const char* description, Entity* parent);
	~Item();

	void Look() const;
	int GetValue() const;

	int MaxValue;
	int MinValue;
	bool Closed;
	bool Openable;

	ITEM_TYPE ItemType;
};

