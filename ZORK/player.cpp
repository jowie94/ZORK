#include "player.h"

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
