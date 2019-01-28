#ifndef APPROACH_BEHAVIOUR_H
#define APPROACH_BEHAVIOUR_H

#include "Behaviour.h"
#include "cMeshObject.h"

class ApproachBehaviour : public Behaviour {
public:
	ApproachBehaviour(cMeshObject* agent, cMeshObject* target, float maxSpeed, float maxForce);
	virtual ~ApproachBehaviour(void);

	virtual void update(float dt);

private:
	cMeshObject* mTarget;
	cMeshObject* mAgent;
	float mMaxSpeed;
	float mMaxForce; //steering speed
	float mRadius;
	float mTimeElapsedSinceLastShot;
	float mTimeToWait;
	bool mStart;
};

#endif
