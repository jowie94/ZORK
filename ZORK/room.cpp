#include "room.h"
#include <iostream>
#include "creature.h"

using namespace std;

Room::Room(const char* name, const char* description) : Entity(name, description, nullptr)
{
	Type = ROOM;
}

Room::~Room()
{
}

void Room::Look() const
{
	cout << Name << endl << Description << endl;

	list<Entity*> entities;
	FindAll(ITEM, entities);

	if (entities.size() > 0)
	{
		cout << "Items here:" << endl;
		for (Entity* entity : entities)
		{
			cout << " - " << entity->Name << endl;
		}
	}

	entities.clear();
	FindAll(CREATURE, entities);

	if (entities.size() > 0)
	{
		cout << "You are not alone:" << endl;
		for (Entity* entity : entities)
		{
			cout << " - " << entity->Name;
			if (!((Creature*)entity)->IsAlive())
			{
				cout << " (dead)";
			}

			cout << endl;
		}
	}

	entities.clear();
	FindAll(EXIT, entities);

	if (entities.size() > 0)
	{
		cout << "Exits here:" << endl;
		for (Entity* entity : entities)
		{
			Exit* exit = (Exit*)entity;
			cout << " - Direction " << exit->GetExitDirectionFrom(this) << " you go to " << exit->GetExitDestinationFrom(this)->Name;
			if (exit->Locked)
			{
				cout << " (locked)";
			}
			else if (exit->Closed)
			{
				cout << " (closed)";
			}
			cout << endl;
		}
	}

	cout << endl;
}

Exit* Room::GetExitAt(const string& direction)
{
	for (Entity* entity : SubEntities)
	{
		if (entity-> Type == EXIT && ((Exit*)entity)->GetExitDirectionFrom(this) == direction)
		{
			return (Exit*)entity;
		}
	}

	return nullptr;
}
