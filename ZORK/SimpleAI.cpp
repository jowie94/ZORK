#include "SimpleAI.h"
#include <iostream>


SimpleAI::SimpleAI(Creature* creature) : AI(creature)
{
}


SimpleAI::~SimpleAI()
{
}

void SimpleAI::Tick()
{
	if (creature->IsPlayerInRoom())
	{
		creature->AttackTarget();
	}
}

void SimpleAI::OnAttacked(Creature* from)
{
	creature->Target = from;
}

void SimpleAI::OnDie()
{
	cout << creature->Name << " died." << endl << endl;
}
