#include "ZombieAI.h"
#include "utils.h"
#include <iostream>

ZombieAI::ZombieAI(Creature* creature): AI(creature)
{}

ZombieAI::~ZombieAI()
{
}

void ZombieAI::Tick()
{
	if (creature->IsPlayerInRoom())
	{
		int attack = randomize(0, 10);
		if (attack >= 5)
		{
			creature->AttackTarget();
		}
		else
		{
			cout << creature->Name << " missed!" << endl << endl;
		}
	}
}

void ZombieAI::OnAttacked(Creature* from)
{
	creature->Target = from;
}

void ZombieAI::OnDie()
{
	cout << creature->Name << " died." << endl << endl;
}
