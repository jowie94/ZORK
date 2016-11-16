#pragma once
#include "ai.h"
class GoalAI :
	public AI
{
public:

	GoalAI(Creature* creature, vector<bool>::reference goal, const char* death_message);
	~GoalAI();

	void Tick();
	void OnAttacked(Creature* from);
	void OnDie();

private:
	vector<bool>::reference goal;
	const char* death_message;
};

