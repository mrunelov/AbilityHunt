/* 
	Defines the entry point for the console application.
*/

#include <iostream>

#include "Gameplay.h"
#include "Interaction/console.h"
#include <signal.h>

int main()
{
	ah::Gameplay gameplay;
	gameplay.initialize();
	return gameplay.run();
    //raise(SIGINT);

}
