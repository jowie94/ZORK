#include "entity.h"
#include "utils.h"
#include <iostream>

Entity::Entity(const char* name, const char* description, Entity* parent = nullptr) : Name(name), Description(description), parent(parent)
{
	if (parent != nullptr)
	{
		parent->sub_entities.push_back(this);
	}

	Type = ENTITY;
}


Entity::~Entity()
{}

void Entity::Look() const
{
	cout << Name << endl << Description << endl;
}

void Entity::Tick()
{}

void Entity::ChangeParent(Entity* newEntity)
{
	if (parent != nullptr)
	{
		parent->sub_entities.remove(this);
	}

	parent = newEntity;

	if (parent != nullptr)
	{
		parent->sub_entities.push_back(this);
	}
}

Entity* Entity::Find(const string& name, const ENTITY_TYPE type) const
{
	for (Entity* entity : sub_entities)
	{
		if (str_equals(entity->Name, name) && entity->Type == type)
		{
			return entity;
		}
	}

	return nullptr;
}

Entity* Entity::Find(const string &name) const
{
	for (Entity* entity : sub_entities)
	{
		if (str_equals(entity->Name, name))
		{
			return entity;
		}
	}

	return nullptr;
}
