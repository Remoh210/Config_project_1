#include "SeekBehaviour.h"

SeekBehaviour::SeekBehaviour(Entity* agent, Entity* target)
	: mAgent(agent)
	, mTarget(target)
{

}

SeekBehaviour::~SeekBehaviour(void)
{
}

void SeekBehaviour::update(float dt)
{
	if (mAgent == 0 || mTarget == 0) return;

	// Implement the seek code here...

	// Update agent's orientation...
}