#ifndef FIGHT_H
#define FIGHT_H

#include "actor.h"
#include "item.h"
#include <vector>

namespace ah {

std::vector<Item> handle_aftermath(std::shared_ptr<Actor>, std::shared_ptr<Actor>);
std::vector<Item> fight(std::shared_ptr<Actor>, std::shared_ptr<Actor>);

} // end namespace ah

#endif
