#include "item.h"
#include <iostream>


Item::Item(const char* name, const char* description, Entity* parent) : Entity(name, description, parent)
{
	Type = ITEM;
	MinValue = MaxValue = 0;
	ItemType = WEAPON;
	Closed = false;
	Openable = false;
}


Item::~Item()
{
}

void Item::Look() const
{
	if (SubEntities.size() > 0)
	{
		cout << Name << " contains: " << endl;
		for (Entity* entity : SubEntities)
		{
			cout << " - " << entity->Name << endl;
		}
	}
	else
	{
		Entity::Look();
	}
}
