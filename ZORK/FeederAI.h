#pragma once
#include "ai.h"
class FeederAI :
	public AI
{
public:
	FeederAI(Creature* creature);
	~FeederAI();

	void Tick();
	void OnAttacked(Creature* from);
	void OnDie();
};

