#include "entity.h"
#include "utils.h"
#include <iostream>

Entity::Entity(const char* name, const char* description, Entity* parent = nullptr) : Name(name), Description(description), parent(parent)
{
	if (parent != nullptr)
	{
		parent->SubEntities.push_back(this);
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
		parent->SubEntities.remove(this);
	}

	parent = newEntity;

	if (parent != nullptr)
	{
		parent->SubEntities.push_back(this);
	}
}

Entity* Entity::Find(const string& name, const ENTITY_TYPE type) const
{
	for (Entity* entity : SubEntities)
	{
		if (str_equals(entity->Name, name) && entity->Type == type)
		{
			return entity;
		}
	}

	return nullptr;
}

void Entity::FindAll(const ENTITY_TYPE type, list<Entity*>& entities) const
{
	for (Entity* entity : SubEntities)
	{
		if (entity->Type == type)
		{
			entities.push_back(entity);
		}
	}
}

Entity* Entity::Find(const string &name) const
{
	for (Entity* entity : SubEntities)
	{
		if (str_equals(entity->Name, name))
		{
			return entity;
		}
	}

	return nullptr;
}
