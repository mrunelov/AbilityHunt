#ifndef ITEM_H
#define ITEM_H

#include "entity.h"
#include "abilities.h"
#include <string>

namespace ah {

class Item : public Entity {
public:
    Item() : id_(UNKNOWN), Entity("<>","") {}

    virtual ~Item() = default;

    Item(ability_t id, std::string name, std::string description, int weight) :
        Entity(name, description), type_("Item"), id_(id), weight_(weight) {}

    Item(std::string type, ability_t id, std::string name, std::string description, int weight) :
        Entity(name, description), type_(type), id_(id), weight_(weight) {}
    

    //copy constructor and asgn
    Item(const Item& other)
        : Entity(other.name_, other.short_descr_, other.long_descr_),
          id_(other.id_),
          type_(other.type_),
          weight_(other.weight_) 
    {
        //std::cout << ("=> Copy Constructor") << std::endl;
    }

    Item& operator=(const Item& other)
    {
        Entity::operator=(other);
        id_ = other.id_;
        type_ = other.type_;
        weight_ = other.weight_;
        
        //std::cout << ("=> Copy Assignment") << std::endl;
        return *this;
    }

    //move constructor and asgn
    Item(const Item&& other)
        : Entity(other.name_, other.short_descr_, other.long_descr_),
          id_(other.id_),
          type_(other.type_),
          weight_(other.weight_) 
    {
        //std::cout << ("=> Move Constructor") << std::endl;
    }
    
    Item& operator=(const Item&& other)
    {
        Entity::operator=(other);
        id_ = other.id_;
        type_ = other.type_;
        weight_ = other.weight_;
        //std::cout << ("=> Move Assignment") << std::endl;
        return *this;   
    }


    ability_t id() const { return id_; }
    virtual int weight() const { return weight_; };
    virtual std::string type() const { return type_; }
    
    virtual void update() {}

protected:
    ability_t id_;
    std::string type_;
    int weight_;
private:

};

} // end namespace

#endif
