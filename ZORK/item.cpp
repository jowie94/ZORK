#include "item.h"



Item::Item(const char* name, const char* description, Entity* parent) : Entity(name, description, parent)
{
	Type = ITEM;
	MinValue = MaxValue = 0;
	ItemType = WEAPON;
}


Item::~Item()
{
}
