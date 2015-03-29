#include "roamingmonster.h"
#include "environment.h"
#include "fight.h"
#include "Interaction/console.h"
#include <iostream>

namespace ah {

RoamingMonster::~RoamingMonster() {}

bool RoamingMonster::is_friendly() const { return false; }

void RoamingMonster::update() {
    //if(just_moved) {
        //just_moved = false;
        //return;
    //}
    //bool found_player = false;
    //for(std::shared_ptr<Actor> a : current_env->actors) {
        //if (a->is_player()) {
            //Console::instance().writeLine("A roaming monster appears. It attacks!");
            //found_player = true;
            //fight(shared_from_this(), a);
        //}
    //}
    //if(!found_player) {
        ////current_env->move_to_random_neighbour(shared_from_this());
        //just_moved = true;
    //}
}

} // end namespace ah
