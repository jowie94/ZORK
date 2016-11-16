#pragma once
#include "creature.h"

class AI
{
public:
	AI(Creature* creature) : creature(creature) {}
	virtual ~AI() {}

	virtual void Tick() = 0;
	virtual void OnAttacked(Creature* from) = 0;
	virtual void OnDie() = 0;
	
	Creature* creature;
};

