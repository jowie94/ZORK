#include "item.h"
#include <iostream>
#include "utils.h"


Item::Item(const char* name, const char* description, Entity* parent) : Entity(name, description, parent)
{
	Type = ITEM;
	MinValue = MaxValue = 0;
	ItemType = COMMON;
	Closed = false;
	Openable = false;
}


Item::~Item()
{
}

void Item::Look() const
{
	if (ItemType == CONTAINER && SubEntities.size() > 0)
	{
		if (!Closed)
		{
			cout << Name << " contains: " << endl;
			for (Entity* entity : SubEntities)
			{
				cout << " - " << entity->Name << endl;
			}
			cout << endl;
		}
		else
		{
			cout << Name << "(closed)" << endl << Description << endl << endl;
		}
	}
	else
	{
		Entity::Look();
	}
}

int Item::GetValue() const
{
	return randomize(MinValue, MaxValue);
}
