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
		cout << "There's no exit in that direction (" << args[0] << ")." << endl;
	}
	else
	{
		if (exit->Locked)
		{
			cout << "This exit is locked!" << endl;
		}
		else if (exit->Closed)
		{
			cout << "This exit is closed!." << endl;
		}
		else
		{
			cout << "You go through the " << args[0] << " exit..." << endl;
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
			cout << "There's no exit in that direction (" << args[1] << ")." << endl;
		}
		else if (exit->Locked)
		{
			cout << "That exit is locked with a key!" << endl;
		}
		else if (!exit->Closed)
		{
			cout << "That exit is already opened!" << endl;
		}
		else
		{
			exit->Closed = false;
			cout << "You opened the " << args[1] << " exit!" << endl;
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
			cout << "There's no exit in that direction (" << args[1] << ")." << endl;
		}
		else if (exit->Closed)
		{
			cout << "That exit is already closed!" << endl;
		}
		else
		{
			exit->Closed = true;
			cout << "You closed the " << args[1] << " exit!" << endl;
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

void Player::UnLock(const arglist& args)
{
}

void Player::Lock(const arglist& args)
{
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
