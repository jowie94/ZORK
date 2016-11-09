#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <vector>

typedef std::vector<std::string> arglist;

#include <list>

enum ENTITY_TYPE
{
	ENTITY,
	ROOM
};

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* parent);
	virtual ~Entity();

	virtual void Tick();

	ENTITY_TYPE Type;

private:

	std::string name;
	std::string description;

	Entity* parent;
	std::list<Entity*> sub_entities;
};

#endif // _ENTITY_H_
