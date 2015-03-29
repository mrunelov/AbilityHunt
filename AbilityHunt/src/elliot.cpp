#include "elliot.h"

#include <iostream>
#include <sstream>

#include "environment.h"
#include "fight.h"
#include "Interaction/console.h"
#include "Interaction/narrator.h"

namespace ah {

Elliot::~Elliot() {}

std::string Elliot::short_description() const 
{
	std::stringstream ss;
	ss << name() << " - " << short_descr_;

	return ss.str();
}

void Elliot::talk(std::shared_ptr<Actor> a) 
{
    Narrator::dialogue(name(), "Oh, ehoeuh! Oh, it's you. You startled me!", {"what are you doing?"});
    Narrator::quote(name(), "I'm looking for a shovel. I need it to get to where The Item is! I know it's underground, and close to here too!");
   	Console::instance().enterToContinue();
    Narrator::dialogue(name(), "I even know the combination see! It's >1234<... oh I shouldn't have told you that", {"I should go."});
}

} // end namespace ah
