#ifndef ABILITYEATER_H
#define ABILITYEATER_H

#include "actor.h"

namespace ah {

class AbilityEater : public Actor {
public:

    AbilityEater();
    AbilityEater(std::string name, std::string description);
    AbilityEater(std::string name, std::string description, int health);
    virtual ~AbilityEater();

    virtual bool is_friendly() const;
    virtual void update();

protected:
    std::string type_ = "AbilityEater";

private:

};

} // end namespace ah


#endif
