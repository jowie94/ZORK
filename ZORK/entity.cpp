#include "entity.h"



Entity::Entity(const char* name, const char* description, Entity* parent = nullptr) : name(name), description(description), parent(parent)
{
	if (parent != nullptr)
	{
		parent->sub_entities.push_back(this);
	}
}


Entity::~Entity()
{}

void Entity::Tick()
{}
