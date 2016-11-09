#include "player.h"
#include <iostream>

Player::Player(const char* name, const char* description, Room* parent) : Creature(name, description, parent)
{
	Type = PLAYER;
}


Player::~Player()
{
}

void Player::Look(const vector<string> &args) const
{
	if (args.size() > 1)
	{
		if (args[1] == "me")
		{
			Creature::Look();
		}
		else
		{
			string arg = args[1];
			Entity* entity = parent->Find(arg);
			if (entity != nullptr)
			{
				entity->Look();
			}
		}
	}
	else
	{
		CurrentRoom()->Look();
	}
}

bool Player::Pick(const arglist& args)
{
	bool ret = true;
	if (args.size() == 2)
	{
		Entity* item = parent->Find(args[1], ITEM);

		if (item != nullptr)
		{
			item->ChangeParent(this);
		} 
		else
		{
			cout << "Couldn't find item " << args[1] << endl;
		}
	}
	else if (args.size() == 4)
	{
		Entity* container = parent->Find(args[3], ITEM);

		if (container == nullptr) // If it is not in the room, try to find it in the inventory
		{
			container = Find(args[3], ITEM);
		}

		if (container == nullptr)
		{
			cout << "I couldn't find the container " << args[3] << endl;
		}
		else
		{
			Entity* item = container->Find(args[1], ITEM);

			if (item != nullptr)
			{
				item->ChangeParent(this);
			}
			else
			{
				cout << "Couldn't find item " << args[1] << " in container " << args[3] << endl;
			}
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}
