#ifndef BOSS_H 
#define BOSS_H 

#include "actor.h"

namespace ah {

class Boss : public Actor {
public:
    //bool player_has_talked_to = false;
    virtual ~Boss();
    Boss() : Actor("DefaultName", "DefaultDescription") {}
    
    Boss(std::string name, std::string description) :
        Actor(name, description) {}

    Boss(std::string name, std::string description, int health) :
        Actor(name, description, false, health) {}

    virtual bool is_friendly() const;
    virtual void update();
    void talk(std::shared_ptr<Actor>);

protected:
    std::string type_ = "Boss";

private:

};

} // end namespace ah


#endif
