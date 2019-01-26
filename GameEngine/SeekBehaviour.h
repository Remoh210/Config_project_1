#ifndef SEEK_BEHAVIOUR_H
#define SEEK_BEHAVIOUR_H

#include "Behaviour.h"
#include "Entity.h"

class SeekBehaviour : public Behaviour {
public:
	SeekBehaviour(Entity* agent, Entity* target);
	virtual ~SeekBehaviour(void);

	virtual void update(float dt);

private:
	Entity* mTarget;
	Entity* mAgent;
};

#endif
