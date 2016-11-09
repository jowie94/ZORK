#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include <list>
#include <string>

typedef std::vector<std::string> arglist;

using namespace std;

enum ENTITY_TYPE
{
	ENTITY,
	ROOM,
	ITEM,
	CREATURE,
	PLAYER
};

class Entity
{
public:
	Entity(const char* name, const char* description, Entity* parent);
	virtual ~Entity();

	virtual void Look() const;
	virtual void Tick();

	void ChangeParent(Entity* newEntity);
	
	Entity* Find(const string &name) const;
	Entity* Find(const string &name, const ENTITY_TYPE type) const;

	ENTITY_TYPE Type;
	string Name;
	string Description;

protected:
	Entity* parent;
	list<Entity*> sub_entities;
};

#endif // _ENTITY_H_
