#include "FeederAI.h"
#include <iostream>

FeederAI::FeederAI(Creature* creature): AI(creature)
{
}

FeederAI::~FeederAI()
{
}

void FeederAI::Tick()
{
	if (creature->IsPlayerInRoom() && creature->Target)
	{
		creature->AttackTarget();
	}
}

void FeederAI::OnAttacked(Creature* from)
{
	creature->Target = from;
}

void FeederAI::OnDie()
{
	cout << creature->Name << " died." << endl;
}
