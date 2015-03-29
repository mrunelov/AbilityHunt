/*
	The Console handles all text streaming to present 
	information to the user. 

*/

#ifndef AH_COMMAND_PARSER_H
#define AH_COMMAND_PARSER_H

#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <sstream>
#include <map>
#include <unordered_map>

#include "../abilities.h"
#include "command.h"

namespace ah
{

class CommandParser
{
public:
	std::map<ability_t, std::vector<std::string>> commands;
	std::vector<std::string> 			allCommands;
	std::map<std::string, ability_t>	abilities;

	CommandParser();
	~CommandParser();

	Command parse(const std::string& raw);


private:
	void initialize();
};

} //namespace ah


#endif //AH_COMMAND_PARSER_H
