#ifndef ACTOR_H
#define ACTOR_H

#include <vector>

#include "item.h"
#include "weapon.h"
#include "entity.h"
#include "inventory.h"
#include "abilities.h"

namespace ah {

class Environment; // forward declaration

class Actor : public Entity, public std::enable_shared_from_this<Actor> {
public:
    Actor() : Actor("DefaultName", "DefaultDescription") {} 
    Actor(std::string name, std::string description, bool is_player=false, int health=10) :
        Entity(name, description), health_(health), is_player_(is_player) {}
        //weapon_("Fists", "'I call em Law & Order'", 0, 1), health_(20), name_(name) {}

    virtual ~Actor() = default;

    // Inherited from Entity
    virtual std::string type() const { return type_; }
    virtual void update();

    virtual void attack();
    virtual void defend(int);
    virtual int doAttack(); // fight!

    virtual void talk() const;
    virtual void talk(std::shared_ptr<Actor>);

    virtual Item drop_item(const Item& i); // parameters?
    std::vector<Item> drop_all_items();
    virtual bool take_item(const Item& i); // parameters?
    virtual bool equip_weapon(Weapon w);
    bool has_item(ability_t) const;

    virtual bool is_friendly() const;

    int health() const { return health_; }
    bool alive() const { return health_ > 0; }

    void use_ability(ability_t);
    bool is_player() const { return is_player_; }

    //virtual void set_current_env(std::shared_ptr<Environment>);

    Inventory& inventory();
    //std::shared_ptr<Environment> current_env;

    //friend bool operator==(Actor &a, Actor &b);
    //friend bool operator!=(Actor &a, Actor &b);

protected:
    bool is_player_;
    int strength();
    std::string type_ = "Actor"; 
    Inventory inventory_;
    int health_;

private:

};

//bool operator==(Actor &a, Actor &b) {
    //return a.name() == b.name();
//}

//bool operator!=(Actor &a, Actor &b) {
    //return a.name() != b.name();
//}

} // end namespace

#endif
