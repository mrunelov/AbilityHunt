#include "commandParser.h"

namespace ah
{

//static initialization of commands

CommandParser::CommandParser()
	: allCommands(),
	  abilities()
{
    commands = 
    {
            {MOVE, 		{"move", "go", "enter", "explore"}},
            {LISTEN, 	{"listen"}},
            {TALK, 		{"talk", "say", "announce"}},
            {LOOK, 		{"look", "view"}},
            {EXAMINE, 	{"examine", "inspect", "investigate"}},
            {INVENTORY, {"inventory", "inv", "backpack"}},
            {LOOT, 		{"loot", "pick", "pickup"}},
            {QUIT,		{"quit", "ragequit"}},
            {THE_ITEM, 	{"win"}}
    };

    initialize();	
}

CommandParser::~CommandParser()
{
}


void CommandParser::initialize()
{
	// Build abilities map and extract commands strings
	for(int i = 0; i != NUM_ABILITIES; ++i)
	{
		ability_t ability = static_cast<ability_t>(i);
		for(const std::string& command : commands[ability])
		{
			allCommands.push_back(command);
			abilities[command] = ability;
		}
	}
}
	
Command CommandParser::parse(const std::string& raw)
{
	// first iteration: raw is one word, find which ability it corresponds to
	Command command;
	command.raw_input = raw;

	if(abilities.find(raw) == abilities.end())
	{
		command.success = false;
		return command;
	}

	command.ability = abilities[raw];
	command.success = true;

	return command;
}

} //namespace ah
