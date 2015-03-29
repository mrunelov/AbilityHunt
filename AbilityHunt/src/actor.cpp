#include "actor.h"

#include <cstdlib>
#include <cmath>
#include <iostream>

#include "environment.h"
#include "Interaction/console.h"

using std::string;

namespace ah {

int Actor::strength() {
    return inventory_.weapon_strength();    
}

// If we attack an Actor, they fight.
int Actor::doAttack() {
    int critical = (rand() % 2); // randomized 0-1
    int attack_value = strength() + ceil(0.5*critical*strength());

    Console::instance() << name() << " attacks for " << attack_value << " damage.  ";
    return attack_value;
}

void Actor::defend(int attack_value) {
    float mitigation = strength()*0.2;
    //std::cout << "being attacked for " << attack_value << " with mitigation " << mitigation << std::endl;
    attack_value -= mitigation;
    Console::instance() << name()<< " took " << attack_value << " damage.";
    Console::instance().nextLine();
    health_ -= attack_value;
    if (health_ <= 0) {
        Console::instance().write(name());
        Console::instance().writeLine(" died.");
    }
}

//void Actor::set_current_env(std::shared_ptr<Environment> env) {
    //current_env = env;
//}

void Actor::update() {
}

void Actor::attack() {}

void Actor::talk() const {}

void Actor::talk(std::shared_ptr<Actor> a) {}

Item Actor::drop_item(const Item& i) {
    if(inventory_.remove_item(i)) {
        Console::instance().write(name());
        Console::instance().writeLine(" dropped an item.");
        return i;
    }
}

std::vector<Item> Actor::drop_all_items() {
    std::vector<Item> dropped_items = inventory_.items_;
    inventory_.items_.clear();

    std::vector<Item> result;
    for(Item i : dropped_items) {
        if(i.id() != UNKNOWN) {
            result.push_back(i);
        }
    }

    return result;
}

bool Actor::take_item(const Item& i) {
    return inventory_.add_item(i);
}

bool Actor::has_item(ability_t key) const {
    return inventory_.has_item(key);
}

bool Actor::equip_weapon(Weapon w) {
    return inventory_.equip_weapon(w);
}

bool Actor::is_friendly() const{
    return true;
}

Inventory& Actor::inventory()
{
    return inventory_;
}


} // end namespace
