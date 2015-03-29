#include "environment.h"
#include "Interaction/console.h"
#include "fight.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>



namespace ah
{
Environment::Environment() :
    paths(),
	actors(),
    actors_that_left()
{
}

Environment::Environment(const std::string& name, const std::string& shortdescr, const std::string& longdescr)
  : Entity(name, shortdescr, longdescr),
    actors(), 
    items(),
    paths()
{
}

void Environment::update()
{

    for(auto a : actors_that_left) {
        actors.erase(std::remove(actors.begin(),actors.end(),a), actors.end());
    }
    actors_that_left.clear();

    for(std::shared_ptr<Actor>& a : actors) {
        if(a->is_player()) {
            for(std::shared_ptr<Actor>& aa : actors) {
                if(!aa->is_player() && !aa->is_friendly() && aa->alive()) {
                    std::vector<Item> dropped_items = fight(a,aa);
                    if(!dropped_items.empty()) {
                        Console::instance().write("dropped ");
                        Console::instance().write(dropped_items.size());
                        Console::instance().writeLine(" items.");
                    }
                    for(Item& i : dropped_items)
                        items.push_back(i);
                }
            }
        }
        if(a->alive())
            a->update();
    }

    
}

void Environment::addPath(Path path) {
    paths.push_back(path);
}

void Environment::enter(std::shared_ptr<Actor> actor) {
    actors.push_back(actor);
    //actor->set_current_env(shared_from_this());
    if (actor->is_player())
    {
        //Console::instance().writeLine(actor->name());
        brief(); //print short description of new environment
    }
}


void Environment::leave(std::shared_ptr<Actor>& actor) {
    actors_that_left.push_back(actor);
}

void Environment::add_item(Item item) {
    items.push_back(item);
}

void Environment::brief() 
{
    //give a short description of the environment
    Console::instance().writeLine(short_descr_);

    //also mention specific, important things such as monsters
    std::vector<std::string> noticableActors;
    for(const std::shared_ptr<Actor>& actor : actors)
        if(actor->alive() && actor->notable())
            noticableActors.push_back(actor->short_description());
    Narrator::describeNoticeActors(noticableActors);
    if(!noticableActors.empty()) Console::instance().enterToContinue();

}

void Environment::describe() 
{
    Console::instance().writeLine(long_descr_);

    //describe paths
    if(!paths.empty()) {
        for(Path& path : paths) {
            Console::instance().writeLine(path.short_description());
        }
    }

    std::vector<std::string> actordescrs;
    for(auto actor : actors)
    {
        if(actor->alive() && !actor->is_player())
        {
            actordescrs.push_back(actor->short_description());
        }
    }

    if(!actordescrs.empty())
    {
        Narrator::describeNoticeActors(actordescrs);
    }
    else {
        Console::instance().writeLine("You're alone.");
    }
    
    /* describe items*/
    if(!items.empty()) {
        Console::instance().writeLine("You see these items:");
        for(const Item& i : items) {
            Console::instance().writeLine(i.name());
        }
    }

    Console::instance().nextLine();
}

//void Environment::move_to_random_neighbour(std::shared_ptr<Actor> a) {
    //if (paths.size() == 0) return;
    //int k = std::rand() % (paths.size()+1); // biased but w/e
    //if (k == paths.size()) return; // don't move!
    //else {
        //paths[k]->to_;
        //std::shared_ptr<Environment> random_neighbour = paths[k]->to_; 
        
        //if(paths.size() == 1 && random_neighbour->is_friendly()) return;

        //while(random_neighbour->is_friendly()) { // only move to unfriendly envs.
            //k = std::rand() % (paths.size() +1);
            //if (k == paths.size()) return;
            //random_neighbour = paths[k]->to_;
        //}
        //leave(a);
        //random_neighbour->enter(a);
    //}
//}

std::shared_ptr<Environment> Environment::get_random_neighbour() {
}


} // namespace ah
