/*
	Class that describes the whole gameplay and runs the gameplay loop
*/

#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "World.h"
#include "Interaction/console.h"

namespace ah
{

class Gameplay
{
public:
    World world_;

	Gameplay();
	~Gameplay();


	void initialize();
	int run();

protected:
private:

};

} // namespace ah

#endif // GAMEPLAY_H

