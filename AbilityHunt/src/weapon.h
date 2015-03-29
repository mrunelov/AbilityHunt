#ifndef WEAPON_H
#define WEAPON_H
#include "item.h"
#include <string>

namespace ah {

class Weapon : public Item {
public:
    Weapon() : Weapon("Fists", "The worst 'weapon' in the game", 0, 1) {}

    Weapon(std::string name, std::string description, int weight, int strength) : 
        Item("Weapon", WEAPON, name, description, weight), strength_(strength) {} 

    virtual int strength() const { return strength_; }

protected:
    int strength_;
    
private:
};

} // end namespace

#endif

