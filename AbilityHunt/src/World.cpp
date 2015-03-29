#include "World.h"

#include <iostream>
#include <sstream>
#include <random>
#include <algorithm>

#include "Interaction/console.h"
#include "Interaction/command.h"
#include "Interaction/narrator.h"
#include "roamingmonster.h"
#include "abilityeater.h" 
#include "boss.h"
#include "item.h"
#include "elliot.h"

namespace ah
{

	World::World() :
        environments_(),
        quit_(false)
	{
	}

	World::~World()
	{
	}

	void World::initialize()
	{	

        /* ENVIRONMENTS (THE MAP)*/
	    auto home = std::make_shared<Environment>(
                FriendlyEnvironment("Meadow","You are in a meadow.", "The forest is green and you hear wildlife. It is quite damp, beautiful."));

	    auto valley = std::make_shared<Environment>(
                Environment("Valley", "You stand in the bottom of a valley.", "Though open and vast, there is almost no wind. The valley is peaceful."));

        auto ruin = std::make_shared<Environment>(
            Environment("Ruin", "You are in an old ruin.", "Old ivy-clad walls surround you and the air is fresh, but you sense something foul."));

        auto cellar = std::make_shared<Environment>(
                FriendlyEnvironment("Cellar", "You're in a cellar. The small room is dirty and moist.", "A small shimmer of light is cast through the hole in the roof. The walls are constructed of old worn stone blocks."));

        auto waterfall = std::make_shared<Environment>(
                Environment("Waterfall", "You found a waterfall in the forest.", "The place feels almost magical. The water is cool." ));

        auto waterfallcave = std::make_shared<Environment>(
                Environment("Waterfall Cave", "Behind the waterfall there is a secret room!", "The room seems to be some kind of abandoned hideout."));


        auto boss_room = std::make_shared<Environment>(
            FriendlyEnvironment("A dark room", "You're in a pitch black room.", "It is black.")); 
        
        environments_.push_back(home);          // 0
        environments_.push_back(valley);        // 1
        environments_.push_back(ruin);          // 2
        environments_.push_back(waterfall);     // 3
        environments_.push_back(cellar);        // 4
        environments_.push_back(waterfallcave); // 5     
        environments_.push_back(boss_room);      // 6

        environment_ = home;

        //// connect environmnents
        Path home_valley_path(1, "riverpath", 
                    "There is a path leading downhill along a river.", 
                    "The river meanders through an evergreen forest, birds are chirping and there is beautiful flora all around.");

        Path valley_home_path(0, "riverpath", 
                    "A small river is flowing out from the forest and can be followed uphill",
                     "The path feels untouched by evil.");

        Path home_cellar_path(4, "hole", "A hole in the ground, big enough to jump down, is close by.", "Looking down the hole its pitch black and smells of dirt. It's certainly very tempting to jump down");

        Path cellar_home_path(0, "hole", "A hole in the ceiling, big enough to climb up through, is close by.", "You see light at the other end");

        Path valley_ruin_path(2, "road", "An old meandering road leads east.", "You have some memory of this road. It leads to an old ruin");

        Path ruin_valley_path(1, "road", "The road back to the valley", "The pavement is worn from weather.");

        Path home_waterfall_path(3, "path", "Between two trees you see the start of a small path.", "The path goes uphill and joins the small river in the direction of its source.");

        Path waterfall_home_path(0, "shortcut", "A shortcut back to the meadow should be directly downhill. ", 
                    "Following the slope you fight your way through thick vegetation. Eventually you get to the meadow.");

        Path waterfall_cave_path(5, "rocks", "There are slippery rocks below the waterfall. ", 
                    "You walk up the rocks carefully and find there was a secret passegeway behind the waterfall!");

        Path cave_waterfall_path(3, "door", "There is a door at the side of the room",
                    "Apparently this was the intended way to get into the hideout, you walk down to the waterfall.");




        home->addPath(home_valley_path);
        home->addPath(home_cellar_path);
        cellar->addPath(cellar_home_path);
        valley->addPath(valley_home_path);
        valley->addPath(valley_ruin_path);
        ruin->addPath(ruin_valley_path);
        home->addPath(home_waterfall_path);
        waterfall->addPath(waterfall_home_path);
        waterfall->addPath(waterfall_cave_path);
        waterfallcave->addPath(cave_waterfall_path);




        Path to_boss(6, "An ominous door", "", "");
        to_boss.setPassword("1234");
        cellar->addPath(to_boss);

        /* CREATE UNDERGROUND MAZE /

        //int num_rooms = 4;
        //std::vector<std::shared_ptr<Environment>> maze;
        
        //for(int i = 0; i < num_rooms; ++i) {
            //std::ostringstream oss;
            //std::ostringstream oss2;
            //oss << (i+1);
            //oss2 << (num_rooms + i -1);
            //auto maze_room = std::make_shared<Environment>(
                //Environment("Dirt room #" + oss.str(), "A generic and dirty room", "A thick layer of dust covers the floor.")); 
            //maze.emplace_back(maze_room);
            //if(i > 0) {
                //auto maze_path = std::make_shared<Path>(
                        //Path(maze[i-1],maze[i], "Dirt path #" + oss.str(), "", ""));
                //maze[i-1]->addPath(maze_path);
            
                //auto maze_path_back = std::make_shared<Path>(
                    //Path(maze[i],maze[i-1], "Dirt path #" + oss2.str(), "", ""));
                //maze[i]->addPath(maze_path_back);
            //}   
        //}   
        
        //int num_random_maze_paths = num_rooms/2;
        //for(int i = 0; i < num_random_maze_paths; ++i) {
            //int from = std::rand() % num_rooms;
            //int to = -1;
            //do {
                //to = std::rand() % num_rooms;
            //} while(to == from);
            //auto random_path = std::make_shared<Path>(
                    //Path(maze[from],maze[to], "Dirt path #?", "", ""));
            //maze[from]->addPath(random_path);
            
        //}
        
        //auto exit = std::make_shared<Path>(
                //Path(maze[maze.size()-1],boss_room,"Boss Door", "A giant, important-looking, door.", "Getting closer, you see that the door has a locking mechanism!"));
            //maze[maze.size()-1]->addPath(exit);
        exit->setPassword("1234");

        //auto boss_room_maze_path = std::make_shared<Path>(
                //Path(boss_room, maze[maze.size()-1], "dirt maze", "", ""));
        //boss_room->addPath(boss_room_maze_path);
        
        //auto cellar_maze_path = std::make_shared<Path>(
                //Path(cellar, maze[0], "Dirt path #1", "", ""));
        //cellar->addPath(cellar_maze_path);
        
        //auto maze_cellar_path = std::make_shared<Path>(
                //Path(maze[0], cellar, "cellar", "", ""));
        //maze[0]->addPath(maze_cellar_path);
        //environments_.insert(environments_.end(),maze.begin(),maze.end());
        
        
        /* MONSTERS */
        std::shared_ptr<Actor> monster1 = std::make_shared<AbilityEater>(
                AbilityEater("Scary Monster", "A scary but harmless monster.", 2));

        monster1->make_notable(true);

        monster1->equip_weapon(Weapon("A4 paper", "Whitelines",0,0));
        monster1->take_item(Item("Ability", TALK, "Talk", "The ability to >talk<", 1));
        ruin->enter(monster1);

        //for(int i = 0; i < 3; ++i) { // insert two monsters into the maze
            //std::ostringstream oss;
            //oss << (i+1);
            //std::shared_ptr<Actor> roaming_monster = std::make_shared<RoamingMonster>(
                //RoamingMonster("Roaming Monster #" + oss.str(), "He can smell you", 2));
            //maze[i]->enter(roaming_monster);

        //}

        //maze[0]->actors[0]->take_item(Item("Ability", SARCASM, "Sarcasm","The ability to be sarcastic when talking", 5));

        /* THE PLAYER */    
        player_= std::make_shared<Actor>(Actor("Jens", "The player", true, 100));

        std::shared_ptr<Actor> boss = std::make_shared<Boss>(
                Boss("The Boss", "The ultimate challenge", 10));
        boss->take_item(Item("Ability", THE_ITEM, "The Item", "The thing everyone's looking for! Using it makes you >win< the game!", 1));
        boss_room->enter(boss);
    }

