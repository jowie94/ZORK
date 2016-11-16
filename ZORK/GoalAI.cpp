#include "GoalAI.h"
#include <iostream>

GoalAI::GoalAI(Creature* creature, vector<bool>::reference goal, const char* death_message)
: AI(creature), goal(goal), death_message(death_message)
{}

GoalAI::~GoalAI()
{
}

void GoalAI::Tick()
{
	if (creature->IsPlayerInRoom())
	{
		creature->AttackTarget();
	}
}

void GoalAI::OnAttacked(Creature* from)
{
	creature->Target = from;
}

void GoalAI::OnDie()
{
	goal = true;
	cout << creature->Name << " died." << endl << death_message << endl;
}
