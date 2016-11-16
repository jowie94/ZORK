#pragma once
#include "ai.h"
class ZombieAI :
	public AI
{
public:
	ZombieAI(Creature* creature);
	~ZombieAI();

	void Tick();
	void OnAttacked(Creature* from);
	void OnDie();
};

