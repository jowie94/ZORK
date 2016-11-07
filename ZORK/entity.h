#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <list>

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* parent);
	virtual ~Entity();

	virtual void Tick();

private:

	std::string name;
	std::string description;

	Entity* parent;
	std::list<Entity*> sub_entities;
};

#endif // _ENTITY_H_
