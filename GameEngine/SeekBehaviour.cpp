#include "SeekBehaviour.h"

SeekBehaviour::SeekBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce)
	: mAgent(agent)
	, mTarget(target)
	, mMaxSpeed(maxSpeed)
	, mMaxForce(maxForce)
{

}

SeekBehaviour::~SeekBehaviour(void)
{
}

void SeekBehaviour::update(float dt)
{
	if (mAgent == 0 || mTarget == 0) return;
	//desired vector
	glm::vec3 desired = mTarget->position - mAgent->position;
	//normalize it and scale by mMaxSpeed
	desired = glm::normalize(desired) * mMaxSpeed;
	glm::vec3 steering = desired - mAgent->velocity;

	mAgent->accel += steering;

	// Update agent's orientation...
}