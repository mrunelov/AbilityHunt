#include "inventory.h"

#include <utility>
#include <iostream>

#include "weapon.h"
#include "Interaction/console.h"

namespace ah {

Inventory::~Inventory() {}

Inventory::Inventory() : capacity_(100), total_weight_(0) {
    items_.resize(NUM_ABILITIES);
}

int Inventory::weapon_strength() const {
    if (weapon_.id() == UNKNOWN)
        return 0;
    return weapon_.strength();
    //if(weapon_ == nullptr) // TODO: rework so that it's always initialized?
        //return 0;
    //return weapon_->strength();
    
}

bool Inventory::add_item(const Item& i) {
    //std::cout << "type: " << i.type() << std::endl;
    //if (i.type() == "Weapon") // TODO: rewrite!
        //return add_weapon(dynamic_cast<Weapon&>(i));
    if(total_weight() + i.weight() > capacity())
        return false;
    
    items_[i.id()] = i; // TODO: just overwrite? or warn the player? for e.g. WEAPON
    total_weight_ += i.weight();
    //items_.insert(std::make_pair(i.id(), i));
    return true;
}

/*
    Replace your weapon
 */
bool Inventory::equip_weapon(Weapon w) {
    if(total_weight() + w.weight() > capacity()) {
        std::cout << "You don't have enough inventory capacity to equip this weapon" << std::endl;
        return false;
    }
    weapon_ = w;
    total_weight_ += w.weight();
    return true;
}

bool Inventory::remove_item(Item i) {
    if(!has_item(i.id()))
        return false;
    items_[i.id()] = Item();
    return true;
}

bool Inventory::has_item(ability_t key) const {
    if (items_[key].id() == UNKNOWN)
        return false;
    return true;
    //std::unordered_map<ability_t,Item>::const_iterator got = items_.find(key);
    //if (got == items_.end())
        //return false;
    //return true;
}

void Inventory::describe() {
  Console::instance().writeLine("-----------", Console::SPEED_INSTANT);
  Console::instance().writeLine("|INVENTORY|", Console::SPEED_INSTANT);
  Console::instance().writeLine("-----------", Console::SPEED_INSTANT);
  //Console::instance().sleep(200);

  for(int i = 0; i < items_.size(); ++i) {
    Console::instance().write("[", Console::SPEED_INSTANT);
    Console::instance().write(i+1, Console::SPEED_INSTANT);
    Console::instance().write("] " , Console::SPEED_INSTANT);
    //Console::instance().sleep(50);
    Console::instance().write(items_[i].name(), Console::SPEED_INSTANT);
    Console::instance().write(" -- ", Console::SPEED_DEFAULT);
    Console::instance().writeLine(items_[i].short_description(), Console::SPEED_INSTANT);
  }
  Console::instance() << "Weapon: " << weapon_.name() << " -- " << weapon_.short_description() << ". Strength: " << weapon_.strength();
  Console::instance().nextLine();
}   


} // end namespace
