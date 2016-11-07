#ifndef _ROOM_H_
#define _ROOM_H_

#include "entity.h"
class Room : public Entity
{
public:
	Room(const char *name, const char *description);
	~Room();
};

#endif // _ROOM_H_
