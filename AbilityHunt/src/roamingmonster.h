#ifndef ROAMINGMONSTER_H 
#define ROAMINGMONSTER_H

#include "actor.h"

namespace ah {

class RoamingMonster : public Actor {
public:
    bool just_moved = false;
    virtual ~RoamingMonster();
    RoamingMonster() : Actor("DefaultName", "DefaultDescription") {}
    
    RoamingMonster(std::string name, std::string description) :
        Actor(name, description) {}

    RoamingMonster(std::string name, std::string description, int health) :
        Actor(name, description, false, health) {}

    virtual bool is_friendly() const;

    virtual void update();

protected:
    std::string type_ = "RoamingMonster";

private:

};

} // end namespace ah


#endif
