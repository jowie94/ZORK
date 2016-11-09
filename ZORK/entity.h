#ifndef _ENTITY_H_
#define _ENTITY_H_
#include <vector>

typedef std::vector<std::string> arglist;

#include <list>

enum ENTITY_TYPE
{
	ENTITY,
	ROOM,
	CREATURE
};

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* parent);
	virtual ~Entity();

	virtual void Look() const;
	virtual void Tick();

	ENTITY_TYPE Type;

protected:
	std::string name;
	std::string description;
	Entity* parent;
	std::list<Entity*> sub_entities;
};

#endif // _ENTITY_H_
