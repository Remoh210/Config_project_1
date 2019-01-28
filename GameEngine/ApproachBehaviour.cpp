#include "ApproachBehaviour.h"
#include "shoot.h"

#include <iostream>
bool first = true;
ApproachBehaviour::ApproachBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce)
	: mAgent(agent)
	, mTarget(target)
	, mMaxSpeed(maxSpeed)
	, mMaxForce(maxForce)
{
	mRadius = 50.0f;
	mTimeElapsedSinceLastShot = 0.0f;
	mTimeToWait = 1.0f;
	mStart = true;
}

ApproachBehaviour::~ApproachBehaviour(void)
{
}

void ApproachBehaviour::update(float dt)
{

	if (mAgent == 0 || mTarget == 0) return;
	float distance = glm::distance(mTarget->position, mAgent->position);
	if (distance < mRadius)
	{

		//mAgent->velocity = glm::vec3(0.0f);
		if (distance < mRadius / 2) {
			if (mStart) {
				mTimeElapsedSinceLastShot = 0.0f;
				mStart = false;
			}
			//mAgent->velocity = glm::vec3(0.0f);
			//mAgent->accel = glm::vec3(0.0f);
			mTimeElapsedSinceLastShot += (float)dt;
			if (mTimeElapsedSinceLastShot > mTimeToWait)
			{
				shoot(mAgent, mTarget, 80.0f, glm::vec3(0.0f, 0.0f, -5.0f));
				mStart = true;
			}
		}
	}
		
	else 
	{
		glm::vec3 desired = mTarget->position - mAgent->position;
		//normalize it and scale by mMaxSpeed
		desired = glm::normalize(desired) * mMaxSpeed;
		float d = glm::length(desired);
		if (d < mRadius) {
			float m = map(d, 0, mRadius, 0, mMaxSpeed);
			desired = glm::normalize(desired) * m;
		}
		else {
			desired = glm::normalize(desired) * mMaxSpeed;
		}

		glm::vec3 steering = desired - mAgent->velocity;

		if (glm::length(steering) > mMaxForce) {
			steering = glm::normalize(steering) * mMaxForce;
		}
		//steering = glm::normalize(desired) * mMaxForce;
		mAgent->accel = steering * 2.0f;

		//glm::mat4 rot = glm::inverse(glm::lookAt(mAgent->position, mTarget->position, glm::vec3(0.0f, 1.0f, 0.0f)));
		//mAgent->m_meshQOrientation;

		//glm::mat4 rot = glm::inverse(glm::lookAt(mAgent->position, mAgent->position + mAgent->velocity, glm::vec3(0.0f, 1.0f, 0.0f)));
		//mAgent->m_meshQOrientation = glm::quat(rot);

	}
	glm::mat4 rot = glm::inverse(glm::lookAt(mAgent->position, mTarget->position, glm::vec3(0.0f, 1.0f, 0.0f)));
	mAgent->m_meshQOrientation = glm::quat(rot);
	//glm::vec3 desired = mTarget->position - mAgent->position;
	////normalize it and scale by mMaxSpeed
	//desired = glm::normalize(desired) * mMaxSpeed;
	//float d = glm::length(desired);
	//float dist = glm::distance(mTarget->position, mAgent->position);
	//if (dist < mRadius + 50.0f) {
	//	float m = map(dist, mRadius, mRadius + 50, 0, mMaxSpeed);
	//	if (m < 0.0f) { m = 0.0f; }
	//	desired = glm::normalize(desired) * m;
	//}
	//else {
	//	desired = glm::normalize(desired) * mMaxSpeed;
	//}

	//if (dist < mRadius) 
	//{ 
	//	mTarget->velocity = glm::vec3(0.0f); 
	//	mTarget->accel = glm::vec3(0.0f);
	//}
	//else 
	//{
	//	glm::vec3 steering = desired - mAgent->velocity;

	//	if (glm::length(steering) > mMaxForce) {
	//		steering = glm::normalize(steering) * mMaxForce;
	//	}
	//	//steering = glm::normalize(desired) * mMaxForce;
	//	mAgent->accel = steering;

	//	glm::mat4 rot = glm::inverse(glm::lookAt(mAgent->position, mAgent->position + mAgent->velocity, glm::vec3(0.0f, 1.0f, 0.0f)));
	//	mAgent->m_meshQOrientation = glm::quat(rot);
	//}

}

