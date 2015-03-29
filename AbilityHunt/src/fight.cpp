#ifndef FIGHT_H
#define FIGHT_H

#include "fight.h"
#include <iostream>

#include "Interaction/console.h"
#include "actor.h"

namespace ah {

std::vector<Item> handle_aftermath(std::shared_ptr<Actor> winner, std::shared_ptr<Actor> loser);

std::vector<Item> fight(std::shared_ptr<Actor> a, std::shared_ptr<Actor> b) 
{

    Console::instance().indent(2);

    Console::instance().writeLineStop("---------------------------------");
    Console::instance() << a->name() << " VS " << b->name() << ".. FIGHT!";
    Console::instance().enterToContinue();
    Console::instance().nextLine();
    while(a->alive() && b->alive()) {
        int a_attack = a->doAttack();
        b->defend(a_attack);
        if(b->alive()) {
            int b_attack = b->doAttack();
            a->defend(b_attack);
        }
    }

    std::string winner;
    int remaining_health = -1;
    // TODO: rewrite to avoid duplicate code...
    if(a->alive()) {
        return handle_aftermath(a,b);
    }
    else {
        return handle_aftermath(b,a);
    }

    //Console::instance().enterToContinue();
    //Console::instance().dedent(2);
}

std::vector<Item> handle_aftermath(std::shared_ptr<Actor> winner, std::shared_ptr<Actor> loser) {


    Console::instance() << winner->name() << " won the fight! Remaining health: " << winner->health();
    Console::instance().nextLine();

    if(loser->is_player()) {
        Console::instance().writeLine("You lost the fight");
    }
    
    return loser->drop_all_items();
    
}

} // end namespace

#endif
