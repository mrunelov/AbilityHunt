#include "boss.h"
#include "environment.h"
#include "fight.h"
#include "abilities.h"
#include "Interaction/console.h"
#include "Interaction/narrator.h"
#include <iostream>

namespace ah {

Boss::~Boss() {}

void Boss::update() {
    // TODO?
}

bool Boss::is_friendly() const { return false; }

void Boss::talk(std::shared_ptr<Actor> a) {
    //std::string question = "Hello stranger, do you like my apartment?";
    //if (a->is_player()) {
        //if(!a->has_item(SARCASM)) {
            //Narrator::dialogue(name(), question, {"No, it's very dirty and moist."});
            //Narrator::dialogue(name(), "You're right, it is. I like your honesty. ", {"I should go."});
        //}
        //else {
            //Narrator::dialogue(name(), question, {"Yeah reaaaally nice. I'd loooove to live here."});
            //Narrator::dialogue(name(), "Is that sarcasm?! You sir, have just won a....Fight the DEATH! ", {"Bring it on!"});

        //fight(shared_from_this(), a);
        //}
    //}
}

} // end namespace ah
