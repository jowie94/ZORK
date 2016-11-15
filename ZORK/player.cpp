#include "player.h"
#include <iostream>
#include "exit.h"

Player::Player(const char* name, const char* description, Room* parent) : Creature(name, description, parent)
{
	Type = PLAYER;
}


Player::~Player()
{
}

void Player::Look(const vector<string>& args) const
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

void Player::Inventory() const
{
	list<Entity*> inventory;
	FindAll(ITEM, inventory);

	if (inventory.size() == 0)
	{
		cout << "You don't own anything :(" << endl;
	}
	else
	{
		cout << "You own:" << endl;
		for (Entity* item : inventory)
		{
			cout << " - " << item->Name;

			if (item == armour)
			{
				cout << " (as armour)";
			}
			else if (item == weapon)
			{
				cout << " (as weapon)";
			}

			cout << endl;
		}
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
			cout << "You picked up " << item->Name << endl;
		}
		else
		{
			cout << "Couldn't find item " << args[1] << endl;
		}
	}
	else if (args.size() == 4)
	{
		Item* container = (Item*)parent->Find(args[3], ITEM);

		if (container == nullptr) // If it is not in the room, try to find it in the inventory
		{
			container = (Item*)Find(args[3], ITEM);
		}

		if (container == nullptr)
		{
			cout << "Couldn't find the container " << args[3] << endl;
		}
		else if (container->Closed)
		{
			cout << "The " << args[3] << " is closed!" << endl;
		}
		else
		{
			Entity* item = container->Find(args[1], ITEM);

			if (item != nullptr)
			{
				item->ChangeParent(this);
				cout << "You picked up " << item->Name << " from " << container->Name << endl;
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

bool Player::Drop(const arglist& args)
{
	bool ret = true;
	if (args.size() == 2)
	{
		Entity* item = Find(args[1], ITEM);

		if (item != nullptr)
		{
			item->ChangeParent(parent);
			if (item == weapon)
			{
				weapon = nullptr;
			}
			if (item == armour)
			{
				armour = nullptr;
			}
			cout << "You dropped " << item->Name << endl;
		}
		else
		{
			cout << "Couldn't find item " << args[1] << "in your inventory." << endl;
		}
	}
	else if (args.size() == 4)
	{
		Item* container = (Item*)parent->Find(args[3], ITEM);

		if (container == nullptr) // If it is not in the room, try to find it in the inventory
		{
			container = (Item*)Find(args[3], ITEM);
		}

		if (container == nullptr)
		{
			cout << "Couldn't find the container " << args[3] << endl;
		}
		else if (container->Closed)
		{
			cout << "The " << args[3] << " is closed!" << endl;
		}
		else
		{
			Entity* item = Find(args[1], ITEM);

			if (item != nullptr)
			{
				item->ChangeParent(container);
				cout << "You dropped " << item->Name << " into " << container->Name << endl;
			}
			else
			{
				cout << "Couldn't find item " << args[1] << " in your inventory." << endl;
			}
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}

bool Player::Move(const arglist& args)
{
	Exit* exit = CurrentRoom()->GetExitAt(args[0]);

	if (exit == nullptr)
	{
		cout << "There's no door in that direction (" << args[0] << ")." << endl;
	}
	else
	{
		if (exit->Locked)
		{
			cout << "This door is locked!" << endl;
		}
		else if (exit->Closed)
		{
			cout << "This door is closed!" << endl;
		}
		else
		{
			cout << "You go through the " << args[0] << " door..." << endl;
			Room* newRoom = exit->GetExitDestinationFrom(CurrentRoom());
			ChangeParent(newRoom);
			newRoom->Look();
		}
	}

	return true;
}

void Player::Open(const arglist& args)
{
	if (args.size() >= 3 && args[2] == "door")
	{
		Exit* exit = CurrentRoom()->GetExitAt(args[1]);

		if (exit == nullptr)
		{
			cout << "There's no door in that direction (" << args[1] << ")." << endl;
		}
		else if (exit->Locked)
		{
			cout << "That door is locked with a key!" << endl;
		}
		else if (!exit->Closed)
		{
			cout << "That door is already opened!" << endl;
		}
		else
		{
			exit->Closed = false;
			cout << "You opened the " << exit->GetExitDirectionFrom(CurrentRoom()) << " door!" << endl;
		}
	}
	else
	{
		Item* container = (Item*)CurrentRoom()->Find(args[1], ITEM);

		if (container == nullptr) // If it is not in the room, try to find it in the inventory
		{
			container = (Item*)Find(args[1], ITEM);
		}

		if (container == nullptr || !container->Openable)
		{
			cout << "There's no openable object called " << args[1] << endl;
		}
		else if (!container->Closed)
		{
			cout << "This container is already opened!" << endl;
		}
		else
		{
			container->Closed = false;
			cout << "You opened " << args[1] << "!" << endl;
		}
	}
}

void Player::Close(const arglist& args)
{
	if (args.size() >= 3 && args[2] == "door")
	{
		Exit* exit = CurrentRoom()->GetExitAt(args[1]);

		if (exit == nullptr)
		{
			cout << "There's no door in that direction (" << args[1] << ")." << endl;
		}
		else if (exit->Closed)
		{
			cout << "That door is already closed!" << endl;
		}
		else
		{
			exit->Closed = true;
			cout << "You closed the " << exit->GetExitDirectionFrom(CurrentRoom()) << " door!" << endl;
		}
	}
	else
	{
		Item* container = (Item*)CurrentRoom()->Find(args[1], ITEM);

		if (container == nullptr) // If it is not in the room, try to find it in the inventory
		{
			container = (Item*)Find(args[1], ITEM);
		}

		if (container == nullptr || !container->Openable)
		{
			cout << "There's no closeable object called " << args[1] << endl;
		}
		else if (container->Closed)
		{
			cout << "This container is already closed!" << endl;
		}
		else
		{
			container->Closed = true;
			cout << "You closed " << args[1] << "!" << endl;
		}
	}
}

bool Player::UnLock(const arglist& args)
{
	bool res = true;

	if (args.size() == 5)
	{
		Exit* exit = CurrentRoom()->GetExitAt(args[1]);

		if (exit == nullptr)
		{
			cout << "There's no door in that direction (" << args[1] << ")." << endl;
		}
		else if (!exit->Locked)
		{
			cout << "The door is not locked!" << endl;
		}
		else
		{
			Item* key = (Item*)Find(args[4], ITEM);

			if (key == nullptr)
			{
				cout << "You don't own " << args[4] << "!" << endl;
			}
			else if (exit->UnLock(key))
			{
				cout << "You unlocked the " << exit->GetExitDirectionFrom(CurrentRoom()) << " door!" << endl;
			}
			else
			{
				cout << "You can't unlock " << exit->GetExitDirectionFrom(CurrentRoom()) << " door with " << key->Name << "." << endl;
			}
		}
	}
	else
	{
		res = false;
	}

	return res;
}

bool Player::Lock(const arglist& args)
{
	bool res = true;

	if (args.size() == 5)
	{
		Exit* exit = CurrentRoom()->GetExitAt(args[1]);

		if (exit == nullptr)
		{
			cout << "There's no door in that direction (" << args[1] << ")." << endl;
		}
		else if (exit->Locked)
		{
			cout << "The door is locked!" << endl;
		}
		else
		{
			Item* key = (Item*)Find(args[4], ITEM);

			if (key == nullptr)
			{
				cout << "You don't own " << args[4] << "!" << endl;
			}
			else if (exit->Lock(key))
			{
				cout << "You locked the " << exit->GetExitDirectionFrom(CurrentRoom()) << " door!" << endl;
			}
			else
			{
				cout << "You can't lock " << exit->GetExitDirectionFrom(CurrentRoom()) << " door with " << key->Name << "." << endl;
			}
		}
	}
	else
	{
		res = false;
	}

	return res;
}

bool Player::Equip(const arglist& args)
{
	bool ret = true;

	if (args.size() == 2)
	{
		Item* equip = (Item*)Find(args[1], ITEM);
		if (equip != nullptr)
		{
			if (Creature::Equip(equip))
			{
				cout << "You equipped " << equip->Name << endl;
			}
			else
			{
				cout << "You can't equip " << equip->Name << endl;
			}
		}
		else
		{
			cout << "You don't own " << args[1] << endl;
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}

bool Player::UnEquip(const arglist& args)
{
	bool ret = true;

	if (args.size() == 2)
	{
		Item* object = nullptr;

		if (args[1] == "weapon")
		{
			object = weapon;
		}
		else if (args[1] == "armour")
		{
			object = armour;
		}
		else
		{
			object = (Item*)Find(args[1], ITEM);
		}

		if (object == nullptr || !Creature::UnEquip(object))
		{
			cout << "You can't unequip " << args[1] << endl;
		}
		else
		{
			cout << "You unequipped " << object->Name << endl;
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}

bool Player::Attack(const arglist& args)
{
	bool ret = true;

	if (args.size() == 1)
	{
		if (Target)
		{
			AttackTarget();
		}
		else
		{
			cout << "You aren't focusing any enemy!" << endl;
		}
	}
	else if (args.size() == 2)
	{
		Entity* target = parent->Find(args[1], CREATURE);

		if (target == nullptr)
		{
			cout << args[1] << " is not in this room!" << endl;
		}
		else
		{
			Target = (Creature*)target;
			AttackTarget();
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}

void Player::Stats(const arglist& args)
{
	Creature::Stats();
}

bool Player::Examine(const arglist& args)
{
	bool ret = true;

	if (args.size() == 2)
	{
		Creature* creature = (Creature*)parent->Find(args[1], CREATURE);

		if (creature == nullptr)
		{
			cout << args[1] << " isn't here!" << endl;
		}
		else
		{
			creature->Stats();

			if (!creature->IsAlive())
			{
				creature->Inventory();
			}
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}

bool Player::Loot(const arglist& args)
{
	bool ret = true;

	if (args.size() == 2)
	{
		Creature* creature = (Creature*)parent->Find(args[1], CREATURE);

		if (creature == nullptr)
		{
			cout << args[1] << " isn't here!" << endl;
		}
		else if (creature->Life > 0)
		{
			cout << "You can't loot when it's still alive!" << endl;
		}
		{
			list<Entity*> items;
			creature->FindAll(ITEM, items);

			if (items.size() > 0)
			{
				cout << "You loot " << creature->Name << " corpse and found:" << endl;

				for (Entity* entity : items)
				{
					cout << " - " << entity->Name << endl;
					entity->ChangeParent(this);
				}
			}
			else
			{
				cout << "You loot " << creature->Name << " corpse but there wasn't anything..." << endl;
			}
		}
	}
	else
	{
		ret = false;
	}

	return ret;
}
