/*
    Elliot is a character in Ability Hunt and is looking for
    <the winning item>. 

    He helps The Player in the beginning and gives him/her a pair of boots,
    then goes on to a waterfall in the forest to look for a hidden passage
    to an underground maze.

    When talked to, he tells the player about <the winning item> and accidently
    also mentiones exactly how to get to the boss and how to beat him.

*/
#ifndef AH_ELLIOT_H 
#define AH_ELLIOT_H 

#include "actor.h"

namespace ah {

class Elliot : public Actor {
public:
    //bool player_has_talked_to = false;
    Elliot() : Actor("Elliot", "A traveller looking for the way to win The Game") {}
    virtual ~Elliot();

    std::string short_description() const override;
    void talk(std::shared_ptr<Actor>) override;

protected:
private:

};

} // end namespace ah


#endif //AH_ELLIOT_H
