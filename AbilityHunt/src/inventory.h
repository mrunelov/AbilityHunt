#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include <iostream>

#include "item.h"
#include "weapon.h"
#include "abilities.h"

namespace ah {

class Inventory {
public:

    Inventory();

    ~Inventory();

    int capacity() { return capacity_; }
    int total_weight() { return total_weight_; }
    bool add_item(const Item& i);
    bool equip_weapon(Weapon w);
    bool remove_item(Item i);
    bool has_item(ability_t key) const;
    int weapon_strength() const;
    std::vector<Item> items_;

    virtual void describe();

protected:

private:
    int capacity_;
    int total_weight_;
    Weapon weapon_;

};

} // end namespace

#endif

