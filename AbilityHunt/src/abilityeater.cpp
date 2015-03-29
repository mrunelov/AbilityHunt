#include "abilityeater.h"
#include "environment.h"
#include "fight.h"
#include "Interaction/console.h"
#include <iostream>

namespace ah 
{

AbilityEater::AbilityEater()
	: AbilityEater("(name)", "(description)")
{}

AbilityEater::AbilityEater(std::string name, std::string description) 
	: Actor(name, description, false)
{}

AbilityEater::AbilityEater(std::string name, std::string description, int health) 
	: Actor(name, description, false, health)
{}

AbilityEater::~AbilityEater() 
{}

bool AbilityEater::is_friendly() const { return false; }

void AbilityEater::update() {
    //for(std::shared_ptr<Actor> a : (*current_env).actors) {
        //if (a->name() == name()) continue; // TODO: replace with id check
        //if (a->is_player()) {
            //Console::instance().writeLine("The scary monster sees you and attacks!");
            //fight(shared_from_this(), a);
        //}
    //}
    //std::cout << "AbilityEater is in room " << (*current_env).name() << std::endl;
}

} // end namespace ah
