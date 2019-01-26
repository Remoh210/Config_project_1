#ifndef BEHAVIOUR_H
#define BEHAVIOUR_H

class Behaviour {
public:
	virtual ~Behaviour(void) { }
	virtual void update(float dt) = 0;

protected:
	Behaviour(void) { }
};

#endif
