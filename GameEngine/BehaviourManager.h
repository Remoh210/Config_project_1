#ifndef BEHAVIOUR_MANAGER_H
#define BEHAVIOUR_MANAGER_H

#include <map>
#include "Entity.h"
#include "Behaviour.h"

class BehaviourManager {
public:
	BehaviourManager(void);
	~BehaviourManager(void);

	void SetBehaviour(Entity* agent, Behaviour* behaviour);
	void RemoveAgent(Entity* agent);

	void update(float dt);

private:
	std::map<Entity*, Behaviour*> mBehaviourMap;
};

typedef std::map<Entity*, Behaviour*>::iterator behaviour_iterator;


#endif
