#include "Gameplay.h"

#include <iostream>
#include <string>

#include "Interaction/console.h"
#include "Interaction/commandParser.h"
#include "Interaction/narrator.h"
#include "actor.h"
#include "abilities.h"
#include "inventory.h"
#include "elliot.h"


namespace ah
{

Gameplay::Gameplay() {}

Gameplay::~Gameplay()
{
}

void Gameplay::initialize()
{
    world_.initialize();

	/*  STARTUP APPLICATION */
    Console::instance().writeLine("----------------------------------", Console::SPEED_INSTANT);
    Console::instance().writeLine("       RUNNING ABILITY HUNT       ", Console::SPEED_INSTANT);
    Console::instance().writeLine("----------------------------------", Console::SPEED_INSTANT);
    Console::instance().nextLine();
    Console::instance().writeLineStop("(Press Enter to Start)");
    Console::instance().nextLine();
    Console::instance().nextLine();

    //[> INTRO <]
    Console::instance().indent(3);
    std::shared_ptr<Actor> elliot = std::make_shared<Elliot>(Elliot());

	////// wake up
    Console::instance().writeLineStop("it is dark...");
    Console::instance().write("but you hear footsteps");
    Console::instance().writeLineStop("...", Console::SPEED_VERY_SLOW);
	
	//// Speak to Elliot
    int gethelp = Narrator::dialogue(elliot->name(), 
                                    "Hello there friend! You seem to have gotten into some trouble there. Want some help?",
                                     { "(Nod)", "(Shake head)" }
                                 );
    if(gethelp != 0) 
    {
        Console::instance().writeLine(" - ok, well you are probably not going to last long with that attitude");
        Console::instance().writeLine("...");
        Console::instance().writeLine("(Game Over) TODO: quit game here");
        while(true) { std::cin.ignore(); }
		
    }

    world_.player_->take_item(Item("Passive", TEXT_GRAPHICS, "Non-see-through glasses.", "Opaque glasses that gives you text graphics", 1));
    world_.player_->take_item(Item("Ability", LOOK, "Binoculars", "Lets you >look< around", 1));
    world_.player_->take_item(Item("Ability", LOOT, "Thief Gloves", "Lets you >loot< or >pick< up items", 1));
    world_.player_->take_item(Item("Ability", QUIT, "On/Off Switch", "Pressing this make you >quit< the game (Game Over)", 1));
    //world_.player_->take_item(Item("Ability", TALK, "Talk", "The ability to talk", 1));

    // Have a look at your inventory
    Console::instance().enterToContinue();
    Narrator::quote(elliot->name(), "Why, you don't have any boots? I'll leave an extra pair for you here!"
                                                        "Nice looking glasses by the way!");

    Item boots("Ability", MOVE, "Red Boots", "These magical boots lets you >move<", 1);
    boots.make_notable(true);
    world_.environment_->add_item(boots);
    Console::instance().writeLine(Narrator::tooltip("press >inv< to view your inventory"));
    Command command;
    do
    {
        command = Console::instance().enterCommand();
    } while(command.ability != INVENTORY);
    
    Console::instance().indent();
    world_.player_->inventory().describe();
    Console::instance().dedent();
    Console::instance().enterToContinue();
    
    //elliot leaves => finish intro sequence
    Narrator::quote(elliot->name(), "Well, I'm off. Good luck to you!");
    Console::instance().enterToContinue();
    Console::instance() << elliot->name() << " trots off, you should get to your senses.";


    world_.getEnvironment("Waterfall Cave")->enter(elliot);


    // The game begins
    //Console::instance().enterToContinue();
    //for (int i = 0; i < 67; ++i) Console::instance().writeLine(".");
    //Console::instance().nextLine();
    //Console::instance().nextLine();
    //Console::instance().nextLine();

}

int Gameplay::run()
{
	//Initialize and draw before gameplay loop
    //world_.draw();
    world_.environment_->enter(world_.player_); // OBS: the player entering rooms triggers descriptions, so it's last!
		
    while (!world_.quit())
    {
        world_.draw();
        world_.update();
    }

	return 0;
}


} // namespace ah
