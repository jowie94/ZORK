#ifndef _ROOM_H_
#define _ROOM_H_

#include "entity.h"
#include "exit.h"

class Room : public Entity
{
public:
	Room(const char *name, const char *description);
	~Room();

	void Look();

	Exit* GetExitAt(const string& direction);
};

#endif // _ROOM_H_