	void World::update()
	{

        Command command;
        do 
        {
            command = Console::instance().enterCommand();

            /* BAD COMMAND */
            if(!command.success) 
            {
                Console::instance().writeLine("Unrecognized command. Try again (hint: look in your inventory).");
                continue;
            }

            /* NOT ACCESSIBLE COMMAND*/
            if(command.ability != INVENTORY && !player_->has_item(command.ability))
            {
                Console::instance().writeLine("You don't have that ability yet.");
                continue;
            }

            /* MOVE ABILITY */ 
            if(command.ability == MOVE)
            {
                std::vector<std::string> options;
                for(Path& path : environment_->paths)
                    options.push_back(path.name());
               
                if (options.empty()) {
                    Console::instance().writeLine("There's nowhere to go.");
                }
                else {
                    int dest = Narrator::dialogue("where?", options);

                    //narrate moving along path
                    Console::instance().write(environment_->paths[dest].long_description());
                    Console::instance().writeLine("..", Console::SPEED_SLOW);
                    Console::instance().enterToContinue();
                    Console::instance().enterToContinue();


                    if(environment_->paths[dest].openTo(*player_))
                    {
                        //move player and update current environment
                        environment_->leave(player_);
                        environment_ = environments_[environment_->paths[dest].to_];
                        environment_->enter(player_);
                    }
                }
            }

            else if(command.ability == TALK) 
            {
                std::vector<std::string> options;
                for(const std::shared_ptr<Actor>& actor : environment_->actors) {
                    if (actor->is_player()) continue;
                    options.push_back(actor->name());
                }
                int actor = Narrator::dialogue("talk to whom?", options);
                environment_->actors[actor]->talk(player_);
            }
            
            /* INVENTORY ABILITY */
            else if(command.ability == INVENTORY)
            {
                player_->inventory().describe();
            }

            /* LOOK AROUND ABILITY */
            else if(command.ability == LOOK) 
            {
                //describe the environment
                environment_->describe();
            }

            /* LOOT ITEMS */
            else if(command.ability == LOOT)
            {
                if(environment_->items.size() == 0)
                {
                    Console::instance().writeLine("there is nothing here to loot.");
                }
                else
                {
                    std::vector<std::string> options;
                    for(const Item& item : environment_->items)
                        options.push_back(item.name());

                    int i_item = Narrator::dialogue("Pick up: ", options);

                    //copy item to inventory
                    std::vector<Item>& items = environment_->items;
                    player_->take_item(environment_->items[i_item]);
                    items.erase(std::remove(items.begin(), items.end(), items[i_item]));
                    Console::instance() << "picked up " << items[i_item].name() << ". " << items[i_item].short_description();
                    Console::instance().nextLine();
                }

            }

            else if(command.ability == QUIT)
            {
                Console::instance().writeLineStop("Game OVer!");
                quit_ = true;
            }
            else if(command.ability == THE_ITEM)
            {
                Console::instance().writeLineStop("You Won!! :D");
                quit_ = true;   
            }


            //Update Map
            for(int i = 0; i < environments_.size(); ++i) {
                if(environments_[i] == environment_) continue; // always update player env last
                environments_[i]->update();
            }
            //// in case a monster enters this round or something, we update player env last
            environment_->update();

        } while(!command.success);
	}

	void World::draw()
	{
		////as for now, just make the next frame with a newline so that its easier to see
        //Console::instance().nextLine();
        //Console::instance().nextLine();
	}

    std::shared_ptr<Environment> World::getEnvironment(const std::string name)
    {

        for(const std::shared_ptr<Environment>& env : environments_)
        {
            if(env->name() == name)
                return env;
        }

        return nullptr;
    }

    bool World::quit()
    {
        return quit_;
    }
}
