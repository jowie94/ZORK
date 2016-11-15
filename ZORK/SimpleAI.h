#pragma once
#include "ai.h"

class SimpleAI :
	public AI
{
public:
	SimpleAI(Creature* creature);
	~SimpleAI();

	void Tick();
	void OnDie();
};

